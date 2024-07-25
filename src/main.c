#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "pico/stdlib.h"

#define forward (1<<0)  //00000000 00000000 00000001代表前进
#define backward (1<<1) //00000000 00000000 00000010代表后退
#define left (1<<2)     //00000000 00000000 00000100代表左转（同时前进和左转是不被允许的）
#define right (1<<3)    //00000000 00000000 00001000代表右转（要求同上）
#define stop (1<<4)     //00000000 00000000 00010000代表停止移动（可以同时改变深度）
#define down (1<<5)     //00000000 00000000 00100000代表上浮（可同时移动）
#define up (1<<6)       //00000000 00000000 01000000代表下潜（要求同上）

EventGroupHandle_t control_group;
typedef struct Motor{
    uint pin1,pin2;
    uint loc;   //0代表左电机，1代表右电机
} Motor;
uint motor_pin[6]={2,3,5,6};
uint pump_pin[2]={8,9};
void motor(void *motor_);
void init();
int main()
{
    stdio_init_all();
    Motor motors[2];
    for(int i=0;i<=2;i++){
        gpio_set_dir(motor_pin[i],GPIO_OUT);
        gpio_set_dir(motor_pin[i+1],GPIO_OUT);
        motors[i].pin1 = motor_pin[i];
        motors[i].pin2 = motor_pin[i+1];
    }
    motors[0].loc = 0;
    motors[1].loc = 1;

    control_group = xEventGroupCreate();
    // xTaskCreate(
    //     motor,
    //     'motor_left',

    // );
    // xTaskCreate(
    //     motor,
    //     'motor_right',

    // );
}
void motor(void *motor_){
    Motor *m;
    m=(Motor*) motor_;
    while (1)
    {
        EventBits_t control_bits = xEventGroupGetBits(control_group);
        if(control_bits&forward){
            gpio_put(m->pin1,1);
            gpio_put(m->pin2,0);
        }
        if(control_bits&backward){
            gpio_put(m->pin1, 0);
            gpio_put(m->pin2, 1);
        }
        if(control_bits&left){
            if(m->loc==0){
                gpio_put(m->pin1, 0);
                gpio_put(m->pin2, 0);
            }
            if(m->loc==1){
                gpio_put(m->pin1, 1);
                gpio_put(m->pin2, 0);                
            }
        }
        if(control_bits&right){
            if(m->loc==0){
                gpio_put(m->pin1, 1);
                gpio_put(m->pin2, 0);
            }
            if(m->loc==1){
                gpio_put(m->pin1, 0);
                gpio_put(m->pin2, 0);                
            }
        }
    }
    
}
