#include "fan.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define FAN_GPIO GPIO_NUM_21 //placeholder, fan gpio not chosen yet

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT
#define LEDC_DUTY               (8191) // 2^13 - 1, maximum duty for 13-bit resolution
#define LEDC_CLK_SRC            LEDC_AUTO_CLK
#define LEDC_FREQUENCY          (4000)

void fan_pwm_init()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_CLK_SRC,
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num = FAN_GPIO,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0, // Set duty to 0
        .hpoint = 0,
    };
    ledc_channel_config(&ledc_channel);
}

void fan_set_speed(int speed_percentage)
{
    if speed_percentage < 0) {
        speed_percentage = 0;
    } else if (speed_percentage > 100) {
        speed_percentage = 100;
    }
    int duty_cycle = (speed_percentage * LEDC_DUTY) / 100;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty_cycle);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}
