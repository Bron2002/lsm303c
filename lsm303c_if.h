//
// Created by bronislav on 10.02.22.
//
#ifndef MAGN_LSM303C_IF_H
#define MAGN_LSM303C_IF_H

#include "lsm303c_types.h"
#include "i2cdev.h"

i2c_dev_t lsm303c_dev = {
        .port = 0,
        .cfg = {
                .mode = I2C_MODE_MASTER,
                .scl_pullup_en = true,
                .sda_pullup_en = true,
                .master.clk_speed = 400000,
                .clk_flags = 0
        }
};

static inline esp_err_t m_readRegs(MAG_REG_t startReg, void *data, uint8_t size)
{
    lsm303c_dev.addr = MAG_I2C_ADDR;
    return i2c_dev_read_reg(&lsm303c_dev, startReg, data, size);
}

static inline esp_err_t m_writeRegs(MAG_REG_t startReg, uint8_t *data, uint8_t size)
{
    lsm303c_dev.addr = MAG_I2C_ADDR;
    return i2c_dev_write_reg(&lsm303c_dev, startReg, data, size);
}

static inline esp_err_t a_readRegs(ACC_REG_t startReg, uint8_t *data, uint8_t size)
{
    lsm303c_dev.addr = ACC_I2C_ADDR;
    return i2c_dev_read_reg(&lsm303c_dev, startReg, data, size);
}

static inline esp_err_t a_writeRegs(ACC_REG_t startReg, uint8_t *data, uint8_t size)
{
    lsm303c_dev.addr = ACC_I2C_ADDR;
    return i2c_dev_write_reg(&lsm303c_dev, startReg, data, size);
}

#endif //MAGN_LSM303C_IF_H
