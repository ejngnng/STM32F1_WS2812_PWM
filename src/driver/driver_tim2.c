#include "driver_tim2.h"
#include "driver_usart1.h"

/* 
 *
 * | TIMx | CH1 | CH2 | CH3 | CH4 |
 * | TIM1 | PA8 | PA9 | PA10| PA11|
 * | TIM2 | PA0 | PA1 | PA2 | PA3 |
 * | TIM3 | PA6 | PA7 | PB0 | PB1 |
 * | TIM4 | PB6 | PB7 | PB8 | PB9 |
 *  
 */

static uint8_t led_buffer[24] = {
  //  0,0,0,0,0,0,0,0,
    9,9,9,9,9,9,9,9, 
    19,19,19,19,19,19,19,19,
    9,9,9,9,9,9,9,9,
};

// TIM2 CH1 PA0 drive WS2812
void driver_timer2_setup(){
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(
        GPIOA,
        GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
        GPIO0  // TIM2--CH1
    );

    timer_disable_counter(TIM2);
    timer_reset(TIM2);

    timer_set_mode(
        TIM2,
        TIM_CR1_CKD_CK_INT,
        TIM_CR1_CMS_EDGE,
        TIM_CR1_DIR_UP
    );

    timer_set_prescaler(TIM2, 72000000/24000000 - 1);
    timer_enable_preload(TIM2);
    timer_set_period(TIM2, 29); // pwm frequency 72M/(ARR+1) *(PSC+1) Hz
    timer_continuous_mode(TIM2);

    timer_disable_oc_output(TIM2, TIM_OC1);
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM2, TIM_OC1);
    timer_enable_oc_output(TIM2, TIM_OC1);
    timer_set_oc_value(TIM2, TIM_OC1, 0);  // pwm duty cycle  CCR1/ARR * 100%
    timer_enable_counter(TIM2);
    // nvic_enable_irq(NVIC_TIM2_IRQ);
    // timer_enable_irq(TIM2, TIM_DIER_CC1IE); // enable timer2 CCR1 isr
    timer_enable_irq(TIM2, TIM_DIER_CC1DE); // enable timer2 CCR1 DMA request
}
uint8_t i=0;
void tim2_isr(){
    printf("timer2 isr\n");
    if(timer_get_flag(TIM2, TIM_SR_CC1IF)){
        timer_clear_flag(TIM2, TIM_SR_CC1IF);
        #if (DEBUG==1)
            printf("timer2 CCR1 isr\n");
        #endif  
        // timer_enable_irq(TIM2, TIM_DIER_CC1DE);
        timer_set_oc_value(TIM2, TIM_OC1, (uint8_t)led_buffer[i++]);
        if(i>=24){
            i=0;
        }
    }
}