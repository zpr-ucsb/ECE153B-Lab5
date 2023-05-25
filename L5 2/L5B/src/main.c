/*
 * ECE 153B - Winter 2023
 *
 * Name(s):
 * Section:
 * Lab: 5B
 */


#include "ADC.h"
#include "DAC.h"
#include "EXTI.h"
#include "PWM.h"
#include "SysClock.h"
#include "stm32l476xx.h"
#include <stdio.h>

int main(void) {
    // Initialization
    System_Clock_Init(); // Switch System Clock = 16 MHz

    ADC_Init();
    DAC_Init();
    EXTI_Init();

    // [TODO] Initialize PWM
    PWM_Init();

    while (1) {
        // [TODO] Trigger ADC and get result
        ADC1->CR |= ADC_CR_ADSTART;

        while ((ADC1->ISR & ADC_CSR_EOC_MST) == 0) {}    // Wait for ADC conversion to complete
        
        res = ADC1->DR;  
        voltage = (res*3.3) / 4096;

        // [TODO] LED behavior based on ADC result
        TIM2->CCR1 = (voltage/3.3) * 4096;
    }
}
