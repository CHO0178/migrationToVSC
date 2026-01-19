#include "MKL25Z4.h"
#include "wdog.h"
#include "soc_def.h"
#include "res_alloc.h"
#include "adc_bm.h"

//fpwm = (48 MHz / 2) / PWM_PERIOD = 94118 Hz
#define PWM_PERIOD		255ul

int main(void)
{
	wdog_init(WDOG_CONF_LPOCLK_1024_CYCLES);

	//nastavte PCR pro BNC J12 jako TPM0_CH2
	//??

	//TPM setup
	//CnSC registr - MSB a ELSB bit na 1
	??
	// modulo registr - zapiste modulo hodnotu
	??
	// SC registr - clock mode selection 01 a divide by 2
	??

	while (1) {
		TPM0->CONTROLS[TPMCH_J12].CnV = adc_bm_read(ADC_BM_MODE_8BIT_SE, ADC_CHAN_POT1);
		wdog_refresh();
	}

	return 0;
}
