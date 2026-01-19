/*

PIT(ch32)
	MCR
		MDIS
		FRZ				freeze in debug (1-allow freeze)
	LTMR64H
	LTMR64H
	LDVAL				load value
	TCTRL
	TFLG				flag

*/

//include libraries
#include "MKL25Z4.h"
#include "led.h"
#include "wdog.h"

int main(void)
{
	wdog_init(WDOG_CONF_LPOCLK_1024_CYCLES);
	//(0) inicializujte diody

	//(0) nastavte zastaveni v debug

	//(0) nastavte modulo pro obnovovani na 1.5s (LDVAL, busFrequency 24MHz)

	//(0) povolte casovac PIT a generovani interruptu (TCTRL)

	//(0) povolte v prijem preruseni v periferii NVIC


	//(1) nastavte druhy kanal na periodu blikani diodou 2s


	//(2) nastavte cas systicku na 0.5s




	while (1) {

		wdog_refresh();
	}

	return 0;
}


//(0) vytvorte interrupt handler pro casovac PIT
//(0) preklopte hodnotu diodu 0
//(1) podle zdroje preklopte diodu 0 nebo 1 nebo 0 i 1 zaroven



//(2) vytvorte handler pro preruseni ze systicku a prepinejte ledku 2

