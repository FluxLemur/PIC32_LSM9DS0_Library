/************
This is a library for the LSM9DS0.

Inspired by the adafruit library for the same breakout board for the Arduino.

Written by Alex Spitzer, Leo Mehr, Einar Veizaga for ECE 4760.
MIT License
************/
#ifndef __LSM9DS0_H__
#define __LSM9DS0_H__

/* All gryo registers and their addresses */
typedef enum {
    WHO_AM_I_G = 0x0F,

    CTRL_REG1_G = 0x20,
    CTRL_REG2_G = 0x21,
    CTRL_REG3_G = 0x22,
    CTRL_REG4_G = 0x23,
    CTRL_REG5_G = 0x24,

    REFERENCE_G = 0x25,
    STATUS_REG_G = 0x27,

    OUT_X_L_G = 0x28,
    OUT_X_H_G = 0x29,
    OUT_Y_L_G = 0x2A,
    OUT_Y_H_G = 0x2B,
    OUT_Z_L_G = 0x2C,
    OUT_Z_H_G = 0x2D,

    FIFO_CTRL_REG_G = 0x2E,
    FIFO_SRC_REG_G = 0x2F,

    INT1_CFG_G = 0x30,
    INT1_SRC_G = 0x31,
    INT1_TSH_XH_G = 0x32,
    INT1_TSH_XL_G = 0x33,
    INT1_TSH_YH_G = 0x34,
    INT1_TSH_YL_G = 0x35,
    INT1_TSH_ZH_G = 0x36,
    INT1_TSH_ZL_G = 0x37,
    INT1_DURATION_G = 0x38,
} gryo_register;

/* All accel / mag registers and their addresses */
typedef enum {
    OUT_TEMP_L_XM = 0x05,
    OUT_TEMP_H_XM = 0x06,

    STATUS_REG_M = 0x07,

    OUT_X_L_M = 0x08,
    OUT_X_H_M = 0x09,
    OUT_Y_L_M = 0x0A,
    OUT_Y_H_M = 0x0B,
    OUT_Z_L_M = 0x0C,
    OUT_Z_H_M = 0x0D,

    WHO_AM_I_XM = 0x0F,

    INT_CTRL_REG_M = 0x12,
    INT_SRC_REG_M = 0x13,
    INT_THS_L_M = 0x14,
    INT_THS_H_M = 0x15,

    OFFSET_X_L_M = 0x16,
    OFFSET_X_H_M = 0x17,
    OFFSET_Y_L_M = 0x18,
    OFFSET_Y_H_M = 0x19,
    OFFSET_Z_L_M = 0x1A,
    OFFSET_Z_H_M = 0x1B,

    REFERENCE_X = 0x1C,
    REFERENCE_Y = 0x1D,
    REFERENCE_Z = 0x1E,

    CTRL_REG0_XM = 0x1F,
    CTRL_REG1_XM = 0x20,
    CTRL_REG2_XM = 0x21,
    CTRL_REG3_XM = 0x22,
    CTRL_REG4_XM = 0x23,
    CTRL_REG5_XM = 0x24,
    CTRL_REG6_XM = 0x25,
    CTRL_REG7_XM = 0x26,

    STATUS_REG_A = 0x27,

    OUT_X_L_A = 0x28,
    OUT_X_H_A = 0x29,
    OUT_Y_L_A = 0x2A,
    OUT_Y_H_A = 0x2B,
    OUT_Z_L_A = 0x2C,
    OUT_Z_H_A = 0x2D,

    FIFO_CTRL_REG = 0x2E,
    FIFO_SRC_REG = 0x2F,

    INT_GEN_1_REG = 0x30,
    INT_GEN_1_SRC = 0x31,
    INT_GEN_1_THS = 0x32,
    INT_GEN_1_DURATION = 0x33,
    INT_GEN_2_REG = 0x34,
    INT_GEN_2_SRC = 0x35,
    INT_GEN_2_THS = 0x36,
    INT_GEN_2_DURATION = 0x37,

    CLICK_CFG = 0x38,
    CLICK_SRC = 0x39,
    CLICK_THS = 0x3A,

    TIME_LIMIT = 0x3B,
    TIME_LATENCY = 0x3C,
    TIME_WINDOW = 0x3D,
    Act_THS = 0x3E,
    Act_DUR = 0x3F
} xm_register;

void lsm9ds0_init(unsigned int CS_G, unsigned int CS_XM);
void lsm9ds0_update();

/* Read the who_am_i register values in the gyro and accelerometer */
char lsm9ds0_whoami_g();
char lsm9ds0_whoami_xm();

float get_accel_x();
float get_accel_y();
float get_accel_z();
float get_gyro_x();
float get_gyro_y();
float get_gyro_z();

#endif
