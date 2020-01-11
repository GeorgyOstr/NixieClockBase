/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#define _XTAL_FREQ 4000000

#define pinA  RA2 
#define pinB  RA7
#define pinC  RA0
#define pinD  RA6

#define l0 RB4
#define l1 RB5
#define l2 RB0
#define l3 RB1
#define l4 RB2

void pwm()
{
    //PR2 = 0b00110001 ;
    //T2CON = 0b00000100 ;
    //CCPR1L = 0b00101100 ;
    //CCP1CON = 0b00111100 ;
PR2 = 0b00110001 ;
T2CON = 0b00000100 ;
CCPR1L = 0b00101010 ;
CCP1CON = 0b00011100 ;
}

void timer()
{
    T1CKPS1=1;
    T1CKPS0=1;
    T1OSCEN=1;
    TMR1CS=1;
    nT1SYNC=1;
    TMR1ON =1;
    
}

void digit(int number)
{
    switch(number){
        case 1: pinA=0; pinB=0; pinC=0; pinD=0; break;
        case 6: pinA=1; pinB=0; pinC=0; pinD=0; break;
        case 9: pinA=0; pinB=1; pinC=0; pinD=0; break;
        case 3: pinA=1; pinB=1; pinC=0; pinD=0; break;
        case 7: pinA=0; pinB=0; pinC=1; pinD=0; break;
        case 5: pinA=1; pinB=0; pinC=1; pinD=0; break;
        case 4: pinA=0; pinB=1; pinC=1; pinD=0; break;
        case 8: pinA=1; pinB=1; pinC=1; pinD=0; break;
        case 2: pinA=0; pinB=0; pinC=0; pinD=1; break;
        case 0: pinA=1; pinB=0; pinC=0; pinD=1; break;
    }
}

void delayOn()
{
    //__delay_us(1);
}

void delayOff()
{
    __delay_us(10);
}

void light(int lamp, int number)
{
    digit(number);
    switch(lamp)
    {
        case 0:  l0 = 1; delayOn(); l0 = 0; delayOff(); break;
        case 1:  l1 = 1; delayOn(); l1 = 0; delayOff(); break;
        case 2:  l2 = 1; delayOn(); l2 = 0; delayOff(); break;
        case 3:  l3 = 1; delayOn(); l3 = 0; delayOff(); break;
    }
}

void showNumber(long number, int time)
{
    for(int i=0; i < time; i++)
    {
        light(3, number/1000);
        light(2, number/100%10);
        light(1, number/10%10);
        light(0, number%10);
    }
}
struct Time
{
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
    unsigned char date;
    unsigned char weekday;
    unsigned char month;
    unsigned int year;
};


struct Time incrementTime(struct Time time)
{
    if (time.seconds==59)
    {
        time.seconds=0;
        if (time.minutes==59)
        {
            time.minutes=0;
            if (time.hours=23)
            {
                time.hours=0;
            }
            else
            {
                time.hours++;
            }
        }
        else
        {
            time.minutes++;
        }
    }
    else
    {
        time.seconds++;
    }
    return time;
}

void main(void)
{

    ConfigureOscillator();
    pwm();
    InitApp();
    timer();
    struct Time time={0,50,22,0,0,0,0};
    l4 = 1;
    
    unsigned int tmr_prev = TMR1H / 16;
    unsigned int tmr_now = TMR1H / 16;

    while(1)
    {
        tmr_now = TMR1H / 16;
        if((tmr_now-tmr_prev) != 0)
        {
            time=incrementTime(time);
        }
        tmr_prev = tmr_now;
        showNumber(100*time.hours+time.minutes,1);
    }

}

