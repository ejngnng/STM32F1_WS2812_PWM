#ifndef DRIVER_USART1_H
#define DRIVER_USART1_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void driver_usart1_setup();

int _write(int file, char *ptr, int len);

#endif