#include <stdint.h>
#include "ADCCode.h"
#include "tm4c123gh6pm.h"
// Configure ADC0 to read at 500K sample/Sec
void ADC0_Temp_Init(void){volatile uint32_t delay;
	
	 /*
	 // We do not need to initialize a GPIO pin since we are measuring temperature
	  
    SYSCTL_RCGCGPIO_R |= 0x10;    // 1) activate clock for Port E and allow time to stabilize
	  while((SYSCTL_RCGCGPIO_R & 0x10)==0){}	
    GPIO_PORTE_DIR_R &= ~0x10;  // 2) make PE4 input
    GPIO_PORTE_AFSEL_R |= 0x10; // 3) enable alternate function on PE4
    GPIO_PORTE_DEN_R &= ~0x10;  // 4) disable digital I/O on PE4
    GPIO_PORTE_AMSEL_R |= 0x10; // 5) enable analog functionality on PE4
	  */
		
	
	SYSCTL_RCGCADC_R |= 0x0001;   // 6) activate ADC0 and allow time to stabilize
	while((SYSCTL_RCGCADC_R&0x1)!=0x01){}
	
		
	// Write proper value here
	ADC0_PC_R &= ~0xF;
  ADC0_PC_R |= 0x2;             // 7) configure for 500K samples/sec
		
	
  ADC0_SSPRI_R = 0x0123;        // 8) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x8;      		// 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;       // 10) seq3 is software trigger
	
	/*
	  // No need to choose a channel since we are measuring temperature
    
		ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R += 9;           // 11) set channel
	 
		*/
			
	ADC0_SSCTL3_R = 0x000E;			// // 12) no D0, yes TS0 IE0 END0
  ADC0_ACTSS_R |= 0x0008;       // 13) enable sample sequencer 3 before we sample.
}





//------------ADC0_InSeq3------------
// Busy-wait analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion

uint32_t ADC0_In(void){  uint32_t result;
  ADC0_PSSI_R = 0x08; // 1) initiate SS3
  while ((ADC0_PSSI_R & 0x08) == 0); // 2) wait for conversion done
  result = ADC0_SSFIFO3_R & 0xFFF; // 3) read result
  ADC0_ISC_R = 0x0008; // 4) acknowledge completion

  return result;

}
