//
// Created by bronislav on 10.02.22.
//
#ifndef MAGN_LSM303C_IF_H
#define MAGN_LSM303C_IF_H

#include "lsm303c_types.h"
#include "i2cdev.h"

// Set standard config, if it not exists.
#ifndef CONFIG_LSM303C_I2C_CLK_SPEED
#define CONFIG_LSM303C_I2C_CLK_SPEED 400000
#define CONFIG_LSM303C_I2C_CLK_PULL_UP 1
#define CONFIG_LSM303C_I2C_SDA_PULL_UP 1
#endif

extern const i2c_dev_t lsm303c_a;
extern const i2c_dev_t lsm303c_m;
extern const char *tag;

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
