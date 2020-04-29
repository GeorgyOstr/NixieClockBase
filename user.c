/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "pic16f628a.h"
#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    TRISA=0x00;
    TRISA5=1;
    TRISA4=1;
    TRISA1=1;
    //Disable damn reference
    VREN=0; VROE=0; VRR=0; VR0=1; VR1=1; VR2=1; VR3=1;
    //Damn comporators
    CM0=1; CM1=1; CM2=1;
    
    TRISB=0x00;
    TRISB6=1;
    TRISB7=1;
    
    RA0=0; //C, Lbutton
    RA1=1; //Power for k155id1. wired to 1
    RA2=0; //A 
    RA3=0; //UM66
    RA4=0; //DS18 not used
    RA5=0; //Buttons all
    RA6=0; //D, RButton
    RA7=0; //B, MidButton
    
    RB0=0; //2
    RB1=0; //3
    RB2=0; //4
    RB3=0; //CCP1
    RB4=0; //0
    RB5=0; //1
    RB6=0; //OSCTIMER
    RB7=0; //OSCTIMER
}

