/*
 * main.c
 *
 *  Created on: Apr 18, 2023
 *      Author: hp
 */

#define GPIOB_BASE_ADDR  0x40020400

#define GPIOB_MODER     (*(unsigned long *) (GPIOB_BASE_ADDR + 0x00))
#define GPIOB_OTYPER    (*(unsigned long *) (GPIOB_BASE_ADDR+0x04))
#define GPIOB_ODR       (*(unsigned long *) (GPIOB_BASE_ADDR+ 0x14))

#define RCC_AHB1ENR (*(unsigned long *)(0x40023800+0x30))
#define RCC_CFGR    (*(unsigned long *)((0x40023800) + (0x08UL)))

int main(){

	RCC_CFGR |= (0x0A << 4);
    RCC_AHB1ENR |= (1<<1);

    unsigned char mode_pin_gpio =1;

    GPIOB_MODER  &= ~(0x03<<(3*2)); // clear pin 3
    GPIOB_MODER  |= mode_pin_gpio << (3*2); // set 2 bits of pin3 by 01 output mode
    // GPIOB_OTYPER |= 0x01 <<(3); // set bit 3 to make it open drain
    GPIOB_OTYPER &= ~(1 <<(3)); // clear bit 3 to make it push-pull

	unsigned long  i;
	GPIOB_ODR |= (1<<3);

    while(1){
    	GPIOB_ODR |= (1<<3);

    	for(i=0;i<1000000;i++);

    	GPIOB_ODR &= ~(1<<3);

    	for(i=0;i<1000000;i++);
    }

    return 0;
}

