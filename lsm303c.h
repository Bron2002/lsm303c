#ifndef __LSM303C_H__
#define __LSM303C_H__

#include "esp_types.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "lsm303c_types.h"

/**
 * The function initialize i2c device for lsm303c.\n
 * It uses ESP_ERROR_CHECK() and can to cause esp aboard.\n
 * @note I2C configuration can be changed in menu configuration.
 * @return ESP_OK, if nothing wasn't interrupt it.
 */
esp_err_t lsm303c_init();

/**
 * @brief Initialization of magnetometer.\n
 * The function initializes magnetometer with following parameters.
 * @param dataRate Output data rate selection.
 * @param omxy X and Y axes operative mode selection.
 * @param tempEn Temperature sensor enable.
 * @param fs Full-scale configuration.
 * @param mode Operating mode selection.
 * @param omz Z-axis operative mode selection.
 * @param bdu Block data update for magnetic data.
 * @return status of data sending.
 */
esp_err_t lsm303c_m_config(
        MAG_DO_t dataRate,
        MAG_OMXY_t omxy,
        MAG_TEMP_EN_t tempEn,
        MAG_FS_t fs,
        MAG_MD_t mode,
        MAG_OMZ_t omz,
        MAG_BDU_t bdu
);
/**
 * The function for enabling control bit.
 *
 * @param cb control bit typedef (it contains mask and address of register).
 * @return status of sending data.
 */
esp_err_t lsm303c_m_set(MAG_ConfBit cb);
/**
 * The function for disabling control bit.
 *
 * @param cb control bit typedef (it contains mask and address of register).
 * @return status of sending data.
 */
esp_err_t lsm303c_m_reset(MAG_ConfBit cb);

float lsm303c_getMagneticField();

void lsm303c_getRawData_m(int16_t *data);

esp_err_t lsm303c_update_m();

esp_err_t lsm303c_updateAndCalc_m();

MagnetData lsm303c_getData_m();

bool lsm303c_mDataReady();


#endif