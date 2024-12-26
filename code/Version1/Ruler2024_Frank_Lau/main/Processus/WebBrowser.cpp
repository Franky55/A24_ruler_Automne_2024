
// #include "WebBrowser.h"

// static const char *TAG = "WiFi_Server";

// /* HTML content for the webpage */
// static const char *HTML_PAGE = 
//     "<!DOCTYPE html>"
//     "<html>"
//     "<head><title>ESP32 Web Server</title></head>"
//     "<body>"
//     "<h1>Welcome to ESP32-C3 Web Server!</h1>"
//     "<p>This is a simple webpage served by the ESP32-C3.</p>"
//     "</body>"
//     "</html>";

// /* HTTP GET handler */
// esp_err_t get_handler(httpd_req_t *req) {
//     httpd_resp_set_type(req, "text/html");
//     httpd_resp_send(req, HTML_PAGE, strlen(HTML_PAGE));
//     return ESP_OK;
// }

// /* Start the HTTP server */
// httpd_handle_t start_webserver(void) {
//     httpd_config_t config = HTTPD_DEFAULT_CONFIG();

//     httpd_uri_t uri_get = {
//         .uri      = "/",
//         .method   = HTTP_GET,
//         .handler  = get_handler,
//         .user_ctx = NULL
//     };

//     httpd_handle_t server = NULL;
//     if (httpd_start(&server, &config) == ESP_OK) {
//         httpd_register_uri_handler(server, &uri_get);
//     }
//     return server;
// }

// /* Wi-Fi Event Handler */
// void wifi_event_handler(void *arg, esp_event_base_t event_base,
//                                int32_t event_id, void *event_data) {
//     if (event_id == WIFI_EVENT_AP_START) {
//         ESP_LOGI(TAG, "Wi-Fi Access Point started");
//     } else if (event_id == WIFI_EVENT_AP_STACONNECTED) {
//         wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
//         ESP_LOGI(TAG, "Station " MACSTR " joined, AID=%d", MAC2STR(event->mac), event->aid);
//     } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
//         wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
//         ESP_LOGI(TAG, "Station " MACSTR " left, AID=%d", MAC2STR(event->mac), event->aid);
//     }
// }

// /* Initialize Wi-Fi in Access Point mode */
// void wifi_init_softap(void) {
//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_ap();

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));

//     esp_event_handler_instance_t instance_any_id;
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
//                                                         ESP_EVENT_ANY_ID,
//                                                         &wifi_event_handler,
//                                                         NULL,
//                                                         &instance_any_id));

//     wifi_config_t wifi_config = {
//     .ap = {
//         .ssid = "ESP32-AP",
//         .password = "password123",
//         .ssid_len = strlen("ESP32-AP"), // Optional, can be 0 if SSID is null-terminated
//         .channel = 1,
//         .authmode = WIFI_AUTH_WPA_WPA2_PSK,
//         .ssid_hidden = 0,
//         .max_connection = 4,
//         .beacon_interval = 100, // Default value
//         .csa_count = 3,         // Default value
//         .dtim_period = 2,       // Default value
//         .pairwise_cipher = WIFI_CIPHER_TYPE_CCMP, // Optional, depends on security setup
//         .ftm_responder = false,
//         .pmf_cfg = {
//             .capable = true,
//             .required = false
//         },
//         .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
//     }
// };



//     if (strlen(WIFI_PASS) == 0) {
//         wifi_config.ap.authmode = WIFI_AUTH_OPEN;
//     }

//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());

//     ESP_LOGI(TAG, "Wi-Fi Access Point started with SSID: %s, Password: %s", WIFI_SSID, WIFI_PASS);
// }


















#include "WebBrowser.h"

static const char *TAG = "WiFi_Server";

httpd_req_t *Request;
bool ClientConnected;

