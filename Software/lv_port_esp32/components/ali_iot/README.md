将组件内容放入到项目下就可以将组件加入到项目中
//下面的几个宏用于定义设备的阿里云身份认证信息：ProductKey、ProductSecret、DeviceName、DeviceSecret
//在实际产品开发中，设备的身份认证信息应该是设备厂商将其加密后存放于设备Flash中或者某个文件中，
//设备上电时将其读出后使用
```
#define LIGHT_PRODUCT_KEY "xx"
#define LIGHT_PRODUCT_SECRET "xxx"
#define LIGHT_DEVICE_NAME "light"
#define LIGHT_DEVICE_SECRET "xxxx"

在启动mqtt协议时
iotx_dev_meta_info_t meta_info;
iotx_sign_mqtt_t sign_mqtt;

memset(&meta_info, 0, sizeof(iotx_dev_meta_info_t));
//下面的代码是将上面静态定义的设备身份信息赋值给meta_info
memcpy(meta_info.product_key, LIGHT_PRODUCT_KEY, strlen(EXAMPLE_PRODUCT_KEY));
memcpy(meta_info.product_secret, LIGHT_PRODUCT_SECRET, strlen(EXAMPLE_PRODUCT_SECRET));
memcpy(meta_info.device_name, LIGHT_DEVICE_NAME, strlen(EXAMPLE_DEVICE_NAME));
memcpy(meta_info.device_secret, LIGHT_DEVICE_SECRET, strlen(EXAMPLE_DEVICE_SECRET));

//调用签名函数，生成MQTT连接时需要的各种数据
IOT_Sign_MQTT(IOTX_CLOUD_REGION_SHANGHAI, &meta_info, &sign_mqtt);

esp_mqtt_client_config_t mqtt_cfg = {
    .host = sign_mqtt.hostname,
    .port = 1883,
    .password = sign_mqtt.password,
    .client_id = sign_mqtt.clientid,
    .username = sign_mqtt.username,
    .event_handle = mqtt_event_handler,
};
```
