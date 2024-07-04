#ifndef USERWIFI_H
#define USERWIFI_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "esp_sntp.h"

// #include <stdio.h>
// #include <unistd.h>
// #include <pthread.h>
// #include "aiot_state_api.h"
// #include "aiot_sysdep_api.h"
// #include "aiot_mqtt_api.h"
                                    /* mqtt need */
#include <stdint.h>
#include <stddef.h>
// #include "esp_wifi.h"
// #include "esp_system.h"
// #include "nvs_flash.h"
// #include "esp_event.h"
// #include "esp_netif.h"
// #include "protocol_examples_common.h"

//#include "freertos/semphr.h"
//#include "freertos/queue.h"

//#include "lwip/sockets.h"
//#include "lwip/dns.h"
//#include "lwip/netdb.h"
//#include "cJSON.h"

#include "mqtt_client.h"
#include "sign_api.h" // 包含签名所需的各种数据结构定义


#include "lvgl/lvgl.h"
/* The examples use WiFi configuration that you can set via project configuration menu

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
// #define EXAMPLE_ESP_WIFI_SSID      "kyGTNeo"
// #define EXAMPLE_ESP_WIFI_PASS      "gtneowifi233"
char wifi_ssid[32];     /* 定义一个数组用来存储ssid*/
char wifi_passwd[64];   /* 定义一个数组用来存储passwd */
#define EXAMPLE_ESP_MAXIMUM_RETRY  5

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

bool Conn_Flag;
struct tm timeinfo;
//void *mqtt_handle;
esp_mqtt_client_handle_t client;
static const char *TAG = "wifi station";

static int s_retry_num = 0;

void wifi_user_init(void);

uint8_t SNTP_GetTime(void);
void mqtt_app_start(void);
void lv_mqtt_task(lv_task_t * task);
//extern void lv_mqtt_task();

#endif
