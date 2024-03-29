/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

#include "pic16f628a.h"
/* Refer to the device datasheet for information about available
oscillator configurations. */

void ConfigureOscillator(void)
{
    PCON,OSCF = 1;
}
