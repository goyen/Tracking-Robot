#include "Tracking.h"


int main()
{
    double distance_1=0.0;
    double distance_2=0.0;
    double degree=0.0;
    event1.rise(&interrupt1);
    event2.rise(&interrupt2);
    route_1.start();
    route_2.start();
    period_s.start();
    while(1)
    {
        pulse=1;
        wait_ms(3);
        pulse=0;
        wait_ms(3);
        if(period_s>0.500)
        {
            event1.disable_irq();
            event2.disable_irq();
            period_s.stop();
            distance_1=(SOUND_SEEPD*(route_1.read_us()-INITIAL_TIME))*0.000001;
            distance_2=(SOUND_SEEPD*(route_2.read_us()-INITIAL_TIME))*0.000001;
            degree=find_degree(distance_1>distance_2?distance_1:distance_2, 0.1, distance_1>distance_2?distance_2:distance_1);
            PC.printf("sensor1: %d sensor2: %d\n\r degree: %lf distance: %lfm\n\r\n\r",point1,point2,distance_1,distance_2);
            reset();
        }
    }
}

void reset(void)
{
    point1=0;
    point2=0;
    route_1.reset();
    route_2.reset();
    period_s.reset();
    route_1.start();
    route_2.start();
    period_s.start();
    event1.enable_irq();
    event2.enable_irq();
}

void interrupt1()
{
    if(point1==0)
    {
        route_1.stop();
    }
    point1++;
}
void interrupt2()
{
    if(point2==0)
    {
        route_2.stop();
    }
    point2++;
}

double find_degree(double a,double b,double c)
{
    double d,e,f;
    double theta=acos(((a*a)+(b*b)-(c*c))/(2.0*b*a));
    d=a*cos(theta);
    e=a*sin(theta);
    f=sqrt(e*e+(d-0.05)*(d-0.05));
    theta=asin(e/f);
    distance=f;
    return theta*180/3.141592;
}
