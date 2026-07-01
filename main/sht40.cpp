#include  "sht40.h"

esp_err_t read_sht40(i2c_master_dev_handle_t dev_handle, sht40_data_t* result){

    if (result == nullptr || dev_handle == nullptr) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t cmd = SHT40_CMD_MEASURE;
    uint8_t data[6];
    esp_err_t ret = i2c_master_transmit(dev_handle, &cmd, 1, I2C_MASTER_TIMEOUT_MS);

    if (ret != ESP_OK) {
        return ret;
    }

    vTaskDelay(pdMS_TO_TICKS(20));

    ret = i2c_master_receive(dev_handle, data, 6, I2C_MASTER_TIMEOUT_MS);

    if (ret != ESP_OK) {
        return ret;
    }

    // test print to find the temp and humidity in bytes
    // printf("%02X %02X %02X %02X %02X %02X\n", data[0], data[1], data[2], data[3], data[4], data[5]);

    uint16_t raw_temp = ((uint16_t)data[0] << 8) | data[1];
    uint16_t raw_hum  = ((uint16_t)data[3] << 8) | data[4];

    result->temperature = -45.0f + 175.0f * ((float)raw_temp / 65535.0f);
    result->humidity   = -6.0f + 125.0f * ((float)raw_hum / 65535.0f);

    if (result->humidity < 0.0f) {
        result->humidity = 0.0f;
    }
    if (result->humidity > 100.0f) {
        result->humidity = 100.0f;
    }

    return ESP_OK;
}