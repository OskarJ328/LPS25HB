/*
 * LPS25HB.h
 *
 *  Created on: Feb 23, 2026
 *      Author: ozker
 */

#ifndef INC_LPS25HB_H_
#define INC_LPS25HB_H_

#include "stdbool.h"
#include "stdint.h"

bool lps_init(void);
float lps_read_temp(void);
float lps_read_absolute_pressure(void);
void lps_set_pressure_offset(uint16_t offset);
float lps_count_relative_pressure(float abs_pressure_hPa, float altitude_height_m);
#endif /* INC_LPS25HB_H_ */
