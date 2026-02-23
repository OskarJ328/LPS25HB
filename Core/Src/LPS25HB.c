/*
 * LPS25HB.c
 *
 *  Created on: Feb 23, 2026
 *      Author: ozker
 */

#include "LPS25HB.h"
#include "LPS25HB_regs.h"
#include "i2c.h"

static uint8_t lps_read_reg(uint8_t reg_addr){
    uint8_t reg_value = 0;
    HAL_I2C_Mem_Read(&hi2c1, LPS25HB_ADDR, reg_addr, 1, &reg_value, 1, HAL_MAX_DELAY);
    return reg_value;
}

