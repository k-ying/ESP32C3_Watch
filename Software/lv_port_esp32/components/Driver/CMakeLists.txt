idf_component_register(#SRCS "userwifi.c" "inv_mpu.c" "inv_mpu_dmp_motion_driver.c" "MPU6050.c" "MAX30205.c"
                    SRC_DIRS . "MAX30205" "MPU6050" "MAX30102"
                    INCLUDE_DIRS . "MAX30205" "MPU6050" "MAX30102"
                    REQUIRES lvgl)
