/*
 * LPS25HB_regs.h
 *
 *  Created on: Feb 23, 2026
 *      Author: ozker
 */

#ifndef INC_LPS25HB_REGS_H_
#define INC_LPS25HB_REGS_H_

//registers
#define LPS25HB_ADDR 0xBA
#define LPS25HB_WHO_AM_I 0x0F
#define LPS25HB_CTRL_REG1 0x20
#define LPS25HB_CTRL_REG2 0x21
#define LPS25HB_CTRL_REG3 0x22
#define LPS25HB_CTRL_REG4 0x23
#define LPS25HB_PRESS_OUT_XL 0x28
#define LPS25HB_PRESS_OUT_L 0x29
#define LPS25HB_PRESS_OUT_H 0x2A
#define LPS25HB_TEMP_OUT_L 0x2B
#define LPS25HB_TEMP_OUT_H 0x2C


//register values
#define WHO_AM_I_VAL 0xBD
#define CTRL_REG_PD 0x80
#define CTRL_REG_ODR2 0x40
// ponizszy define wynika z tego ze jesli chcemy od razu odczytac dwa rejestry na raz
//nalezy zmienic najstarszy bit adresu na 1.
#define TEMP_OUT LPS25HB_TEMP_OUT_L | 0x80

#endif /* INC_LPS25HB_REGS_H_ */
