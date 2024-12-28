#ifndef WEB_BROWSER_H
#define WEB_BROWSER_H

#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "esp_mac.h" // For MAC2STR and MACSTR

#define WIFI_SSID "RulerFrankLau"
#define WIFI_PASS "Ruler2024"
#define MAX_STA_CONN 4

void wifi_init_softap();
httpd_handle_t start_webserver();
void send_sse_update(float value1, float value2);

extern httpd_req_t *Request;
extern bool ClientConnected;

#endif