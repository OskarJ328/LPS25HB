/*
 * LPS25HB.c
 *
 *  Created on: Feb 23, 2026
 *      Author: ozker
 */

#include "LPS25HB.h"
#include "LPS25HB_regs.h"
#include "i2c.h"

#define TIMEOUT 100


static uint8_t lps_read_reg(uint8_t reg_addr){
    uint8_t reg_value = 0;
    HAL_I2C_Mem_Read(&hi2c1, LPS25HB_ADDR, reg_addr, 1, &reg_value, 1, TIMEOUT);
    return reg_value;
}

static void lps_write_reg(uint8_t reg_addr, uint8_t value){
    HAL_I2C_Mem_Write(&hi2c1, LPS25HB_ADDR, reg_addr, 1, &value, sizeof(value), TIMEOUT);
}

static bool lps_check_connection(void){
    uint8_t who_am_i = lps_read_reg(LPS25HB_WHO_AM_I);

    if (who_am_i == WHO_AM_I_VAL){
        return true;
    }
    else{
        return false;
    }
}

bool lps_init(void){
    if(lps_check_connection()){
        lps_write_reg(LPS25HB_CTRL_REG1, CTRL_REG_ODR2 | CTRL_REG_PD);
        return true;
    }
    else{
        return false;
    }
    
}

float lps_read_temp(void){ 
    uint8_t raw_temp_buffer[2];

    if(HAL_I2C_Mem_Read(&hi2c1, LPS25HB_ADDR, TEMP_OUT, 1, raw_temp_buffer, sizeof(raw_temp_buffer), TIMEOUT) != HAL_OK){
        Error_Handler();
    }
    
    int16_t raw_temp = (int16_t)((raw_temp_buffer[1] << 8) | raw_temp_buffer[0]); 

    float temp = 42.5f + (raw_temp / 480.0f);
    return temp;
}

float lps_read_pressure(void){
    uint8_t raw_pressure_buffer[3];
    if(HAL_I2C_Mem_Read(&hi2c1, LPS25HB_ADDR, PRESSURE_OUT, 1, raw_pressure_buffer, sizeof(raw_pressure_buffer), TIMEOUT) != HAL_OK){
        Error_Handler();
    }

    int32_t raw_pressure = (int32_t)((raw_pressure_buffer[2] << 16) | (raw_pressure_buffer[1] << 8) | raw_pressure_buffer[0]);
    
    float pressure = raw_pressure / 4096.0;
    return pressure;
}