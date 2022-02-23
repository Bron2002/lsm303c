#include "lsm303c.h"
#include <math.h>
#include "lsm303c_if.h"

const char *tag = "lsm303c";
MagnetData mRaw = {
        .min = {INT16_MAX, INT16_MAX, INT16_MAX},
        .max = {INT16_MIN, INT16_MIN, INT16_MIN}
};

esp_err_t lsm303c_init(gpio_num_t sda, gpio_num_t scl, i2c_port_t num)
{
    uint8_t data;
    lsm303c_dev.cfg.scl_io_num = scl;
    lsm303c_dev.cfg.sda_io_num = sda;
    lsm303c_dev.port = num;
    // I2C init.
    ESP_ERROR_CHECK(i2c_param_config(lsm303c_dev.port, &lsm303c_dev.cfg));

    ESP_ERROR_CHECK(i2cdev_init());

    ESP_ERROR_CHECK(a_readRegs(ACC_WHO_AM_I, &data, 1));
    if (data != LSM303C_WHO_I_AM_A)
        ESP_LOGE(tag, "incorrect 'who i a`m' of accel");

    ESP_ERROR_CHECK(m_readRegs(MAG_WHO_AM_I, &data, 1));
    if (data != LSM303C_WHO_I_AM_M)
        ESP_LOGE(tag, "incorrect 'who i a`m' of magnet");

    return ESP_OK;
}

esp_err_t lsm303c_config_m(
        MAG_DO_t dataRate,
        MAG_OMXY_t omxy,
        MAG_TEMP_EN_t tempEn,
        MAG_FS_t fs,
        MAG_MD_t mode,
        MAG_OMZ_t omz,
        MAG_BDU_t bdu
)
{
    uint8_t data[] = {
            tempEn | omxy | dataRate,
            fs,
            mode,
            omz,
            bdu
    };

    return m_writeRegs(MAG_CTRL_REG1, data, 5);
}

bool lsm303c_mDataReady()
{
    uint8_t data;
    ESP_ERROR_CHECK_WITHOUT_ABORT(m_readRegs(MAG_STATUS_REG, &data, 1));
    return data & MAG_XYZDA_YES;
}

float lsm303c_getMagneticField()
{
    float sqrtSum = 0;
    for (int i = 0; i < 3; i++)
    {
        sqrtSum += (float) pow(LSM303C_M_SENS * (float) mRaw.centered[i], 2.0);
    }
    return pow(sqrtSum, 0.5);
}

esp_err_t lsm303c_update_m()
{
    return m_readRegs(MAG_OUTX_L, &mRaw.raw, 6);
}

esp_err_t lsm303c_updateAndCalc_m()
{
    esp_err_t e = m_readRegs(MAG_OUTX_L, &mRaw.raw, 6);
    for (int i = 0; i < 3; ++i)
    {
        if (mRaw.max[i] < mRaw.raw[i])
        {
            mRaw.max[i] = mRaw.raw[i];
            mRaw.d[i] = (mRaw.max[i] + mRaw.min[i]) / 2;
        } else if (mRaw.min[i] > mRaw.raw[i])
        {
            mRaw.min[i] = mRaw.raw[i];
            mRaw.d[i] = (mRaw.max[i] + mRaw.min[i]) / 2;
        }
        mRaw.centered[i] = mRaw.raw[i] - mRaw.d[i];
    }
    return e;
}

inline MagnetData lsm303c_getData_m()
{
    return mRaw;
}

void lsm303c_getRawData_m(int16_t *data)
{
    i2c_dev_read_reg(&lsm303c_dev, MAG_OUTX_L, data, 6);
}

esp_err_t lsm303c_selfTest_m(bool en)
{
    uint8_t d;
    ESP_ERROR_CHECK_WITHOUT_ABORT(m_readRegs(MAG_CTRL_REG1, &d, 1));
    if (en)
        d |= MAG_ST_EN;
    else
        d &= MAG_ST_DIS;
    return m_writeRegs(MAG_CTRL_REG1, &d, 1);
}
