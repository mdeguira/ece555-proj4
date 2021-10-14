#include <stdint.h>
#include "ADCCode.h"
#include "tm4c123gh6pm.h"
//ADC init at PE2, 125K samples/sec
void ADC0_InitSWTriggerSeq3_Ch1(void){volatile unsigned long delay;
	
	// All the steps in Init are needed
	
	// 1) activate clock for Port E
  //    allow time for clock to stabilize
  // 2) make PE2 input
  // 3) enable alternate function on PE2
  // 4) disable digital I/O on PE2
  // 5) enable analog function on PE2
  // 6) activate ADC0 
  // 7) configure for 125K 
  // 8) Sequencer 3 is highest priority
  // 9) disable sample sequencer 3
  // 10) seq3 is software trigger
  // 11) channel Ain1 (PE2)
  // 12) no TS0 D0, yes IE0 END0
  // 13) enable sample sequencer 3
	
	SYSCTL_RCGCADC_R 		|= 0x0001;   						// 1) activate ADC0
	while((SYSCTL_RCGCADC_R&0x0001) != 0x0001){};// for stabilization
		
  SYSCTL_RCGCGPIO_R 	|= 0x10;    						// 2) activate clock for Port E
	while((SYSCTL_PRGPIO_R&0x10) != 0x10){};  	//  for stabilization
	
	GPIO_PORTE_DIR_R 		&= ~0x04;    						// 3) make PE4 input
	GPIO_PORTE_AFSEL_R 	|= 0x04;   							// 4) enable alternate function on PE2
	GPIO_PORTE_DEN_R 		&= ~0x04;    						// 5) disable digital I/O on PE2
  GPIO_PORTE_AMSEL_R 	|= 0x04;   							// 6) enable analog functionality on PE2
	
	ADC0_PC_R &= ~0xF;
  ADC0_PC_R |= 0x1;             // 7) configure for 125K samples/sec
	ADC0_SSPRI_R = 0x0123;        // 8) Sequencer 3 is highest priority
	ADC0_ACTSS_R &= ~0x0008;      // 9) disable seq3
	ADC0_EMUX_R &= ~0xF000;       // 10) seq3 is software trigger
	
	ADC0_SSMUX3_R &= ~0x000F;
  ADC0_SSMUX3_R += 1;           // 12) set channel to PE2

	ADC0_SSCTL3_R = 0x0006;       // 13) no TS0 D0, yes IE0 END0
	
		ADC0_IM_R &= ~0x0008;
		
	ADC0_ACTSS_R |= 0x0008;       // 15) enable sample sequencer 3
}


//------------ADC0_InSeq3------------
// Busy-wait analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion

uint32_t ADC0_In(void){  
	uint32_t result;
  // 1) initiate SS3
  // 2) wait for conversion done
  // 3) read result
  // 4) acknowledge completion
  ADC0_PSSI_R = 0x0008; 								// 1) initiate SS3
  while ((ADC0_PSSI_R & 0x08) == 0); 	// 2) wait for conversion done
  result = ADC0_SSFIFO3_R & 0xFFF; 		// 3) read result
  ADC0_ISC_R = 0x0008; 								// 4) acknowledge completion

  return result;

}

