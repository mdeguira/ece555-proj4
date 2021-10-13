#include <stdint.h>


#include "PLL.h"
#include "ADCCode.h"
#include "UART.h"
#include "tm4c123gh6pm.h"

//Global Declarations
unsigned long Size = 2; 			// potentiomter range in cm
unsigned char String[10]; 		// string to output to screen
unsigned long Distance; 			// potentiometer distance in units of 0.001 cm
unsigned long ADCvalue;  			// 12-bit 0 to 4095 sample
unsigned long Flag;     			// 1 means valid Distance, 0 means Distance is empty, A global variable to keep track if Systick is overflow

// Students need to write the function
unsigned long Convert(unsigned long sample);
void SysTick_Init_Interrupts(unsigned long period);
void SysTick_Handler(void);

// Instructor Given Functions declarations
void ConvertDistancetostring(unsigned long n);
	
int main(void){
	PLL_Init();                           // PLL at 50 Mhz, no need to change
	UART_Init();													// UART Init  -  Check IBRD and FBRD
	ADC0_InitSWTriggerSeq3_Ch1();					// ADC initialization PE2/AIN1
	SysTick_Init_Interrupts(2000000);			// Pass the proper value such that we get Interrupt at every 500ms
	
	while(1){
			// is "Flag" set?
			// If yes then disable Flag and Print the Value using UART_printf
			UART_printf(String);Newline();
			
	}
	
}
/*------------Students written Function--------------------*/

//********Convert****************
// Convert a 12-bit binary ADC sample into a 32-bit unsigned
// fixed-point distance (resolution 0.001 cm).  Calibration
// data is gathered using known distances and reading the
// ADC value measured on PE1.  
// Overflow and dropout should be considered 
// Input: sample  12-bit ADC sample
// Output: 32-bit distance (resolution 0.001cm)
unsigned long Convert(unsigned long sample){
	// (samples/4095) * size
	// Multiply above value to convert to fixed value
	// "Size" is global variable, for my case its 2 as the length of the Potentiometer is 2 CM, changed it if required
	
}

// Initialize SysTick interrupts to trigger at 40 Hz, 25 ms
void SysTick_Init_Interrupts(unsigned long period){
	// Initialize SysTick interrupts
	// Input: 32bit desired reload value
	
	// disable systick
	// reload value
	// clear flag
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000; // set priority
	// enable systick
}
// executes every 25 ms, collects a sample, converts and stores in mailbox
void SysTick_Handler(void){ 
	// Reads ADC & store in mailbox w/ flag
	// "Distance" is global varaible
	// Use the handler to read ADC value, then Conver () function and finally converting values using pre-written ConvertDistancetostring
	 
	Flag = 1;           // Setting global Flag when existing
}

/*---------------Instructor Written Function-------------------*/
// Converts ADC input into an ASCII string of the actual distance
// Converts a 32-bit distance into an ASCII string
// Input: 32-bit number to be converted (resolution 0.001cm)
// Output: store the conversion in global variable String[10]
// Fixed format 1 digit, point, 3 digits, space, units, null termination
// Examples
//    4 to "0.004 cm"  
//   31 to "0.031 cm" 
//  102 to "0.102 cm" 
// 2210 to "2.210 cm"
//10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm"
void ConvertDistancetostring(unsigned long n){
	int i;// used in for loops
	
	if(n>9999){ // 10000 to "*.*** cm"
		for(i = 1; i < 5; i++)
			String[i] = '*';
	}
	
	else{ // get digits from least to most significant
		for(i = 4; i > 0; i--){
			String[i] = n % 10 + 0x30;
			n = n / 10;
		}
	}
	
	// Rest of String
	String[0] = String[1];
	String[1] = '.';
	String[5] = ' ';
	String[6] = 'c';
	String[7] = 'm';
	String[8] = ' ';
	String[9] = 0;
}
