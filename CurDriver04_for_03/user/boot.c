#include "include.h"
#define USER_FLASH_START_OFFSET 0xD000
// #define NVIC_VTOR_MASK 0x1FFFFF80
u32 data_;
#define FLASH_DELIMITER			(0x0800D000)
typedef  void (*pFunction)(void);
uint32_t JumpAddress;
pFunction Jump_To_Application;
	volatile uint32_t NVIC_ISER ;// get value of enable interrupt register
	volatile uint32_t NVIC_ICER ;			// get value of disable interrupt register
	volatile uint32_t NVIC_IABR ;			// get value of active interrupt register
	volatile uint32_t SCB_VTOR;
void NVIC_DeInit(void)
{
  uint8_t tmp;
	for (tmp = 0; tmp < 8; tmp++) 
{
		NVIC->ISER[tmp] = 0x00;
		NVIC->ICER[tmp] = 0x00;
		NVIC->ISPR[tmp] = 0x00;
		NVIC->ICPR[tmp] = 0x00;
		NVIC->IABR[tmp] = 0x00;
}
/* Clear all interrupt priority */
    for (tmp = 0; tmp < 32; tmp++) 
{
      NVIC->IP[tmp] = 0x00;
}

}

void NVIC_SCBDeInit(void)
{
    uint8_t tmp;
	for(tmp = 0; tmp < 8; tmp++) {					// clear pending interrupts 
		NVIC->ICPR[tmp] = 0xFFFFFFF;}		
	for(tmp = 0; tmp < 8; tmp++) {				// disable all interrupts
		NVIC->ICER[tmp] = 0xFFFFFFF;}
    SCB->ICSR = 0x0A000000;
    SCB->VTOR = 0x00000000;
    SCB->AIRCR = 0x05FA0000;
    SCB->SCR = 0x00000000;
    SCB->CCR = 0x00000200;

    for (tmp = 0; tmp < 32; tmp++) {
        SCB->SHP[tmp] = 0x00;
    }

    SCB->SHCSR = 0x00000000; // запретить обработку системных отказов
    //SCB->CFSR = 0xFFFFFFFF;
    SCB->HFSR = 0xFFFFFFFF;	// регистр состояния тяжелого отказа
    //SCB->DFSR = 0xFFFFFFFF;
}

void NVIC_SetVTOR(uint32_t offset)
{
//     SCB->VTOR  = (offset & NVIC_VTOR_MASK);
//     SCB->VTOR  = offset;
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, offset);
}

/*
__asm void boot_jump( uint32_t address )
{
   LDR SP, [R0]         ;Load new stack pointer address
   LDR PC, [R0, #4]     ;Load new program counter address
}
*/
void jump ()
{
				JumpAddress = *(__IO uint32_t*) (FLASH_DELIMITER + 4);
				Jump_To_Application = (pFunction) JumpAddress;      /// Jump to user application 
				__set_MSP(*((__IO uint32_t*) FLASH_DELIMITER));     /// Initialize user application's Stack Pointer 
				Jump_To_Application();				
}

void Disable_peripheral()
{
	 __disable_irq();
		NVIC_DisableIRQ(TIM3_IRQn);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, DISABLE);
		CAN_ITConfig(CAN2, CAN_IT_FMP0, DISABLE);  // CAN2 FIFO0 message pending interrupt enable 
		CAN_ITConfig(CAN2, CAN_IT_FF0, DISABLE);  	// CAN2 FIFO0 full interrupt enable 
		CAN_ITConfig(CAN2, CAN_IT_FMP1, DISABLE);  // CAN2 FIFO1 message pending interrupt enable 
		CAN_ITConfig(CAN2, CAN_IT_FF1, DISABLE);  	// CAN2 FIFO1 full interrupt enable 
		NVIC_DisableIRQ(CAN2_RX0_IRQn);
		NVIC_DisableIRQ(CAN2_RX1_IRQn);
		NVIC_DisableIRQ(CAN2_TX_IRQn);
}
#define bootloader_size							0xD000
#define ApplicationAddress    			0x8000000 + bootloader_size
void reboot(void)
{
	boot_flag = 0;
// 	NVIC_ISER = *(NVIC->ISER);			// get value of enable interrupt register
// 	NVIC_ICER = *(NVIC->ICER);			// get value of disable interrupt register
// 	NVIC_IABR = *(NVIC->IABR);			// get value of active interrupt register
// 	SCB_VTOR =   (SCB->VTOR);
	__set_PRIMASK(1);			// disable all interrupts
// 				// reallocate NVIC
// 				JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
//         Jump_To_Application = (pFunction) JumpAddress;      /* Jump to user application */
//       __set_MSP(*(__IO uint32_t*) ApplicationAddress);     /* Initialize user application's Stack Pointer */
//       Jump_To_Application();
// 			NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xD000);
//  			
	  NVIC_DeInit();
  	NVIC_SCBDeInit();
	  Disable_peripheral();
		NVIC_SystemReset();

}

