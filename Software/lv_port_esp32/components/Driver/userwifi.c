
#include "userwifi.h"

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            // .ssid = wifi_ssid,
            // .password = wifi_passwd,

            /* Setting a password implies station will connect to all security modes including WEP/WPA.
             * However these modes are deprecated and not advisable to be used. Incase your Access point
             * doesn't support WPA2, these mode can be enabled by commenting below line */
	        .threshold.authmode = WIFI_AUTH_WPA2_PSK,

            .pmf_cfg = {
                .capable = true,
                .required = false
            },
        },
    };
    strcpy((char *)wifi_config.sta.ssid, wifi_ssid);
    strcpy((char *)wifi_config.sta.password, wifi_passwd);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 wifi_ssid, wifi_passwd);
                 Conn_Flag=true; //userflag
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 wifi_ssid, wifi_passwd);
                 Conn_Flag=false; 
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
        Conn_Flag=false; 
    }

    /* The event will not be processed after unregister */
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
    vEventGroupDelete(s_wifi_event_group);
}


void wifi_user_init(void)
{
    //Initialize NVS
    // esp_err_t ret = nvs_flash_init();
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    //   ESP_ERROR_CHECK(nvs_flash_erase());
    //  ret =  nvs_flash_init();
    //  }
    //  ESP_ERROR_CHECK(ret);
    Conn_Flag = false;

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    printf("---------------- WiFi START! -----------------\n");
    //vTaskDelay(1000/portTICK_RATE_MS);
    wifi_init_sta();
    printf("---------------- WiFi OK! -----------------\n");

}

/* -------------------------------------- SNTP Func ----------------------------------- */
static void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    if (sntp_enabled())
    {
        sntp_stop();
    }
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "ntp1.aliyun.com");
    sntp_init();
}
static void obtain_time(void)
{
    //ESP_ERROR_CHECK( nvs_flash_init() );
    //ESP_ERROR_CHECK(esp_netif_init());
    //ESP_ERROR_CHECK( esp_event_loop_create_default() );

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    //ESP_ERROR_CHECK(example_connect());

    initialize_sntp();

    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 10;
    // do{
    //     retry = 0;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count)
        {
            ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        // if(esp_wifi_disconnect()==ESP_OK){
        //     uint8_t reconn_count=0;
        //     while(esp_wifi_connect() != ESP_OK && reconn_count <5){
        //         ESP_LOGI(TAG, "Reconnect after disconnect... (%d/5)", reconn_count);
        //     }
        //     vTaskDelay(2000 / portTICK_PERIOD_MS);
        // }
    // } while (retry==retry_count);
    
    time(&now);
    localtime_r(&now, &timeinfo);

    //ESP_ERROR_CHECK( example_disconnect() );
}

uint8_t SNTP_GetTime(void)
{
    time_t now;
    
    time(&now);
    localtime_r(&now, &timeinfo);
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2021 - 1900)) {
        ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time over NTP.");
        obtain_time();
        // update 'now' variable with current time
        time(&now);
    }

    char strftime_buf[64];
        // update 'now' variable with current time
        time(&now);
        // Set timezone to China Standard Time
        setenv("TZ", "CST-8", 1);
        tzset();
        localtime_r(&now, &timeinfo);
        // strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
        // ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
    if (timeinfo.tm_year < (2021 - 1900))
    {
        return 1;
    }else return 0;
    
}

                                    /* 使用LVGL TASK管理：心跳和消息 */
// lv_task_t * mqtt_task = lv_task_create(lv_mqtt_task, 5000, LV_TASK_PRIO_LOWEST, mqtt_handle);

