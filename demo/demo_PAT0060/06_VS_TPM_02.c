#include "MKL25Z4.h"
#include "wdog.h"
#include "soc_def.h"
#include "res_alloc.h"

//napiste makro pro prioritu preruseni s nazvem TPM0_EXPT_PRI a prioritou 2
//??

//fpwm = (48 MHz / 2) / PWM_PERIOD = 93750 Hz
#define PWM_PERIOD		256ul

//duty cycle is increased with fincr = 50 Hz
//OVF_LIMIT = fpwm / fincr
#define OVF_LIMIT		1875ul

//dopiste makro s nazvem TPM_SC_COMPVAL - SC registr - Enable TOF interrupts; Clock Mode Selection 01; Prescale Divide by 2
//??

uint32_t ovf_count;
uint8_t chan_val;

void __attribute__ ((interrupt)) TPM0_IRQHandler(void)
{	
	// SC registr - Timer Overflow Flag 1 + TPM_SC_COMPVAL
	//??

	ovf_count++;
	if (ovf_count == OVF_LIMIT) {
		ovf_count = 0ul;
		TPM0->CONTROLS[TPMCH_J12].CnV = chan_val++;
	}
}

int main(void)
{
	wdog_init(WDOG_CONF_LPOCLK_1024_CYCLES);
	
	//NVIC Setup
	//adresa a priorita preruseni
	//??
	//povoleni preruseni
	//??
	
	//nastavte PCR pro BNC J12 jako TPM0_CH2
	//??
	
	//TPM setup
	// SC registr - MSB, ELSB - 1
	//??
	// modulo registr - zapiste modulo hodnotu
	//??
	// SC registr - pouzijte vytvorene makro
	//??

	while (1) {
		wdog_refresh();
	}

	return 0;
}