#include "driver_dma1.h"

#if (DEBUG_DMA == 1)
#include "driver_usart1.h"
#endif
void driver_dma1_setup(){
    rcc_periph_clock_enable(RCC_DMA1);

    dma_channel_reset(DMA1,DMA_CHANNEL5);
    dma_set_peripheral_address(DMA1,DMA_CHANNEL5,(uint32_t)&TIM2_CCR1);
    dma_set_read_from_memory(DMA1,DMA_CHANNEL5);
    dma_enable_memory_increment_mode(DMA1,DMA_CHANNEL5);
    dma_set_peripheral_size(DMA1,DMA_CHANNEL5,DMA_CCR_PSIZE_16BIT);
    dma_set_memory_size(DMA1,DMA_CHANNEL5,DMA_CCR_MSIZE_8BIT);
    dma_set_priority(DMA1,DMA_CHANNEL5,DMA_CCR_PL_HIGH);
	dma_enable_transfer_complete_interrupt(DMA1,DMA_CHANNEL5);

	nvic_set_priority(NVIC_DMA1_CHANNEL5_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL5_IRQ);  
}

void driver_tim2ch1_dma1ch5_transmit(uint8_t *tx_buf, int tx_len){
    /* Reset DMA channel */
    dma_disable_channel(DMA1, DMA_CHANNEL5);
    dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t)tx_buf);
    dma_set_number_of_data(DMA1, DMA_CHANNEL5, tx_len);
    dma_enable_channel(DMA1, DMA_CHANNEL5);
    timer_enable_counter(TIM2);
}

void driver_dma_start(){
    dma_enable_channel(DMA1, DMA_CHANNEL5);
}

void driver_dma_stop(){
    dma_disable_channel(DMA1, DMA_CHANNEL5);
}

void dma1_channel5_isr(){
   #if (DEBUG_DMA == 1)
    printf("DMA ch5 isr\n");
   #endif
    if(dma_get_interrupt_flag(DMA1, DMA_CHANNEL5, DMA_TCIF)){
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_TCIF);
        // timer_disable_irq(TIM2, TIM_DIER_CC1DE);
        // driver_dma_stop();
        // timer_disable_oc_output(TIM2, TIM_OC1);
        #if (DEBUG_DMA == 1)
        printf("DMA send complete\n");
        #endif
    }
}