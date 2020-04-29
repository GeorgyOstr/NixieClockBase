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

#define AllButtons RA5
#define RButton RA6 
#define MButton RA7 
#define LButton RA0

bool MPressed = 0;
bool LPressed = 0;
bool RPressed = 0;

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

void buttons()
{
    //Buttons
    bool tmpR = RButton;
    bool tmpL = LButton;
    bool tmpM = MButton;
    
    RButton = 1;
    LButton = 1;
    MButton = 0;
    if(AllButtons == 0){MPressed = 1;}
    else{MPressed = 0;}

    RButton = 1;
    LButton = 0;
    MButton = 1;
    if(AllButtons == 0){LPressed = 1;}
    else{LPressed = 0;}

    RButton = 0;
    LButton = 1;
    MButton = 1;
    if(AllButtons == 0){RPressed = 1;}
    else{RPressed = 0;}
    
    RButton = tmpR;
    LButton = tmpL;
    MButton = tmpM;

}

void light(int lamp, int number)
{
    buttons();
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
        light(3, number/1000%10);
        buttons();
        light(2, number/100%10);
        light(1, number/10%10);
        light(0, number%10);
    }
}
