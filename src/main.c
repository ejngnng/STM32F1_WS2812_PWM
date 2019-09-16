#include "driver/driver_usart1.h"
#include "driver/driver_tick.h"
#include "driver/driver_tim4.h"
#include "driver/driver_tim3.h"
#include "driver/driver_tim2.h"


int main(){
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    driver_tick_setup();
    driver_usart1_setup();
    driver_timer2_setup();
    driver_timer3_setup();
    driver_timer4_setup();
    printf("setup done\n");
    while(1){
        // timer_disable_oc_output(TIM2, TIM_OC1);
        // timer_disable_oc_output(TIM3, TIM_OC2);
        // timer_disable_oc_output(TIM4, TIM_OC1);
        // timer_set_oc_value(TIM2, TIM_OC1, 0);
        // timer_set_oc_value(TIM3, TIM_OC2, 0);
        // timer_set_oc_value(TIM4, TIM_OC1, 0);
        delay_ms(100);
        gpio_toggle(GPIOC, GPIO13);
        // timer_enable_oc_output(TIM2, TIM_OC1);
        // timer_enable_oc_output(TIM3, TIM_OC2);
        // timer_enable_oc_output(TIM3, TIM_OC1);
        // timer_set_oc_value(TIM2, TIM_OC1, 26);
        // timer_set_oc_value(TIM3, TIM_OC2, 26);
        // timer_set_oc_value(TIM4, TIM_OC1, 26);
        // delay_ms(300);
    }
    return 0;
}