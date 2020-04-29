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
#include "TimeLib.h"
#include "LightLib.h"

void pwm()
{
    //PR2 = 0b00110001 ;
    //T2CON = 0b00000100 ;
    //CCPR1L = 0b00101100 ;
    //CCP1CON = 0b00111100 ;
    PR2     = 0b00110001 ;
    T2CON   = 0b00000100 ;
    CCPR1L  = 0b00101010 ;
    CCP1CON = 0b00011100 ;
}

void timer()
{
    T1CKPS1 = 1;
    T1CKPS0 = 1;
    T1OSCEN = 1;
    TMR1CS  = 1;
    nT1SYNC = 1;
    TMR1ON  = 1; 
    TMR1H   = 0; 
    TMR1L   = 0;
    /* Disable TIMER1 interrupt  */ 
    CCP1IF  = 0;
    CCP1IE  = 0;
    TMR1IF  = 0; 
    TMR1IE  = 0; 
}

void main(void)
{
    ConfigureOscillator();
    pwm();
    InitApp();
    __delay_us(1000);
    timer();
    
    struct Time time={0,0,50,22,0,0,0,0};
    struct Time sixteenth={1,0,0,0,0,0,0,0};
    
    l4 = 1;
    unsigned int tmr_prev = TMR1H;
    unsigned int tmr_now = TMR1H;
    unsigned char count16 = 0;
    unsigned int out = 0;
    while(1)
    {
        //TIME COUNTING
        tmr_now = TMR1H;
        if((tmr_now-tmr_prev) != 0)
        {

            time = incrementTime(time, sixteenth);
        }
        tmr_prev = tmr_now;
        //TIME COUNTING
        out = time.hours*100 + time.minutes;
        out = time.minutes*100 + time.seconds;
        
        if (RPressed)
        {
            out = 2222;
        }
        if (LPressed)
        {
            out = 4444;
        }
        if (MPressed)
        {
            out = 0;
        }
        
        
        
        showNumber(out, 1);
    }
}

