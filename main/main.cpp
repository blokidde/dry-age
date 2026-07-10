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

#define HUMIDITY_ATOMIZER_OFF 75.0f
#define HUMIDITY_ATOMIZER_ON 70.0f
#define TEMPERATURE_RELAIS_ON 13.0f
#define TEMPERATURE_RELAIS_OFF 11.0f

#define FAN_SPEED_IDLE 30
#define FAN_SPEED_ATOMIZER 60
#define FAN_SPEED_COOLING 60

extern "C" void app_main(void)
{
    //init to nullptr so they can be safely used in init functions
    i2c_master_bus_handle_t bus_handle = nullptr;
    i2c_master_dev_handle_t dev_handle = nullptr;

    //data struct to hold the temperature and humidity readings
    sht40_data_t data = {};

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
        // Read temperature and humidity from SHT40 sensor
        esp_err_t ret = read_sht40(dev_handle, &data);
        
        //check if the read was successful and print the values or an error message
        if(ret == ESP_OK) {
            printf("Temperature: %.2f °C, Humidity: %.2f %%\n", data.temperature, data.humidity);

            // Control the relais and atomizer based on the temperature and humidity readings
            if (data.temperature > TEMPERATURE_RELAIS_ON) {
                relais_on();
                printf("Relais ON\n");
            } else if (data.temperature < TEMPERATURE_RELAIS_OFF) {
                relais_off();
                printf("Relais OFF\n");
            }

            if (data.humidity < HUMIDITY_ATOMIZER_ON) {
                atomizer_on();
                printf("Atomizer ON\n");
            } else if (data.humidity > HUMIDITY_ATOMIZER_OFF) {
                atomizer_off();
                printf("Atomizer OFF\n");
            }
        } else {
            printf("Error reading SHT40 sensor: %d\n", ret);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}