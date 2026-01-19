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
		PCS			// zdroj hodinoveho signalu
					// pg.90
	CMR				// compare
	CNR				// counter modulo

PORT
	PCR
		MUX			// multiplexer
*/

#include "MKL25Z4.h"

#include "wdog.h"
#include "led.h"

void tmrDelay();
void setupTimerFor1sDelay();

#define DISP_PERIOD		15625ul

int main(void)
{
	static uint8_t swCounter = 0u;

	wdog_init(WDOG_CONF_DIS);  // <-- must be disabled

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
	LPTMR0->CSR = 0ul;

	// CZ: nastavte delicku casovace na deleni 256 a clock select na zdroj hodinoveho signalu 3
	LPTMR0->PSR = 0b0111<<3 | 3;

	// CZ: nastavte modulo hodnotu takovou aby byl vyvolan interrupt kazdou 1s
	//		frekvence tohoto zdroje pocitejte 4MHz
	LPTMR0->CMR = DISP_PERIOD - 1u;
}

/**
 * @brief using LPTMR0 to stop the program for previously defined time
 * then remove flag and stop timer
 */
void tmrDelay()
{
	// CZ: povolte spusteni casovace
	LPTMR0->CSR |= 1;

	// CZ: cekej dokud se neobjevi flag
	while(!(LPTMR0->CSR & LPTMR_CSR_TCF_MASK)){}

	// CZ: vynuluj priznak preruseni
	LPTMR0->CSR = 1<<7;

	// CZ: vypnete casovac
	LPTMR0->CSR &= ~1;

}
