#include "driver_tim3.h"

/* 
 *
 * | TIMx | CH1 | CH2 | CH3 | CH4 |
 * | TIM1 | PA8 | PA9 | PA10| PA11|
 * | TIM2 | PA0 | PA1 | PA2 | PA3 |
 * | TIM3 | PA6 | PA7 | PB0 | PB1 |
 * | TIM4 | PB6 | PB7 | PB8 | PB9 |
 *  
 */

// TIM3 CH2 PA7 drive WS2812
void driver_timer3_setup(){
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM3);
    rcc_periph_clock_enable(RCC_AFIO);

    /**
     * 
     * PA6 == TIM3 CH1
     * PA7 == TIM3 CH2
     * PB0 == TIM3 CH3
     * PB1 == TIM3 CH4
     * 
     **/

    gpio_set_mode(
        GPIOA,
        GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
        GPIO7
    );

    timer_disable_counter(TIM3);
    timer_reset(TIM3);

    timer_set_mode(
        TIM3,
        TIM_CR1_CKD_CK_INT,
        TIM_CR1_CMS_EDGE,
        TIM_CR1_DIR_UP
    );

    timer_set_prescaler(TIM3, 72000000/24000000 - 1);
    timer_enable_preload(TIM3);
    timer_set_period(TIM3, 29); // pwm frequency 72M/(ARR+1) *(PSC+1) Hz
    timer_continuous_mode(TIM3);

    timer_disable_oc_output(TIM3, TIM_OC2);
    timer_set_oc_mode(TIM3, TIM_OC2, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM3, TIM_OC2);
    timer_enable_oc_output(TIM3, TIM_OC2);
    timer_set_oc_value(TIM3, TIM_OC2, 0);  // pwm duty cycle  CCR1/ARR * 100%
    timer_enable_counter(TIM3);
    timer_enable_irq(TIM3, TIM_DIER_CC2DE); // enable timer3 CCR3 DMA reqeuest
}