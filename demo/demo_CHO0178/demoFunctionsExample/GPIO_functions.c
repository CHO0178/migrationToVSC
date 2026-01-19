#include "demo_CHO0178/demoFunctionsExample/exampleFunctions.h"
#include "MKL25Z4.h"
#include "demo_CHO0178/littleHelper.h"
#include "GPIO_functions.h"
// RGB diode

PORT_Type* const barGraphDiodesPorts[8] = {PORTB,PORTB,PORTB,PORTB,PORTC,PORTC,PORTC,PORTC};
GPIO_Type* const barGraphDiodesGPIOs[8] = {GPIOB,GPIOB,GPIOB,GPIOB,GPIOC,GPIOC,GPIOC,GPIOC};
const int buttonsPins[4] = {4,5,12,13};
const int barGraphDiodesPins[8] = {8,9,10,11,10,11,12,13};

void initRGB(){
	// change multiplexer in port to connect the signal to peripheral GPIO
	PORTB->PCR[18] = (PORTB->PCR[18] & (~(111<<8))) | (1<<8);
	PORTB->PCR[19] = (PORTB->PCR[19] & (~(111<<8))) | (1<<8);
	PORTD->PCR[1]  = (PORTB->PCR[1] & (~(111<<8))) | (1<<8);
	// set GPIO as output for RGB diode
	GPIOB->PDDR |= (1<<18) | (1<<19);
	GPIOD->PDDR |= (1<<1);
	// turn diodes OFF
	GPIOB->PDOR |= (1<<18) | (1<<19);
	GPIOD->PDOR |= (1<<1);
}
void setRGB(int R,int G, int B){
	R = (~R)&1;
	G = (~G)&1;
	B = (~B)&1;
	//GPIOB->PDOR &=~((1<<18)|(1<<19));
	//GPIOB->PDOR |= ((R<<18)|(G<<19));
	GPIOB->PDOR = (((R<<18)|(G<<19)) & (~((1<<18)|(1<<19)))) | (((R<<18)|(G<<19)) & ((R<<18)|(G<<19)));
	GPIOD->PDOR = ((B<<1) & (~(1<<1))) | ((B<<1) & (1<<1));
}

// diode BarGraph
void initBarGraph(){
	// for all diodes
	for(int i = 0;i<8;i++)
	{
		// set multiplexer
		barGraphDiodesPorts[i]->PCR[(int)barGraphDiodesPins[i]] = (barGraphDiodesPorts[i]->PCR[(int)barGraphDiodesPins[i]] & (~0b111<<8)) | (0b001<<8);
		// set output
		//barGraphDiodesGPIOs[i]->PDDR |= (1<<barGraphDiodesPins[i]);
		// turn off diodes
		//barGraphDiodesGPIOs[i]->PDOR |= (1<<barGraphDiodesPins[i]);
	}
	// set output
	GPIOB->PDDR |= (1<<8) | (1<<9) | (1<<10) | (1<<11); //
	GPIOC->PDDR |=  (1<<10) | (1<<11) | (1<<12) | (1<<13); // 0b1111<<10; //
	// turn off diodes
	GPIOB->PDOR |= (1<<8) | (1<<9) | (1<<10) | (1<<11); //(1<<8) | (1<<9) | (1<<10) | (1<<11);
	GPIOB->PDOR |= (1<<10) | (1<<11) | (1<<12) | (1<<13); //0b1111<<10; //
}
void setBarGraphVal(int val){
	if(val <= 8){return;};
	int i = 0;
	setBarGraphNumber(0);
	while(val!=0)
	{
		setBarGraphDiode(i);
		i++;
		val--;
	}
}
void setBarGraphNumber(int num){
	// invert order of bit in num
	int reverseNum = 0;
	for(int i = 0;i<8;i++)
	{
		reverseNum |= ((num >> (7-i))&1)<<i;
	}
	reverseNum = ~reverseNum;
	// set diodes
	GPIOB->PDOR = ((reverseNum & 0b1111)<<8) | (GPIOB->PDOR & ~(0b1111<<8));
	uint32_t a = (reverseNum & (0b1111<<4));
	a = (a>>4);
	a = (a<<10);
	GPIOC->PDOR = a | (GPIOC->PDOR & (~(0b1111<<10)));
}
void setBarGraphDiode(int diodeID){
	barGraphDiodesGPIOs[diodeID]->PDOR |= (1<<barGraphDiodesPins[diodeID]);
}
void clearBarGraphDiode(int diodeID){
	barGraphDiodesGPIOs[diodeID]->PDOR |= (1<<barGraphDiodesPins[diodeID]);
}

// buttons
/**
 * @brief initialize buttons
 * 
 */
void initButtons(){
	for(int i = 0;i<4;i++)
	{
		// set multiplexer
		PORTA->PCR[buttonsPins[i]] = ((0b001<<8) & (~0b111<<8)) | ((0b001<<8) & (~0b111<<8));
	}
	GPIOA->PDOR &= ((0b11<<5) | (0b11<<12));
}

/**
 * @brief Get the Button Val object
 * 
 * @param buttonID
 * @return 0 - button not pressed, 1 - button pressed
 */
char getButtonVal(int buttonID){
	return (~(GPIOA->PDIR >> buttonsPins[buttonID])) & 1;
}

