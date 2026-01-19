/**
 * @author Ing. Jan Choutka
 * @date 02.05.2024
 * @version 1
 * @brief example code for communication with computer using RS232.
 * Communication on computer side use putty with com speed: 115'200
 *
 */
/*
UART
	S1
		RDRF	//
		TDRE	//
	D			// data
	C2
		TIE		//
		RIE		//
		TE		//
		RE		//
	BDH
		SBR		// upper bits of speed
	BDL
		SBR		// lower bits speed


PORT
	PCR
		MUX


set speed to SBR 13
*/

#include "wdog.h"
#include "MKL25Z4.h"

int main(void)
{
	wdog_init(WDOG_CONF_DIS);
	// enable receiving interrupts
	NVIC_SetPriority(UART1_IRQn,2);
	NVIC_EnableIRQ(UART1_IRQn);

	// initialize rx and tx pins

	// initialize comunication


	while (1) {
		wdog_refresh();
	}
	return 0;
}

void initComunication(){
	// EN: set input multiplexer in port to UART1 peripherals
	PORTC->PCR[3] = 0b11<<8;
	PORTC->PCR[4] = 0b11<<8;

	// EN: allow ENVIC for receiving interrupts form UART1
	NVIC_SetPriority(UART1_IRQn, 2);
	NVIC_EnableIRQ(UART1_IRQn);

	// EN: enable sending interrupt for incoming and finished messages
	UART1->C2 = (UART_C2_RIE_MASK | UART_C2_TE_MASK | UART_C2_RE_MASK);

	// EN: setup speed of communication to 115200Bd
	UART1->BDH = UART_BDH_SBR(13u >> 8u);
	UART1->BDL = UART_BDL_SBR(13u);


}








