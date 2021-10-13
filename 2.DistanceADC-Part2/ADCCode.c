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
}


//------------ADC0_InSeq3------------
// Busy-wait analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion

uint32_t ADC0_In(void){  uint32_t result;
  // 1) initiate SS3
  // 2) wait for conversion done
  // 3) read result
  // 4) acknowledge completion

  return result;

}

