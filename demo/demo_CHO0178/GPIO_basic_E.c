#include "MKL25Z4.h"
#include "wdog.h"
#include "littleHelper.h"

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
	PCOR
	PTOR
	PDIR
	PDDR
*/

void exercise1Setup();
void exercise2Setup();
void exercise4Setup();
void exercise2Loop();
void exercise3Loop();
void exercise4Loop();

int main(void)
{
	wdog_init(WDOG_CONF_DIS);

	exercise1Setup();
	exercise4Setup();

	while (1) {
		wdog_refresh();
		exercise4Loop();
	}

	return 0;
}

void exercise1Setup()
{
	// CZ: presmerujte signal z periferie GPIO na prislusny pin cervene diody
	// EN: redirect signal from GPIO peripherals to pin associated with red part
	//	   of RGB diode
	PORTB->PCR[18] |= 1<<8;
	// CZ: nastavte pin cervene led diody na output
	// EN: setup pin of associated with red diode as output
	GPIOB->PDDR |= 1<<18;
	// CZ: zapnete cervenou diodu
	// EN: turn on red diode
	GPIOB->PDOR &=~(1<<18);
}

void exercise2Setup()
{
	// presmerujte signal z periferie GPIO na příslušný pin cervene a zelene diody
	// EN: redirect signal from GPIO peripherals to pin associated with red and
	//	   green part of RGB diode

	// nastavte cervenou a zelenou diodu na vystup
	// GPIOB->PDDR = (1<<18) | (1<<19);

}
void exercise2Loop()
{
	// CZ: blikejte stridave cervenou, zelenou a zadnou diodou
	// EN: bling alternately red, green and none diode
	// *******************************
	// CZ: zapni cervenou diodu
	// EN: turn on red diode

	// CZ: zamestnej procesor
	// EN: utilize processor
	heavyFunction();
	// CZ: zapni zelenou diodu a vypni cervenou
	// EN: turn on greed diode and turn off red diode

	// CZ: zamestnej procesor
	// EN: utilize processor

	// CZ: vypni zelenou diodu
	// EN: turn off green diode

	// CZ: zamestnej procesor
	// EN: utilize processor

}

void exercise3Loop()
{
	// CZ: vytvor semafor:  R -> Y(red&green) -> G -> Y
	// EN: create semaphor: R -> Y(red&green) -> G -> Y
}

void exercise4Setup()
{
	// CZ: presmerujte signal z periferie GPIO na příslušný pin tlacitka
	// EN: redirect signal from GPIO peripherals to pin associated with button 1
	PORTA->PCR[4] |= 1<<8;
}

void exercise4Loop()
{
	// CZ: vlozte hodnotu z tlacitka na diodu
	// EN: move value of button input to diode output
	if(GPIOA->PDIR & (1<<4))
	{
		GPIOB->PDOR |= 1<<18;
	}
	else{
		GPIOB->PDOR &=~(1<<18);
	}
}
