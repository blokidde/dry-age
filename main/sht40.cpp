#include  "sht40.h"

#define SHT40_CMD_MEASURE 0xFD
#define SHT40_BYTES 6
#define SHT40_WAITTIME_MS 20
#define SHT40_MAX_VAL 65535.0f
#define SHT40_TEMP_OFFSET -45.0f
#define SHT40_TEMP_SCALE 175.0f
#define SHT40_HUMIDITY_OFFSET -6.0f
#define SHT40_HUMIDITY_SCALE 125.0f
#define SHT40_HUMIDITY_MIN 0.0f
#define SHT40_HUMIDITY_MAX 100.0f

#define I2C_MASTER_SCL_IO GPIO_NUM_4 
#define I2C_MASTER_SDA_IO GPIO_NUM_5
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TIMEOUT_MS 1000

esp_err_t read_sht40(i2c_master_dev_handle_t dev_handle, sht40_data_t* result){

    if (result == nullptr || dev_handle == nullptr) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t cmd = SHT40_CMD_MEASURE;
    uint8_t data[SHT40_BYTES];
    esp_err_t ret = i2c_master_transmit(dev_handle, &cmd, 1, I2C_MASTER_TIMEOUT_MS);

    if (ret != ESP_OK) {
        return ret;
    }

    vTaskDelay(pdMS_TO_TICKS(SHT40_WAITTIME_MS));

    ret = i2c_master_receive(dev_handle, data, SHT40_BYTES, I2C_MASTER_TIMEOUT_MS);

    if (ret != ESP_OK) {
        return ret;
    }

    // test print to find the temp and humidity in bytes
    // printf("%02X %02X %02X %02X %02X %02X\n", data[0], data[1], data[2], data[3], data[4], data[5]);

    uint16_t raw_temp = ((uint16_t)data[0] << 8) | data[1];
    uint16_t raw_hum  = ((uint16_t)data[3] << 8) | data[4];

    result->temperature = SHT40_TEMP_OFFSET + SHT40_TEMP_SCALE * ((float)raw_temp / SHT40_MAX_VAL);
    result->humidity   = SHT40_HUMIDITY_OFFSET + SHT40_HUMIDITY_SCALE * ((float)raw_hum / SHT40_MAX_VAL);

    if (result->humidity < SHT40_HUMIDITY_MIN) {
        result->humidity = SHT40_HUMIDITY_MIN;
    }
    if (result->humidity > SHT40_HUMIDITY_MAX) {
        result->humidity = SHT40_HUMIDITY_MAX;
    }

    return ESP_OK;
}

void sht40_i2c_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags = {
            .enable_internal_pullup = true,
        },
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, bus_handle));

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SHT40_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*bus_handle, &dev_config, dev_handle));
}