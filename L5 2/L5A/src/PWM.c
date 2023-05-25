#include "PWM.h"

void PWM_Init() {
	// Enable GPIO Port A Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Enable clock for TIM2
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // Configure PA1
    GPIOA->MODER &= ~(GPIO_MODER_MODE1);         // Reset MODER of Port A, Pin 1
    GPIOA->MODER |= GPIO_MODER_MODE1_1;          // Set MODER of Port A, Pin 1 to Alternative Mode
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED1);    // Set OSPEEDR of Port A, Pin 1 to Very High
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD1);         // Reset PUPDR of Port A, Pin 1 to No Pull Up, No Pull Down
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL1);        // Clear AF1 for Port A, Pin 1
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_0;         // Select AF1 (TIM2_CH1) for Port A, Pin 1

    // Configure PWM Output for TIM2 CH1
    TIM2->CCER |= TIM_CCER_CC1E;                 // Enable CH1 for TIM2, not CH1N

    TIM2->CR1 &= ~(TIM_CR1_DIR);                  // [TIM2 CR1] Set the direction to count up.
    TIM2->PSC = 50;                               // Set the prescaler value.
    TIM2->ARR = 4095;                             // Set the auto-reload value.
    TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M);             // Clear the output compare mode bits.
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;              // Set the output compare mode bits to PWM mode 1: 0110.
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_2;
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;               // Enable output preload.
    TIM2->CCER &= ~(TIM_CCER_CC1P);               // Set the output polarity for compare 1 to active high.
    TIM2->CCER |= TIM_CCER_CC1E;                  // Enable the channel 1 output.
    TIM2->CCR1 = 1;                               // [TIM2 CCRx] Set the capture/compare value.

    TIM2->CR1 |= TIM_CR1_CEN;                     // Enable the counter.

}
 