#ifndef DRIVER_DMA1_H
#define DRIVER_DMA1_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/spi.h>

void driver_dma1_setup();

void driver_spi_dma_transmit(uint8_t *tx_buf, int tx_len);

void driver_dma_start();

void driver_dma_stop();

/* DMA Channel3 transmit completed interrupt */
void dma1_channel3_isr();

#endif