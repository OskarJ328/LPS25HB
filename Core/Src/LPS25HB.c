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

    float temp_C = 42.5f + (raw_temp / 480.0f);
    return temp_C;
}

float lps_read_absolute_pressure(void){
    uint8_t raw_pressure_buffer[3];
    if(HAL_I2C_Mem_Read(&hi2c1, LPS25HB_ADDR, PRESSURE_OUT, 1, raw_pressure_buffer, sizeof(raw_pressure_buffer), TIMEOUT) != HAL_OK){
        Error_Handler();
    }

    int32_t raw_pressure = (int32_t)((raw_pressure_buffer[2] << 16) | (raw_pressure_buffer[1] << 8) | raw_pressure_buffer[0]);
    
    float pressure_hPa = raw_pressure / 4096.0;
    return pressure_hPa;
}

void lps_set_pressure_offset(uint16_t offset){
    uint16_t reg_val = 16 * offset;
    lps_write_reg(LPS25HB_RPDS_L, reg_val);
    lps_write_reg(LPS25HB_RPDS_H, reg_val >> 8);
}

float lps_count_relative_pressure(float abs_pressure_hPa, float altitude_height_m){
    float pressure_diff_hPa = 11.7f * altitude_height_m / 100.0f;
    return abs_pressure_hPa + pressure_diff_hPa;
}