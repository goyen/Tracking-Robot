#include "mbed.h"
#define     SOUND_SEEPD     342
#define     INITIAL_TIME    505

InterruptIn event1(PTA5);
InterruptIn event2(PTA12);
DigitalOut pulse(PTA4);        
Serial PC(USBTX,USBRX);

Timer route_1;
Timer route_2;
Timer period_s;
int point1=0;
int point2=0;
int time_interval=0;
double distance=0.0;

void reset(void);
void interrupt1();
void interrupt2();
double find_degree(double a,double b,double c);

