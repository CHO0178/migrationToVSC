/**
 * @brief lesson: digital to analog converter
 * try to generate periodically 3 states of value
 * 0V;(3.3/2)V;3.3V. Try to measure this on oscilloscope
 * generate sinusoidal signal to one of BNC connector
 * and measure it by oscilloscope.
 * @author Ing. Jan Choutka
 * @date 12.11.2024
 * @version 1
 */

#include "MKL25Z4.h"

void initDAC();

/*
DAC(ch.30)
	DAT				// analog value of base voltage in DAT multiples

	C0
		DACEN 		// DAC Enable
		DACRFS		// select reference voltage
		DACTRGSEL	// select trigger type
		DACSWTRG	// SW trigger

PORT
	PCR
		MUX		// multiplexer
*/

int main(void)
{

	while(1)
	{
		// CZ: nastavte vystupni napeti na 0V
		DAC0->DAT[0].DATL = 0;
		DAC0->DAT[0].DATH = 0;

		// CZ: zamestnejte procesor

		// CZ: nastavte vystupni napeti na (3.3/2)V
		DAC0->DAT
		// CZ: zamestnejte procesor

		// CZ: nastavte vystupni napeti na 3.3V

		// CZ: zamestnejte procesor
	}
}

void initDAC()
{
	// CZ: nastavte napetovou referenci na DACREF_1 a typ trigru na SW
	// EN: set reference voltage to DACREF_1 and trigger type to SW
	DAC0->C0 |= 1 << 5;

	// CZ: povolte vyuziti DAC
	DAC0->C0 |= 1 << 7;

}

