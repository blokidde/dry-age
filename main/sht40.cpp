#include  "sht40.h"

void read_sht40(){
    ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, &cmd, 1, I2C_MASTER_TIMEOUT_MS));
    vTaskDelay(pdMS_TO_TICKS(20));

    ESP_ERROR_CHECK(i2c_master_receive(dev_handle, data, 6, I2C_MASTER_TIMEOUT_MS));

    // test print to find the temp and humidity
    // printf("%02X %02X %02X %02X %02X %02X\n", data[0], data[1], data[2], data[3], data[4], data[5]);

    uint16_t raw_temp = ((uint16_t)data[0] << 8) | data[1];
    uint16_t raw_hum  = ((uint16_t)data[3] << 8) | data[4];

    float temperature = -45.0f + 175.0f * ((float)raw_temp / 65535.0f);
    float humidity   = -6.0f + 125.0f * ((float)raw_hum / 65535.0f);

    if (humidity < 0.0f) {
        humidity = 0.0f;
    }
    if (humidity > 100.0f) {
        humidity = 100.0f;
    }
}