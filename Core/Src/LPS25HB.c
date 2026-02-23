/*
 * LPS25HB.c
 *
 *  Created on: Feb 23, 2026
 *      Author: ozker
 */

#include "LPS25HB.h"
#include "LPS25HB_regs.h"
#include "i2c.h"

#define WHO_AM_I_VAL 0xBD

static uint8_t lps_read_reg(uint8_t reg_addr){
    uint8_t reg_value = 0;
    HAL_I2C_Mem_Read(&hi2c1, LPS25HB_ADDR, reg_addr, 1, &reg_value, 1, HAL_MAX_DELAY);
    return reg_value;
}

static void lps_write_reg(uint8_t reg_addr, uint8_t value){
    HAL_I2C_Mem_Write(&hi2c1, LPS25HB_ADDR, reg_addr, 1, &value, sizeof(value), HAL_MAX_DELAY);
}

bool lps_check_connection(void){
    uint8_t who_am_i = lps_read_reg(LPS25HB_WHO_AM_I);

    if (who_am_i == WHO_AM_I_VAL){
        return true;
    }
    else{
        return false;
    }
}
