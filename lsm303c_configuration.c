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
    ESP_ERROR_CHECK(i2c_dev_read_reg(&lsm303c_a, ACC_WHO_AM_I, &data, 1));
    if (data != LSM303C_WHO_I_AM_A)
        ESP_LOGE(tag, "incorrect 'who i a`m' of accel");

    ESP_ERROR_CHECK(i2c_dev_read_reg(&lsm303c_m, MAG_WHO_AM_I, &data, 1));
    if (data != LSM303C_WHO_I_AM_M)
        ESP_LOGE(tag, "incorrect 'who i a`m' of magnet");

    return ESP_OK;
}

esp_err_t lsm303c_m_config(
        MAG_DO_t dataRate,
        MAG_OMXY_t omxy,
        MAG_TEMP_EN_t tempEn,
        MAG_FS_t fs,
        MAG_MD_t mode,
        MAG_OMZ_t omz,
        MAG_BDU_t bdu
)
{
    // Assembling of config message.
    uint8_t data[] = {
            tempEn | omxy | dataRate,
            fs,
            mode,
            omz,
            bdu
    };
    // Send config message and return status of it.
    return i2c_dev_write_reg(&lsm303c_m, MAG_CTRL_REG1, data, sizeof(data));
}

esp_err_t lsm303c_m_set(MAG_ConfBit cb)
{
    uint8_t data, reg = cb >> 8;
    esp_err_t err;
    if ((err = i2c_dev_read_reg(&lsm303c_m, reg, &data, 1)) != ESP_OK)
        return err;
    data |= (uint8_t)cb;
    return i2c_dev_write_reg(&lsm303c_m, reg, &data, 1);
}

esp_err_t lsm303c_m_reset(MAG_ConfBit cb)
{
    uint8_t data, reg = cb >> 8;
    esp_err_t err;
    if ((err = i2c_dev_read_reg(&lsm303c_m, reg, &data, 1)) != ESP_OK)
        return err;
    data &= ~(uint8_t)cb;
    return i2c_dev_write_reg(&lsm303c_m, reg, &data, 1);
}
