/**
 * @brief lesson: Low power timer used to blink diode by polling
 * @author Ing. Jan Choutka
 * @date 24.04.2024
 * @version 1
 */
/*
LPTMR(CH33)
	CSR 			// register for interrupt setup
	PSR
		PRESCALE	// delicka signalu
		PCS			//
					// pg.90
	CMR				// compare
	CNR				// counter

PORT
	PCR
		MUX			// multiplexer
*/

#include "MKL25Z4.h"

#include "wdog.h"
#include "led.h"

void tmrDelay();
void setupTimerFor1sDelay();

#define DELAY_PERIOD		15625ul

int main(void)
{
	static uint8_t swCounter = 0u;

	wdog_init(WDOG_CONF_LPOCLK_1024_CYCLES);

	led_init();
	setupTimerFor1sDelay();


	while (1) {
		tmrDelay();
		led_bindisp(++swCounter);

		wdog_refresh();
	}

	return 0;
}

/**
 * @brief setup timer LPTMR0 for waiting 1s and then rise flag
 */
void setupTimerFor1sDelay()
{
	// CZ: nastavete vsechny hodnoty registru CSR na 0 (vypnuti casovace)


	// CZ: nastavte delicku casovace na deleni 256 a clock select na zdroj hodinoveho signalu 3


	// CZ: nastavte modulo hodnotu takovou aby byl vyvolan interrupt kazdou 1s
	//		frekvence tohoto zdroje pocitejte 4MHz

}

/**
 * @brief using LPTMR0 to stop the program for previously defined time
 * then remove flag and stop timer
 */
void tmrDelay()
{
	// CZ: povolte spusteni casovace


	// CZ: cekej dokud se neobjevi flag


	// CZ: vynuluj priznak preruseni


	// CZ: vypnete casovac


}
