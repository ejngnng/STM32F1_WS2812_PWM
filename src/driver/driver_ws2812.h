#ifndef DRIVER_WS2812_H
#define DRIVER_WS2812_H

#include <stdint.h>
#include <string.h>
#include "color/color.h"

/*
* WS2812 data frame 24bit
* G7~G0 R7~-R0 B7~B0
*/

#define WS2812_BIT1    0xF8
#define WS2812_BIT0    0xE0


void driver_ws2812_setup(uint8_t nums);

void driver_ws2812_set_pixel_rgb(rgb_t rgb, uint8_t nums);

void driver_ws2812_show();

#endif