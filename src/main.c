#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"

void pwm_wave(float duty_ratio, uint motor_pin)
{
    while (true) {
        gpio_out(motor_pin, 1)
        vTaskDelay(100*(1-duty_ratio));
        gpio_out(motor_pin, 0)
        vTaskDelay(100*duty_ratio)
    }
}

void led_task()
{   
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(100);
        gpio_put(LED_PIN, 0);
        vTaskDelay(100);
    }
}

void motor_task(uint motor_pin)
{
    
    gpio_init(motor_pin);
    gpio_set_dir(motor_pin, GPIO_OUT);
    pwm_wave(0.4, motor_pin);
}

int main()
{
    stdio_init_all();

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(motor_task, "MOTOR_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}