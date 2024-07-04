#include "MPU6050.h"

#define SCL TOUCH_I2C_SCL    /*!< I2C SCL pin number  */
#define SDA TOUCH_I2C_SDA    /*!< I2C SDA pin number  */

// /**
//  * @brief I2C initial
//  */
// void I2C_Init()
// {
//     i2c_config_t config;
//     config.master.clk_speed = 40000;
//     config.mode = I2C_MODE_MASTER;
//     config.scl_io_num = SCL;
//     config.sda_io_num = SDA;
//     config.sda_pullup_en = GPIO_PULLUP_ENABLE;
//     config.scl_pullup_en = GPIO_PULLUP_ENABLE;

//     i2c_param_config(I2C_NUM_0, &config);
//     i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
// }

/**
 * @brief MPU-6050 initial
 */
uint8_t MPU_Init()
{
	uint8_t res = 0;
	//I2C_Init();
	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x80);
	vTaskDelay(100 / portTICK_RATE_MS);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0x00);
	MPU_Set_Gyro_FSR(2);//3
	MPU_Set_Accel_FSR(2);
	MPU_Set_Rate(50);
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//关闭所有中断
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	MPU_Read_Byte(MPU_DEVICE_ID_REG, &res);
	if(res == MPU_ADDR)
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU_Set_Rate(50);						//设置采样率为50Hz
	}else
		return 1;
	return 0;
}

/**
 * @brief Set the Gyroscope full-scale range of ±250, ±500, ±1000, and ±2000°/sec (dps)
 *
 * @param fsr the number of register, it could be 0, 1, 2, 3
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Set_Gyro_FSR(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG, fsr << 3);
}

/**
 * @brief Set the Accelerometer full-scale range of ±2g, ±4g, ±8g, and ±16g
 *
 * @param fsr the number of register, it could be 0, 1, 2, 3
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Set_Accel_FSR(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG, fsr << 3);
}

/**
 * @brief Set the band of low pass filter
 *
 * @param lps parameter is the band of low pass filter
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6;
	return MPU_Write_Byte(MPU_CFG_REG, data);
}

/**
 * @brief Set the Sample rate of Gyroscope, Accelerometer, DMP, etc.
 *
 * @param rate parameter is the sample rate of Gyroscope, Accelerometer, DMP, etc.
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate > 1000)
		rate = 1000;
	if(rate < 4)
		rate = 4;
	data = 1000/rate - 1;
	data = MPU_Write_Byte(MPU_SAMPLE_RATE_REG, data);
	return MPU_Set_LPF(rate / 2); /*!< set low pass filter the half of the rate */
}

/**
 * @brief Get the temperature of the MPU-6050
 *
 * @return
 *     - temp is the temperature of the MPU-6050
 *     - 1 is Error
 */
int16_t MPU_Get_Temperature()
{
	uint8_t buf[2];
	int16_t raw;
	float temp;
	if(MPU_Read_Len(MPU_TEMP_OUTH_REG, buf, 2) == 0)
		return 1;
	raw = ((uint16_t)(buf[1] << 8)) | buf[0];
	temp = 36.53 + ((double)raw/340);
	return temp*100;
}

/**
 * @brief Get the Gyroscope data of the MPU-6050
 *
 * @param gx parameter is the x axis data of Gyroscope
 * @param gy parameter is the y axis data of Gyroscope
 * @param gz parameter is the z axis data of Gyroscope
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Get_Gyroscope(int16_t *gx, int16_t *gy, int16_t *gz)
{
	uint8_t buf[6], res;
	res = MPU_Read_Len(MPU_GYRO_XOUTH_REG, buf, 6);
	if(res == 0)
	{
		*gx=((uint16_t)buf[0]<<8)|buf[1];
		*gy=((uint16_t)buf[2]<<8)|buf[3];
		*gz=((uint16_t)buf[4]<<8)|buf[5];
	}
	return res;
}

/**
 * @brief Get the Accelerometer data of the MPU-6050
 *
 * @param ax parameter is the x axis data of Accelerometer
 * @param ay parameter is the y axis data of Accelerometer
 * @param az parameter is the z axis data of Accelerometer
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Get_Accelerometer(int16_t *ax, int16_t *ay, int16_t *az)
{
	uint8_t buf[6], res;
	res = MPU_Read_Len(MPU_ACCEL_XOUTH_REG, buf, 6);
	if(res == 0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];
		*ay=((uint16_t)buf[2]<<8)|buf[3];
		*az=((uint16_t)buf[4]<<8)|buf[5];
	}
	return res;
}

/**
 * @brief Write a byte to MPU-6050 through I2C
 *
 * @param reg parameter is a register of MPU-6050
 * @param data parameter will be written to the register of MPU-6050
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Write_Byte(uint8_t reg, uint8_t data)
{
	esp_err_t error;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	error = i2c_master_write_byte(cmd, (MPU_ADDR << 1) | I2C_MASTER_WRITE, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_write_byte(cmd, reg, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_write_byte(cmd, data, 1);
	if(error != ESP_OK)
		return 1;

	i2c_master_stop(cmd);

	i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);

	i2c_cmd_link_delete(cmd);

	return 0;
}

/**
 * @brief Write a buffer to MPU-6050 through I2C
 *
 * @param reg parameter is a register of MPU-6050
 * @param data parameter is a buffer which will be written to a register of MPU-6050
 * @param len parameter is the length of data
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Write_Len(uint8_t reg, uint8_t *data, uint8_t len)
{
	esp_err_t error;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	error = i2c_master_write_byte(cmd, (MPU_ADDR << 1) | I2C_MASTER_WRITE, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_write_byte(cmd, reg, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_write(cmd, data, len, 1);
	if(error != ESP_OK)
		return 1;

	i2c_master_stop(cmd);

	i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);

	i2c_cmd_link_delete(cmd);

	return 0;
}

/**
 * @brief Read a byte from MPU-6050 through I2C
 *
 * @param reg parameter is a register of MPU-6050
 * @param res the data read will be stored in this parameter
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Read_Byte(uint8_t reg, uint8_t *res)
{

	esp_err_t error;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	error = i2c_master_write_byte(cmd, (MPU_ADDR << 1) | I2C_MASTER_WRITE, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_write_byte(cmd, reg, 1);
	if(error != ESP_OK)
		return 1;

	i2c_master_start(cmd);
	error = i2c_master_write_byte(cmd, (MPU_ADDR << 1) | I2C_MASTER_READ, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_read_byte(cmd, res, I2C_MASTER_LAST_NACK);
	if(error != ESP_OK)
		return 1;

	i2c_master_stop(cmd);

	i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);

	i2c_cmd_link_delete(cmd);
	return 0;
}

/**
 * @brief Read a buffer from MPU-6050 through I2C
 *
 * @param reg parameter is a register of MPU-6050
 * @param buf parameter is a buf witch will store the data
 * @param len parameter is the length of buf
 *
 * @return
 *     - 0 is Success
 *     - 1 is Error
 */