// 下面的几个宏用于定义设备的阿里云身份认证信息：ProductKey、ProductSecret、DeviceSecret、DeviceName
// 在实际产品开发中，设备的身份认证信息应该是设备厂商将其加密后存放于设备Flash中或者某个文件中，
// 设备上电时将其读出后使用
// #define LIGHT_PRODUCT_KEY "a1yn1z1pwiQ"
// #define LIGHT_PRODUCT_SECRET "5H7isOnx0ZRzzkiD"
// #define LIGHT_DEVICE_SECRET "59ef12d3f80d8708ac6dee52d67aa311"
// #define LIGHT_DEVICE_NAME "demo1"
#define LIGHT_PRODUCT_KEY "a1fpFa35yU2"
#define LIGHT_PRODUCT_SECRET "8z36QxtRWwgSJp3t"
#define LIGHT_DEVICE_SECRET "81efbc2aaab4c2ac3c4087cbb376683b"
#define LIGHT_DEVICE_NAME "demo1"
// 初始化mqtt的客户端
/**
 * mqtt event callback function.
 * @param event event data
 */
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED: // MQTT 客户端连接上服务器事件
        msg_id = esp_mqtt_client_publish(client, "/a1fpFa35yU2/demo1/user/update", "Hello!!!!!", 0, 0, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        lv_task_t * mqtt_task = lv_task_create(lv_mqtt_task, 5000, LV_TASK_PRIO_LOWEST,client);
        break;
    case MQTT_EVENT_DISCONNECTED: // MQTT 客户端断开连接事件
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED: // MQTT 订阅事件
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED: // MQTT 取消订阅事件
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED: // MQTT 发布消息到指定主题事件
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA: // MQTT 客户端接收到数据事件
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        // mqtt data router to specified topic
        //topic_router_handler(event);
        break;
    case MQTT_EVENT_ERROR: // 错误事件
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }

    return ESP_OK;
}

/**
 * mqtt event handler function.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

/**
 * start mqtt client.
 */
void mqtt_app_start(void)
{
    // 设备的元信息
    iotx_dev_meta_info_t meta_info;
    // 阿里云认证签名
    iotx_sign_mqtt_t sign_mqtt;

    memset(&meta_info, 0, sizeof(iotx_dev_meta_info_t));
    // 下面的代码是将上面静态定义的设备身份信息赋值给meta_info
    memcpy(meta_info.product_key, LIGHT_PRODUCT_KEY, strlen(LIGHT_PRODUCT_KEY));
    memcpy(meta_info.product_secret, LIGHT_PRODUCT_SECRET, strlen(LIGHT_PRODUCT_SECRET));
    memcpy(meta_info.device_name, LIGHT_DEVICE_NAME, strlen(LIGHT_DEVICE_NAME));
    memcpy(meta_info.device_secret, LIGHT_DEVICE_SECRET, strlen(LIGHT_DEVICE_SECRET));

    // 调用签名函数，生成MQTT连接时需要的各种数据，IOTX_CLOUD_REGION_SHANGHAI 指连接站点是华东2(上海)
    IOT_Sign_MQTT(IOTX_CLOUD_REGION_SHANGHAI, &meta_info, &sign_mqtt);

    esp_mqtt_client_config_t mqtt_cfg = {
        // .uri = CONFIG_BROKER_URL,
        .host = sign_mqtt.hostname,      // 完整的阿里云物联网站点域名
        .port = 1883,                    // 阿里云站点的端口号
        .password = sign_mqtt.password,  // MQTT建立连接时需要指定的Password。把提交给服务器的参数按字典排序并拼接后，使用hmacsha256方法和设备的DeviceSecret，加签生成Password。
        .client_id = sign_mqtt.clientid, // MQTT建立连接时需要指定的ClientID。建议使用设备的MAC地址或SN码，64字符内。
        .username = sign_mqtt.username,  // MQTT建立连接时需要指定的Username。由设备名DeviceName、符号（&）和产品ProductKey组成，格式：deviceName+"&"+productKey。示例：Device1&alSseIs****。
        // .event_handle = mqtt_event_handler, // mqtt客户端启动成功后对连接、断开连接、订阅、取消订阅、发布、接收数据等事件的处理。
    };
#if CONFIG_BROKER_URL_FROM_STDIN
    char line[128];

    if (strcmp(mqtt_cfg.uri, "FROM_STDIN") == 0)
    {
        int count = 0;
        printf("Please enter url of mqtt broker\n");
        while (count < 128)
        {
            int c = fgetc(stdin);
            if (c == '\n')
            {
                line[count] = '\0';
                break;
            }
            else if (c > 0 && c < 127)
            {
                line[count] = c;
                ++count;
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        mqtt_cfg.uri = line;
        printf("Broker url: %s\n", line);
    }
    else
    {
        ESP_LOGE(TAG, "Configuration mismatch: wrong broker url");
        abort();
    }
#endif /* CONFIG_BROKER_URL_FROM_STDIN */

    // 初始化mqtt的客户端
    client = esp_mqtt_client_init(&mqtt_cfg);
    // 注册mqtt连接、断开连接、订阅、取消订阅、发布、接收数据等事件的处理。
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    // 启动esp mqtt的客户端
    esp_mqtt_client_start(client);
}

