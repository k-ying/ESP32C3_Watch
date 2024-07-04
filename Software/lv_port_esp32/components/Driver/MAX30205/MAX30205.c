#include "MAX30205.h"

/**
 @brief I2C写数据函数
 @param slaveAddr -[in] 从设备地址
 @param regAddr -[in] 寄存器地址
 @param pData -[in] 写入数据
 @param dataLen -[in] 写入数据长度,byte
 @return 错误码
*/
int ESPI2C_WriteData(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pData, uint16_t dataLen)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, slaveAddr | WRITE_BIT, ACK_CHECK_EN); //c3 idf4.4无需位移设备地址
    if(NULL != regAddr)
    {
        i2c_master_write_byte(cmd, regAddr, ACK_CHECK_EN);
    }
    i2c_master_write(cmd, pData, dataLen, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
 @brief I2C读数据函数
 @param slaveAddr -[in] 从设备地址
 @param regAddr -[in] 寄存器地址
 @param pData -[in] 读出数据
 @param dataLen -[in] 读出数据长度
 @return 错误码
*/
int ESPI2C_ReadData(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pData, uint16_t dataLen)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, slaveAddr | READ_BIT, ACK_CHECK_EN); //c3 idf4.4无需位移设备地址
    if(NULL != regAddr)
    {
        i2c_master_write_byte(cmd, regAddr, ACK_CHECK_EN);
    }
    i2c_master_read(cmd, pData, dataLen, ACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

int MAX30205_Init (void)
{
    //IIC_Init();
    //i2c_master_init();
   //I2CwriteByte(MAX30205_ADDRESS, MAX30205_CONFIGURATION, 0x00);
   uint8_t Wregdata=0x00;
   int ret = ESPI2C_WriteData(MAX30205_ADDRESS, MAX30205_CONFIGURATION,&Wregdata, 1);
   /*
    //      I2CwriteByte(MAX30205_ADDRESS, MAX30205_THYST ,        0x00);
    //   I2CwriteByte(MAX30205_ADDRESS, MAX30205_TOS, 0x00); */
    return ret;
}

int16_t Read_max16(uint8_t address,uint8_t subAddress)
{
            int16_t All_Data;
            uint8_t Part_Data;
            //非标准读取，需要自己写，时序看DataSheet

            //I2Cwriteaddr(address|IIC_WRITE, subAddress); //对器件地址发送写入命令 写入寄存器地址
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, address | WRITE_BIT, ACK_CHECK_EN);
            i2c_master_write_byte(cmd, subAddress, ACK_CHECK_EN);
            //need delay?

            //IIC_Start();                                           //开始
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, address | READ_BIT, ACK_CHECK_EN);
            //IIC_Send_Byte(address|IIC_READ);                //发送读取命令
            i2c_master_read_byte(cmd, &All_Data, ACK_VAL);
            //IIC_Wait_Ack();                                    //等待回应
            //data=IIC_Read_Byte(1);//主机发送应答信号
            
            //IIC_Wait_Ack();
            //instant = IIC_Read_Byte(0);//主机发送非应答信号
            i2c_master_read_byte(cmd, &Part_Data, NACK_VAL);

            //IIC_Stop();                             //产生停止信号
            i2c_master_stop(cmd);
 
            i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
            i2c_cmd_link_delete(cmd);

            All_Data = (All_Data<<8) | Part_Data; // 数据合并
  
            return All_Data;   
}   

double GetTemperature(void)
{
    double temperature= 0.0;
    int16_t temp;
    temp = Read_max16(MAX30205_ADDRESS,MAX30205_TEMPERATURE);
    temperature = temp*0.00390625;
    return  temperature;
}