uint8_t MPU_Read_Len(uint8_t reg, uint8_t *buf, uint8_t len)
{
	esp_err_t error;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	error = i2c_master_write_byte(cmd, (MPU_ADDR << 1) | I2C_MASTER_WRITE, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_write_byte(cmd, reg, 1);
	if(error != ESP_OK)
		return 1;

	i2c_master_start(cmd);
	error = i2c_master_write_byte(cmd, (MPU_ADDR << 1) | I2C_MASTER_READ, 1);
	if(error != ESP_OK)
		return 1;

	error = i2c_master_read(cmd, buf, len, I2C_MASTER_LAST_NACK);
	if(error != ESP_OK)
		return 1;

	i2c_master_stop(cmd);

	i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);

	i2c_cmd_link_delete(cmd);
	return 0;
}

#define SVM_Buf_size 5
#define CV_Buf_size 15

uint8_t SVM_FallenDet(float SVM_v, int16_t az)
{
	static uint8_t SVM_P = 0,CV_P = 0;
	static float SVM_BUF[SVM_Buf_size];
	static uint8_t CV_BUF[CV_Buf_size];
	bool CV_flag=0,Fall_flag=0;
	float SUM=0,SD=0;
	// int16_t ax=0,ay=0,az=0;
	//MPU_Get_Accelerometer(&ax,&ay,&az);
/*
	//printf("ax = %f,ay = %f,az = %f\n", ax/16384.0,ay/16384.0,az/16384.0);
	//printf("az = %d\n", az);
	// printf("az = %f\n", acos(az/16384.0) * 57.29577);
*/
	SVM_BUF[SVM_P] = SVM_v ;//sqrt((ax/16384.0)*(ax/16384.0) + (ay/16384.0)*(ay/16384.0)  + (az/16384.0)*(az/16384.0));
/*
	// printf("SVM = %f ",SVM_BUF[SVM_P]);
	//if SVM > SVM_flag
*/
	if (SVM_BUF[SVM_P] > 1.8)
	{
		for(int i = 0; i < SVM_P+1;i++)
    	{
    	    SUM += SVM_BUF[i];
    	}
		SUM = SUM / (SVM_P+1);//now SUM is AVG

		for (int j = 0;j < SVM_P+1;j++)
    	{
    	    SD += pow((SVM_BUF[j]-SUM),2);
    	}
		SD = sqrt(SD / (SVM_P+1));
/*
		//printf("\nSD = %f \n",SD);
		//CV is (SUM / SD), if CV > CV_flag
*/
		if ((SD / SUM) > 0.30)
		{
			CV_flag=1;
		}else{CV_flag=0;}
/*
		// printf("CV = %f ", (SD / SUM));
*/
	}else{CV_flag=0;}
/*-------------------------- MUST DO For Next --------------------------*/
	CV_BUF[CV_P] = CV_flag;
	if (SVM_P == SVM_Buf_size-1)
	{
		for (int k = 0; k < SVM_Buf_size-1; k++)
		{
			SVM_BUF[k]=SVM_BUF[k+1];
		}
	}else{SVM_P++;}
	if (CV_P == SVM_Buf_size-1)
	{
		CV_P =0;
		SUM=0;
		for (int L = 0; L < SVM_Buf_size-1; L++)
		{
			SUM += CV_BUF[L];
			CV_BUF[L]=0;
		}
		if (SUM == 1){
			Fall_flag=1;
/*
			//printf("------1-----");
*/
		}
	}else{CV_P++;}
	if(Fall_flag && az > 10000)//az~<65^o
	{
		return 1;
	}else{return 0;}
}