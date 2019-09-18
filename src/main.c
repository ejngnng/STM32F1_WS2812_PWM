#include "driver/driver_usart1.h"
#include "driver/driver_tick.h"
#include "driver/driver_tim4.h"
#include "driver/driver_tim3.h"
#include "driver/driver_tim2.h"
#include "driver/driver_ws2812.h"
#include "driver/driver_dma1.h"

#define LED_NUMS    3   // 3 leds

int main(){
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    driver_tick_setup();
    driver_usart1_setup();
    driver_timer2_setup();
    driver_dma1_setup();
    // driver_timer3_setup();
    // driver_timer4_setup();
    driver_ws2812_setup(LED_NUMS);
    printf("setup done\n");
    while(1){
		driver_ws2812_set_pixel_rgb(RGB_Red, 0);
		driver_ws2812_set_pixel_rgb(RGB_Black, 1);
		driver_ws2812_set_pixel_rgb(RGB_Black, 2);
		driver_ws2812_show();
		// delay_ms(500);
		// for(uint8_t i=0; i<2; i++){
		// 	driver_ws2812_set_pixel_rgb(RGB_Black, i);
		// }
		// driver_ws2812_show();
        delay_ms(100);
        gpio_toggle(GPIOC, GPIO13);
    }
    return 0;
}