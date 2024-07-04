#ifndef __30205_H
#define __30205_H
#include "driver/i2c.h"
#include "lvgl_i2c_conf.h"

/**************************** IIC定义 *************************************/

#define I2C_MASTER_SCL_IO           TOUCH_I2C_SCL      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           TOUCH_I2C_SDA      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          TOUCH_I2C_SPEED_HZ                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

/**************************** IIC定义 *************************************/

#define MAX30205_ADDRESS  0X90    // A2/1/0->GND = 0x90h from Datasheet
#define MAX30205_TEMPERATURE 0X00
#define MAX30205_CONFIGURATION 0X01
#define MAX30205_THYST         0X02
#define MAX30205_TOS           0X03

int ESPI2C_WriteData(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pData, uint16_t dataLen);
int ESPI2C_ReadData(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pData, uint16_t dataLen);
int MAX30205_Init (void);
int16_t Read_max16(uint8_t address,uint8_t subAddress);
double GetTemperature(void);

#endif
