//
// Created by bronislav on 23.02.22.
//
#include "lsm303c.h"
#include "lsm303c_if.h"

esp_err_t lsm303c_init()
{
    // data for reading.
    uint8_t data;

    // I2C init.
    ESP_ERROR_CHECK(i2c_param_config(lsm303c_a.port, &lsm303c_a.cfg));

    // I2cdev initialize.
    ESP_ERROR_CHECK(i2cdev_init());

    // Checking "who I am" registers.
    ESP_ERROR_CHECK(a_readRegs(ACC_WHO_AM_I, &data, 1));
    if (data != LSM303C_WHO_I_AM_A)
        ESP_LOGE(tag, "incorrect 'who i a`m' of accel");

    ESP_ERROR_CHECK(m_readRegs(MAG_WHO_AM_I, &data, 1));
    if (data != LSM303C_WHO_I_AM_M)
        ESP_LOGE(tag, "incorrect 'who i a`m' of magnet");

    return ESP_OK;
}