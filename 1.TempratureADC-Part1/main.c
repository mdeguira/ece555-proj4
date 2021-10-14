// Date Created: 11/03/2013 
// Original Author: Chris Mitchell (cpmitc4@gmail.com)
//
// Brief description of the program:
// This lab demonstrates a simple enviornmental monitoring unit.  This 
// program will read the internal analog temperature sensor on the TivaWare
// Launchpad development board through the onboard ADC.  The temperature will
// then be converted to Celsius and Farenheit and printed to the console.  
  
//
// The following UART signals are configured only for displaying console
// messages for this example.  These are not required for operation of the
// ADC.
// - UART0 peripheral
// - GPIO Port A peripheral (for UART0 pins)
// - UART0RX - PA0
// - UART0TX - PA1
//
//
// NOTE: The internal temperature sensor is not calibrated.  This example
// just takes the raw temperature sensor sample and converts it using the
// equation found in the datasheet.
//
//*****************************************************************************

//Kat was here
//Includes
#include <stdbool.h>
#include <stdint.h>



#include "ADCCode.h"
#include "UART.h"
#include "tm4c123gh6pm.h"


//Student Written Functions

uint32_t Get_TempC(void);
uint32_t Convert_Raw_To_V(uint32_t raw);
uint32_t Convert_V_To_C(uint32_t v);
uint32_t Convert_C_To_F ( uint32_t TempC);
//test

int main(void)
{
		unsigned char keystroke; 			// Variable to note key-pressed
		unsigned long val;						// Get Temp Here
	
		UART_Init(); 									// Init UART0 at 16M, 9600 baud 
	  ADC0_Temp_Init();							// Initialize ADC0 to take temperature readings
		
    UART_printf("Initialization Complete..."); Newline();
		UART_printf("Press C/c for Celsius or F/f for Fahrenhit"); Newline(); Newline();
    // Continually read and display the temperature
    while(1)
    {	
				// Wait for user to enter a key
				keystroke = Getchar();
				if (keystroke == 'c' || keystroke == 'C') {
					val = (unsigned long)Get_TempC;
					UART_OutUDec(val);
					Newline(); Newline();
				}
				else if (keystroke == 'f' || keystroke == 'F') {
					val = (unsigned long)Get_TempC;
					UART_OutUDec(Convert_C_To_F(val));
					Newline(); Newline();
				}
				else { 
					UART_printf("Press C/c for Celsius or F/f for Fahrenhit"); Newline(); Newline();
				}
    }
}


/*
 *  NOTE: You need to complete the following functions
 */



// Returns the temperature in Celsius
// You should call ADC0_In, convertRawToVolts(), and convertVoltsToCelsius()
uint32_t Get_TempC(void){
	int i;
	uint32_t result=0;
	
	// Read raw result from ADC0
	// Try averaging multiple readings together to get more stable outputs
	// Your code should come beneath 
	for (int i = 0; i < 20; i++) {
		result += ADC0_In();
	}
	result /= 20;
	
	//Hard code ADC output as 1746 to generate 42C
	//result = 1746;       // Comment this line once you add your Averaging routine above
	
	// Convert raw ADC value to millivolts
	result = Convert_Raw_To_V(result);
	
	// Convert voltage to Celsius
	result = Convert_V_To_C(result);
	
	// Return temperature in Celsius
	return result;
}

uint32_t Convert_Raw_To_V(uint32_t raw){
	uint32_t result;
	
	// Convert raw ADC value t o mV. 
	// voltage = max_possible_voltage * ADC_result / max_possible_ADC_value
	// result = voltage;
	result = 3300 * raw / 4095;
	
	
	return result;
}
// Convert temperature from millivolts to Celsius
uint32_t Convert_V_To_C(uint32_t v){
	uint32_t result;
	
	/*
	 * Equation derived from pg. 812 of the "Tiva™ TM4C123GH6PM 
	 * Microcontroller Data Sheet" (available online)
   *
	 * Voltage (mV) / 1000 = 2.7 - ((TempC + 55)/75)
	 */
	result = (2.7 - (v / 1000)) * 75 - 55;
	
	return result;
}

// Convert a temperature from Celsius to Fahrenheit
uint32_t Convert_C_To_F( uint32_t TempC)
{
	uint32_t TempF;
	
	// complete this equation
	// T in F = 32 + (T in C *1.8) 
  TempF = 32 + (TempC * 1.8);
	
	return TempF;
}
