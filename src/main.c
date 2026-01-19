/*
 * Name: main.c
 * Author: You
 *
 * This is a stub. Write your code here.
 *
 */

#include "wdog.h"

__attribute__ ((weak)) int main(void)
{
	wdog_init(WDOG_CONF_DIS);

	while (1) {

	}

	return 0;
}