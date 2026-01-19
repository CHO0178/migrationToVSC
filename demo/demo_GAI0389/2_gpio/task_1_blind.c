#include "MKL25Z4.h"
#include "wdog.h"
#include "soc_def.h"
#include "res_alloc.h"


int main(void)
{
	wdog_init(WDOG_CONF_LPOCLK_1024_CYCLES);

	//TODO: set BNC pin J8 as GPIO peripheral output using PDDR register

	//TODO: configure the J8 BNC pin as an alternative GPIO using the PCR register of the PORT peripheral


	while (1) {
		//1A - use the PTOR register of the GPIO peripheral to switch log1/log0


		//1B - use the PDOR register of the GPIO peripheral to switch log1/log0


		//1C - use the PCOR, PSOR registers of the GPIO peripheral for switching log1/log0
		wdog_refresh();
	}

	return 0;
}
