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

/* CZ: cviceni:
 * EN: exercizes:

	setup: 1 loop: -
	setup: 2 loop: -
	setup: 2 loop: 2
	setup: 2 loop: 3
	setup: 4 loop: 4

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

	while (1) {
		wdog_refresh();
	}

	return 0;
}

void exercise1Setup()
{
	// CZ: presmerujte signal z periferie GPIO na prislusny pin cervene diody
	// EN: redirect signal from GPIO peripherals to pin associated with red part
	//	   of RGB diode
	PORTB->PCR[18] |= 1 << PORT_PCR_MUX_SHIFT;
	// CZ: nastavte pin cervene led diody na output
	// EN: setup pin of associated with red diode as output
	GPIOB->PDDR |= 1 << 18;
	// CZ: zapnete cervenou diodu
	// EN: turn on red diode
	GPIOB->PDOR &= ~(1 << 18);  // log. 0 0V dovoli protekat proudu skrze diodu viz datasheet
}

void exercise2Setup()
{
	// presmerujte signal z periferie GPIO na příslušný pin cervene a zelene diody
	// EN: redirect signal from GPIO peripherals to pin associated with red and
	//	   green part of RGB diode
	PORTB->PCR[18] |= 1 << PORT_PCR_MUX_SHIFT;
	PORTB->PCR[19] |= PORT_PCR_MUX(1);
	// nastavte cervenou a zelenou diodu na vystup
	// GPIOB->PDDR = (1<<18) | (1<<19);
	GPIOB->PDDR |= (1 << 18) | (1 << 19);



}
void exercise2Loop()
{
	// CZ: blikejte stridave cervenou, zelenou a zadnou diodou
	// EN: bling alternately red, green and none diode
	// *******************************
	// CZ: zapni cervenou diodu
	// EN: turn on red diode
	GPIOB->PDOR = 1 << 19;   //nastaveni zelene na log. 1 (3,3V) zamezi proudu diodou
	// CZ: zamestnej procesor
	// EN: utilize processor
	for(int i = 0;i < 2000000; i++){}
	// CZ: zapni zelenou diodu a vypni cervenou
	// EN: turn on greed diode and turn off red diode
	GPIOB->PDOR = 1 << 18;
	// CZ: zamestnej procesor
	// EN: utilize processor
	for(int i = 0;i < 2000000; i++){}
	// CZ: vypni zelenou diodu
	// EN: turn off green diode
	GPIOB->PDOR = 0;
	// CZ: zamestnej procesor
	// EN: utilize processor
	for(int i = 0;i < 2000000; i++){}
}

void exercise3Loop()
{
	// CZ: vytvor semafor:  R -> Y(red&green) -> G -> Y
		// EN: create semaphor: R -> Y(red&green) -> G -> Y
	GPIOB->PDOR |= 1 << 19;
	heavyFunction();
	GPIOB->PDOR = 0;
	heavyFunction();
	GPIOB->PDOR = 1 << 18;
	heavyFunction();
	GPIOB->PDOR = 0;
	heavyFunction();
}

void exercise4Setup()
{
	// CZ: presmerujte signal z periferie GPIO na příslušný pin tlacitka
	// EN: redirect signal from GPIO peripherals to pin associated with button 1
	PORTA->PCR[4] = 1<<PORT_PCR_MUX_SHIFT;
}

void exercise4Loop()
{
	// CZ: vlozte hodnotu z tlacitka na diodu
	// EN: move value of button input to diode output
	GPIOB->PDOR = (GPIOA->PDIR>>4)<<18;
}
