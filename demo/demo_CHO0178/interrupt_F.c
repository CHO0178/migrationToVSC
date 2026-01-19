#include "demo_CHO0178/littleHelper.h"
#include "MKL25Z4.h"
#include "wdog.h"
#include "led.h"
#include "btn.h"


/*
pinout(str. 161)

PORT (CH11)
	PCR[32]
		ISF
		IRQC
		MUX
	ISFR

GPIO (CH41)
	PDOR
*/

/*
CZ: postupne spoustejte funkce z main nebo z handleru dle postupu
EN: sequentially execute functions from main or from the handler according to the procedure

// Blocking function = B
// Non blocking function = NB

1) main: B,NB	handler: -
2) main: NB		handler: B
3) main: -		handler: B,NB
4) main: NB		handler: B
5)	CZ: pouzijte spravnou variantu a upravte kod tak, aby fungoval bez pouziti tlacitka 1
	EN: use the correct variant and modify the code to work without using button 1
*/


void blockingFunctionExample();
void nonBlockingFunctionExample();

int main(void)
{
	wdog_init(WDOG_CONF_DIS);
	led_init();
	btn_init();

	// CZ: povol prijem preruseni pro port A a nastav prioritu na 2
	// EN: enable processing of incoming interrupt signal from port A and set
	// priority 2
	NVIC_SetPriority(PORTA_IRQn,2);
	NVIC_EnableIRQ(PORTA_IRQn);

	// CZ: povol generovani preruseni v periferii port A pro sestupnou hranu
	//	signalu tlacitka 1
	// EN: enable generating interrupt signal in port A for falling edge
	// edge of signal button 1
	PORTA->PCR[4] |= 0b1010 << PORT_PCR_IRQC_SHIFT;

	while (1) {
		wdog_refresh();
		// CZ: zavolej funkci
		// EN: call function
		blockingFunctionExample();
	}

	return 0;
}

void PORTA_IRQHandler(void)
{
	// CZ: vynuluj flag
	// EN: reset flag
	PORTA->PCR[4] |= 1 << PORT_PCR_ISF_SHIFT;
	// CZ: zavolej funkci
	// EN: call function
	nonBlockingFunctionExample();
}


void blockingFunctionExample()
{
	// CZ: zamestnej procesor
	// EN: utilize processor
	for(int i = 0;i<1000000;i++){}
	// CZ: zapni diodu 1 a vypni diodu 2
	// EN: turn on diode 1 and turn off diode 2
	GPIOB->PDOR |= 1<<8;
	GPIOB->PDOR &= ~(1<<9);
	// CZ: zamestnej procesor
	// EN: utilize processor
	for(int i = 0;i<1000000;i++){}
	// CZ: zapni diodu 2 a vypni diodu 1
	// EN: turn on diode 2 and turn off diode 1
	GPIOB->PDOR |= 1<<9;
	GPIOB->PDOR &= ~(1<<8);
}

void nonBlockingFunctionExample()
{
	// CZ: pokud je tlacitko 2 sepnute rozsvit diodu 3
	// EN: if button 2 is pushed turn on diode 3
	if(GPIOA->PDIR & (1<<5))
	{
		GPIOB->PDOR |= 1<<10;
	}
	else
	{
		GPIOB->PDOR &= ~(1<<10);
	}
}


