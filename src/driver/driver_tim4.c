#include "driver_tim4.h"

/* 
 *
 * | TIMx | CH1 | CH2 | CH3 | CH4 |
 * | TIM1 | PA8 | PA9 | PA10| PA11|
 * | TIM2 | PA0 | PA1 | PA2 | PA3 |
 * | TIM3 | PA6 | PA7 | PB0 | PB1 |
 * | TIM4 | PB6 | PB7 | PB8 | PB9 |
 *  
 */

// TIM4 CH1 PB6 drive WS2812
void driver_timer4_setup(){
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_TIM4);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(
        GPIOB,
        GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
        GPIO6  // TIM4--CH1
    );

    timer_disable_counter(TIM4);
    timer_reset(TIM4);

    timer_set_mode(
        TIM4,
        TIM_CR1_CKD_CK_INT,
        TIM_CR1_CMS_EDGE,
        TIM_CR1_DIR_UP
    );

    timer_set_prescaler(TIM4, 36000000/24000000 - 1);
    timer_enable_preload(TIM4);
    timer_set_period(TIM4, 90-1); // pwm frequency 72M/(ARR+1) *(PSC+1) Hz
    timer_continuous_mode(TIM4);

    timer_disable_oc_output(TIM4, TIM_OC1);
    timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM4, TIM_OC1);
    timer_enable_oc_output(TIM4, TIM_OC1);
    timer_set_oc_value(TIM4, TIM_OC1, 89-26);  // pwm duty cycle  CCR1/ARR * 100%
    timer_enable_counter(TIM4); 
}

