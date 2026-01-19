#ifndef GPIO_FUNCTIONS_H
#define GPIO_FUNCTIONS_H

// RGB diode
void initRGB();
void setRGB(int R,int G, int B);

// diode BarGraph
void initBarGraph();
void setBarGraphVal(int val);
void setBarGraphNumber(int num);
void setBarGraphDiode(int diodeID);
void clearBarGraphDiode(int diodeID);

// buttons
void initButtons();
char getButtonVal(int buttonID);



#endif
