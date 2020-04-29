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

void pwm(unsigned int freq, unsigned int duty)
{
    
    //Duty = ( (float)duty/1023) * (_XTAL_FREQ / (PWM_freq*TMR2PRESCALE));
    //PWM Period = [(PR2) + 1] * 4 * TOSC * (TMR2 Prescale Value)
    //PR2 = (_XTAL_FREQ/ (PWM_freq*4*TMR2PRESCALE)) ? 1;
    
    T2CON = 0b00000100; //prescale: 00 01 10 11 = 1 4 16 16 
    CCP1CON = 0b00011100 ;
    CCPR1L  = 0b00101010 ;
    PR2     = 0b00110001 ;

    PR2 = (_XTAL_FREQ / (freq*4)) - 1;

    duty = (_XTAL_FREQ/1000 * duty) / freq ; 
    CCP1X = duty % 1; 
    CCP1Y = duty & 2; 
    CCPR1L = duty>>2;
}

void pwmMod(unsigned int freq, unsigned int duty)
{
    PR2 = (_XTAL_FREQ / (freq*4)) - 1;
    duty = (_XTAL_FREQ/1000 * duty) / freq; 
    CCP1X = duty % 1; 
    CCP1Y = duty & 2; 
    CCPR1L = duty>>2;
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
    //pwm();
    pwm(36200, 900);
    
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
    unsigned int pwmduty = 400;
    while(1)
    {
        //TIME COUNTING
        tmr_now = TMR1H;
        if((tmr_now-tmr_prev) != 0)
        {
            pwmduty+=3;
            if (pwmduty>985){pwmduty = 400;}
            pwmMod(36200, pwmduty);
            time = incrementTime(time, sixteenth);
        }
        tmr_prev = tmr_now;
        //TIME COUNTING
        out = time.hours*100 + time.minutes;
        out = time.minutes*100 + time.seconds;
        out = pwmduty;
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
        showNumber(out);
    }
}

