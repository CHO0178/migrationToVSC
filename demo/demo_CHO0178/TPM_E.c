/*
TPM(CH31)
	SC
	CNT
	MOD
	CnSC
	CnV
	STATUS
	CONF
*/

#include "soc_def.h"
#include "res_alloc.h"
#include "adc_bm.h"
#include "wdog.h"
#include "MKL25Z4.h"

#define PWM_PERIOD		255ul

void main()
{
	// CZ: nastavte mux pro výstup signálu na BNC konektor J12
	// EN: set multiplexer for output signal to BNC connector J12
TPM0
	// CZ: nastavte modulo hodnotu na PWM_PERIOD (kde vnikne problem?)
	// EN: set modulo value to PWM_PERIOD (where is problem?)

	// CZ: nastavte typ signálu na Edge-aligned PWM, High-true pulses na příslušném kanálu
	// EN: set signal type as Edge-aligned PWM , High-true pulses

	// CZ: nastavte CMOD na (0b01) a delicku hodinoveho signalu na deleni dvemi (0b01)
	// EN: set CMOD to (0b01) and clock signal divider to divide by two (0b01)

	while(1)
	{
		uint16_t pot1Val = adc_bm_read(ADC_BM_MODE_8BIT_SE, ADC_CHAN_POT1);
		uint16_t pot2Val = adc_bm_read(ADC_BM_MODE_8BIT_SE, ADC_CHAN_POT2);
		// CZ: nastavte hodnotu chanel value na hodnoutu získanou z potenciometru (0-255)
		// EN: set value of channel to value received from potentiometer (0-255)

	}
}

	// CZ: otestujte a provedte zmenu pro opravu peaku na osciloskopu při zadani maximalni hodnoty
	// EN: test and fix the peak shown on osciloscope for maximum input from
	// CZ: pridejte dalsi potenciometr na jiný kanal stejneho casovace otestujte vztahy
	// mezi kanaly pri pouziti ruznych nastaveni registru CnSC
	// EN: connect another potentiometer to a different channel of the same
	// timer and test their relationships configured in register CnSC
