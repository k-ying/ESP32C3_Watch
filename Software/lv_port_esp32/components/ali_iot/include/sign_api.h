#ifndef __SIGN_H__
#define __SIGN_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOTX_PRODUCT_KEY_LEN            (20)
#define IOTX_PRODUCT_SECRET_LEN         (64)
#define IOTX_DEVICE_NAME_LEN            (32)
#define IOTX_DEVICE_SECRET_LEN          (64)

#define DEV_SIGN_SOURCE_MAXLEN          (200)
#define DEV_SIGN_HOSTNAME_MAXLEN        (64)
#define DEV_SIGN_CLIENT_ID_MAXLEN       (200)
#define DEV_SIGN_USERNAME_MAXLEN        (64)
#define DEV_SIGN_PASSWORD_MAXLEN        (65)

typedef enum {
    IOTX_CLOUD_REGION_SHANGHAI,   /* Shanghai */
    IOTX_CLOUD_REGION_SINGAPORE,  /* Singapore */
    IOTX_CLOUD_REGION_JAPAN,      /* Japan */
    IOTX_CLOUD_REGION_USA_WEST,   /* America */
    IOTX_CLOUD_REGION_GERMANY,    /* Germany */
    IOTX_CLOUD_REGION_CUSTOM,     /* Custom setting */
    IOTX_CLOUD_DOMAIN_MAX         /* Maximum number of domain */
} iotx_mqtt_region_types_t;

typedef struct _iotx_dev_meta_info {
    char product_key[IOTX_PRODUCT_KEY_LEN + 1];
    char product_secret[IOTX_PRODUCT_SECRET_LEN + 1];
    char device_name[IOTX_DEVICE_NAME_LEN + 1];
    char device_secret[IOTX_DEVICE_SECRET_LEN + 1];
} iotx_dev_meta_info_t;

typedef struct {
    char hostname[DEV_SIGN_HOSTNAME_MAXLEN];
    uint16_t port;
    char clientid[DEV_SIGN_CLIENT_ID_MAXLEN];
    char username[DEV_SIGN_USERNAME_MAXLEN];
    char password[DEV_SIGN_PASSWORD_MAXLEN];
} iotx_sign_mqtt_t;

int32_t IOT_Sign_MQTT(iotx_mqtt_region_types_t region, iotx_dev_meta_info_t *meta, iotx_sign_mqtt_t *signout);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef __SIGN_H__ */

