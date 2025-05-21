#define SW1 (GPIOC->IDR)&(1<<0)  
#define SW2 (GPIOC->IDR)&(1<<1)   
#define SW3 (GPIOC->IDR)&(1<<2)
#define SW4 (GPIOC->IDR)&(1<<3)
#define SW5 (GPIOC->IDR)&(1<<4)  
#define SW6 (GPIOC->IDR)&(1<<5)   
#define PWR_EN (GPIOC->IDR)&(1<<6)
#define SW8 (GPIOC->IDR)&(1<<7)

#define SW13     (GPIOC->IDR)&(1<<10)  
#define S_MASTER (GPIOC->IDR)&(1<<11)   
#define SW_TEST  (GPIOC->IDR)&(1<<12)
#define SW_AUTO  (GPIOC->IDR)&(1<<13)

#define ENC_BUTTON  (GPIOA->IDR)&(1<<10)

#define SET_VOFF_OUT_PORT GPIOB->ODR |=  (1<<14)  
#define CLR_VOFF_OUT_PORT GPIOB->ODR &=  ~(1<<14)

#define SET_STB_OUT_PORT GPIOB->ODR |=  (1<<13)   
#define CLR_STB_OUT_PORT GPIOB->ODR &=  ~(1<<13)

#define SET_ERR_OUT_PORT GPIOB->ODR |=  (1<<15)
#define CLR_ERR_OUT_PORT GPIOB->ODR &=  ~(1<<15)





void PortsInit(void);

