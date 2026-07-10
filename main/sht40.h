#pragma once

#include <stdint.h>
#include "driver/i2c_master.h"
#include "esp_err.h"

typedef struct {
    float temperature;
    float humidity;
} sht40_data_t;

esp_err_t read_sht40(i2c_master_dev_handle_t dev_handle, sht40_data_t* result);
void sht40_i2c_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle);
