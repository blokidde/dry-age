#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/i2c_master.h"

#define ATOMIZER_GPIO GPIO_NUM_18
#define I2C_MASTER_SCL_IO GPIO_NUM_4 
#define I2C_MASTER_SDA_IO GPIO_NUM_5
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0
#define I2C_MASTER_TIMEOUT_MS 1000

#define SHT40_ADDR 0x44
#define SHT40_CMD_MEASURE 0xFD

static void i2c_master_init(i2c_master_bus_handle_t *bus_handle, i2c_master_dev_handle_t *dev_handle)
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

static void gpio_init_output(gpio_num_t gpio_num)
{
    gpio_config_t io_conf ={
        .pin_bit_mask = (1ULL << gpio_num),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);
}

extern "C" void app_main(void)
{
    // uint8_t data[6];
    // i2c_master_bus_handle_t bus_handle;
    // i2c_master_dev_handle_t dev_handle;
    // i2c_master_init(&bus_handle, &dev_handle);
    // printf("I2C master initialized\n");

    gpio_init_output(ATOMIZER_GPIO);
    printf("GPIO initialized\n");

    // uint8_t cmd = SHT40_CMD_MEASURE;

    for(;;) {
        // ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, &cmd, 1, I2C_MASTER_TIMEOUT_MS));
        // vTaskDelay(pdMS_TO_TICKS(20));

        // ESP_ERROR_CHECK(i2c_master_receive(dev_handle, data, 6, I2C_MASTER_TIMEOUT_MS));

        // // printf("%02X %02X %02X %02X %02X %02X\n", data[0], data[1], data[2], data[3], data[4], data[5]);

        // uint16_t raw_temp = ((uint16_t)data[0] << 8) | data[1];
        // uint16_t raw_hum  = ((uint16_t)data[3] << 8) | data[4];

        // float temperature = -45.0f + 175.0f * ((float)raw_temp / 65535.0f);
        // float humidity   = -6.0f + 125.0f * ((float)raw_hum / 65535.0f);

        // if (humidity < 0.0f) {
        //     humidity = 0.0f;
        // }
        // if (humidity > 100.0f) {
        //     humidity = 100.0f;
        // }

        // printf("Temperature: %.2f C, Humidity: %.2f %%RH\n", temperature, humidity);

        gpio_set_level(ATOMIZER_GPIO, 0);
        printf("Atomizer ON\n");

        vTaskDelay(pdMS_TO_TICKS(10000));

        gpio_set_level(ATOMIZER_GPIO, 1);
        printf("Atomizer OFF\n");

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

    // ledc_timer_config_t ledc_timer = {
    //     .speed_mode = LEDC_LOW_SPEED_MODE,
    //     .duty_resolution = LEDC_TIMER_13_BIT,
    //     .timer_num = LEDC_TIMER_0,
    //     .freq_hz = 5000,
    //     .clk_cfg = LEDC_AUTO_CLK,
    // };

    // ledc_timer_config(&ledc_timer);

    // ledc_channel_config_t ledc_channel = {
    //     .gpio_num = BUZZER_GPIO,
    //     .speed_mode = LEDC_LOW_SPEED_MODE,
    //     .channel = LEDC_CHANNEL_0,
    //     .intr_type = LEDC_INTR_FADE_END,
    //     .timer_sel = LEDC_TIMER_0,
    //     .duty = 0,
    //     .hpoint = 0,
    // };

    // ledc_channel_config(&ledc_channel);

    // ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 3000);

    // for(int i = 1000; i < 6000; i++) {
    //     printf("Setting frequency to %d Hz\n", i);
    //     ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER_0, i);
    //     ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    //     vTaskDelay(10 / portTICK_PERIOD_MS);
    // }

    // ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    // ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);