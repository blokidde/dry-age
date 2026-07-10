#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/i2c_master.h"

#include "app_gpio.h"
#include "atomizer.h"
#include "sht40.h"
#include "relais.h"
#include "fan.h"

extern "C" void app_main(void)
{
    //init to nullptr so they can be safely used in init functions
    i2c_master_bus_handle_t bus_handle = nullptr;
    i2c_master_dev_handle_t dev_handle = nullptr;

    sht40_i2c_init(&bus_handle, &dev_handle);
    printf("I2C master initialized\n");

    //init gpio for atomizer
    atomizer_init();    
    printf("GPIO for atomizer initialized\n");

    relais_init();
    printf("GPIO for relais initialized\n");

    fan_pwm_init();
    printf("PWM for fan initialized\n");
    
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