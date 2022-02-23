set(req i2cdev freertos)

idf_component_register(SRCS "lsm303c.c" "lsm303c_calibration.c" "lsm303c_if.c" "lsm303c_configuration.c"
        INCLUDE_DIRS "." REQUIRES ${req})
