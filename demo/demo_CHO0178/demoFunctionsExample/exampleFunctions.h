/*
 * exampleFunctions.h
 *
 *  Created on: 17. 4. 2024
 *      Author: cho0178
 */

#ifndef SRC_DEMO_CHO0178_DEMOFUNCTIONSEXAMPLE_EXAMPLEFUNCTIONS_H_
#define SRC_DEMO_CHO0178_DEMOFUNCTIONSEXAMPLE_EXAMPLEFUNCTIONS_H_
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief set the multiplexer of port to GPIO alternative, set the direction of the RGB diode pin to output
 * 
 */


void blink();
void timerWait(unsigned int time);
void blockingWait();




#ifdef __cplusplus
}
#endif

#endif /* SRC_DEMO_CHO0178_DEMOFUNCTIONSEXAMPLE_EXAMPLEFUNCTIONS_H_ */
