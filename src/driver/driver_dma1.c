#include "driver_dma1.h"

#if (DEBUG_DMA == 1)
#include "driver_usart1.h"
#endif
void driver_dma1_setup(){
    rcc_periph_clock_enable(RCC_DMA1);

    dma_channel_reset(DMA1,DMA_CHANNEL3);
    dma_set_peripheral_address(DMA1,DMA_CHANNEL3,(uint32_t)&SPI1_DR);
    dma_set_read_from_memory(DMA1,DMA_CHANNEL3);
    dma_enable_memory_increment_mode(DMA1,DMA_CHANNEL3);
    dma_set_peripheral_size(DMA1,DMA_CHANNEL3,DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1,DMA_CHANNEL3,DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1,DMA_CHANNEL3,DMA_CCR_PL_HIGH);
	dma_enable_transfer_complete_interrupt(DMA1,DMA_CHANNEL3);
	/* SPI1 TX on DMA1 Channel 3 */
	nvic_set_priority(NVIC_DMA1_CHANNEL3_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL3_IRQ);  
}

void driver_spi_dma_transmit(uint8_t *tx_buf, int tx_len){
    /* Reset DMA channel */
    dma_disable_channel(DMA1, DMA_CHANNEL3);
    dma_set_memory_address(DMA1, DMA_CHANNEL3, (uint32_t)tx_buf);
    dma_set_number_of_data(DMA1, DMA_CHANNEL3, tx_len);
    dma_enable_channel(DMA1, DMA_CHANNEL3);
    spi_enable_tx_dma(SPI1);
    spi_enable(SPI1);
}

void driver_dma_start(){
    dma_enable_channel(DMA1, DMA_CHANNEL3);
}

void driver_dma_stop(){
    dma_disable_channel(DMA1, DMA_CHANNEL3);
}

void dma1_channel3_isr(){
    #if (DEBUG_DMA == 1)
    printf("dma ch3 isr\n");
    #endif
    if(dma_get_interrupt_flag(DMA1, DMA_CHANNEL3, DMA_TCIF)){
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL3, DMA_TCIF);
        spi_disable_tx_dma(SPI1);
        #if (DEBUG_DMA == 1)
        printf("DMA send complete\n");
        #endif
    }
}