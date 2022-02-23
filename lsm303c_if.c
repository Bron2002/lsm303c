//
// Created by bronislav on 23.02.22.
//
#include "lsm303c.h"
#include "lsm303c_if.h"

const i2c_dev_t lsm303c_a = {
        .cfg = {
                .mode = I2C_MODE_MASTER,
                .scl_io_num = CONFIG_LSM303C_I2C_CLK_GPIO,
                .sda_io_num = CONFIG_LSM303C_I2C_SDA_GPIO,
                .scl_pullup_en = CONFIG_LSM303C_I2C_CLK_PULL_UP,
                .sda_pullup_en = CONFIG_LSM303C_I2C_SDA_PULL_UP,
                .master.clk_speed = CONFIG_LSM303C_I2C_CLK_SPEED,
                .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL
        },
        .port = CONFIG_LSM303C_I2C_NUM,
        .addr = ACC_I2C_ADDR
};

const i2c_dev_t lsm303c_m = {
        .cfg = {
                .mode = I2C_MODE_MASTER,
                .scl_io_num = CONFIG_LSM303C_I2C_CLK_GPIO,
                .sda_io_num = CONFIG_LSM303C_I2C_SDA_GPIO,
                .scl_pullup_en = CONFIG_LSM303C_I2C_CLK_PULL_UP,
                .sda_pullup_en = CONFIG_LSM303C_I2C_SDA_PULL_UP,
                .master.clk_speed = CONFIG_LSM303C_I2C_CLK_SPEED,
                .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL
        },
        .port = CONFIG_LSM303C_I2C_NUM,
        .addr = MAG_I2C_ADDR
};