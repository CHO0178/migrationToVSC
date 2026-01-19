#include "exampleFunctions.h"
#include "MKL25Z4.h"

unsigned int waitingTicks = 0; // half of millisecond

void timerWait(unsigned int time)
{
	// set value of timer to time in ms
	unsigned int calculatedNumberOfTicks = time*2;
	waitingTicks = 0;

	// enable receiving interrupt in NVIC
	NVIC_EnableIRQ(TPM2_IRQn);
	NVIC_SetPriority(TPM2_IRQn,2);

	// set prescaler to divide by 1
	TPM2->SC |= 0b111<<TPM_SC_PS_SHIFT;

	// set modulo value
	// F_clk = 48MHz
	// T/(div/F_clk) = 0.0005/(128/48000000) = 187
	TPM2->MOD = 187;

	// set up-counting
	TPM2->SC &= ~TPM_SC_CPWMS_MASK;

	// set clock source as module clock
	TPM2->SC |= 0b01 << TPM_SC_CMOD_SHIFT;

	// enable interrupts in TPM
	TPM2->SC |= TPM_SC_TOIE_MASK;

	while(waitingTicks<=calculatedNumberOfTicks){}  // wait for time to be evaluated

	// turn off counting
	TPM2->SC &= ~TPM_SC_CMOD_MASK;
}

void TPM2_IRQHandler()
{
	// clear timer flag
	TPM2->SC |= TPM_SC_TOF_MASK;
	//
	waitingTicks++;
}