/* HTML content for the webpage */
static const char *HTML_PAGE = 
    "<!DOCTYPE html>"
    "<html>"
    "<head><title>ESP32 Web Server</title></head>"
    "<body>"
    "<h1>Welcome to ESP32-C3 Web Server!</h1>"
    "<p>Value: <span id='value1'>0</span></p>"
    "<p>Value: <span id='value2'>0</span></p>"
    "<p>Value: <span id='value3'>0</span></p>"
    "<script>"
    "const eventSource = new EventSource('/events');"
    "eventSource.onmessage = function(event) {"
    "   const values = event.data.split(\",\");"
    "    document.getElementById('value1').innerText = values[0];"
    "    document.getElementById('value2').innerText = values[1];"
    "    document.getElementById('value3').innerText = values[2];"
    "};"
    "</script>"
    "</body>"
    "</html>";

/* HTTP GET handler */
esp_err_t get_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, HTML_PAGE, strlen(HTML_PAGE));
    return ESP_OK;
}

/* HTTP GET handler for the SSE events */
esp_err_t sse_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/event-stream");
    httpd_resp_set_hdr(req, "Cache-Control", "no-cache");
    httpd_resp_set_hdr(req, "Connection", "keep-alive");
    Request = req;
    ClientConnected = true;

    ESP_LOGI("SSE", "Client connected.");

    // Keep the connection alive indefinitely
    while (ClientConnected) {
        vTaskDelay(pdMS_TO_TICKS(10));  // Wait to avoid a busy loop
    }

    ESP_LOGI("SSE", "Client disconnected.");
    Request = NULL;  // Clear the global pointer
    return ESP_OK;
}

/* Start the HTTP server */
httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_uri_t uri_get = {
        .uri      = "/",
        .method   = HTTP_GET,
        .handler  = get_handler,
        .user_ctx = NULL
    };

    httpd_uri_t uri_sse = {
        .uri      = "/events",
        .method   = HTTP_GET,
        .handler  = sse_handler,
        .user_ctx = NULL
    };

    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_sse);
    }
    return server;
}

/* Wi-Fi Event Handler */
void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
    if (event_id == WIFI_EVENT_AP_START) {
        ESP_LOGI(TAG, "Wi-Fi Access Point started");
    } else if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
        ESP_LOGI(TAG, "Station " MACSTR " joined, AID=%d", MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
        ESP_LOGI(TAG, "Station " MACSTR " left, AID=%d", MAC2STR(event->mac), event->aid);
    }
}

/* Initialize Wi-Fi in Access Point mode */
void wifi_init_softap(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        &instance_any_id));

    wifi_config_t wifi_config = {
    .ap = {
        .ssid = "ESP32-AP",
        .password = "password123",
        .ssid_len = strlen("ESP32-AP"), // Optional, can be 0 if SSID is null-terminated
        .channel = 1,
        .authmode = WIFI_AUTH_WPA_WPA2_PSK,
        .ssid_hidden = 0,
        .max_connection = 4,
        .beacon_interval = 100, // Default value
        .csa_count = 3,         // Default value
        .dtim_period = 2,       // Default value
        .pairwise_cipher = WIFI_CIPHER_TYPE_CCMP, // Optional, depends on security setup
        .ftm_responder = false,
        .pmf_cfg = {
            .capable = true,
            .required = false
        },
        .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
    }
};



    if (strlen(WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi Access Point started with SSID: %s, Password: %s", WIFI_SSID, WIFI_PASS);
}



void send_sse_update(int value1, int value2, int value3)
{
    if (Request != NULL && ClientConnected) {
        char message[128];
        snprintf(message, sizeof(message), "data: %d,%d,%d\n\n", value1, value2, value3);

        if (httpd_resp_send_chunk(Request, message, strlen(message)) != ESP_OK) {
            ESP_LOGW("SSE", "Failed to send update. Client might be disconnected.");
            ClientConnected = false;  // Mark the client as disconnected
        }
    } else {
        // ESP_LOGW("SSE", "No active client to send updates.");
    }
}