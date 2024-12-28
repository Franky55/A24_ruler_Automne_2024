idf_component_register(SRCS "main.cpp" "TimeBased.cpp" "I2C_Controller.cpp" "IMU.cpp" 
                    "Processus/IMU_Processus.cpp" "TCA9534.cpp" "IO_Expender.cpp" "Processus/Button_Processus.cpp"
                    "Processus/WebBrowser.cpp"
                    "src/platform.cpp"
                    "src/vl53l5cx_api.cpp"
                    "src/vl53l5cx_plugin_detection_thresholds.cpp"
                    "src/vl53l5cx_plugin_motion_indicator.cpp"
                    "src/vl53l5cx_plugin_xtalk.cpp"
                    INCLUDE_DIRS "." "../includes" "../includes/include")