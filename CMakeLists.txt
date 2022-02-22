set(req i2cdev freertos)

idf_component_register(SRCS "lsm303c.c"
        INCLUDE_DIRS "." REQUIRES ${req})
