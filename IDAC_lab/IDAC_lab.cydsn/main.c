#include "project.h"

const uint8 sinus[] = 
{
    128, 167, 203, 231, 249,
    255, 249, 231, 203, 167,
    128, 89, 53, 25, 7,
    1, 7, 25, 53, 89
};

int32 n = 0;
uint32 n1 = 0;

CY_ISR(MySinusDac)
{
    IDAC_SetValue(sinus[n]);
    
    if(n1 ==0)
    {
        n = n + 1;
    }
    
    if(n1==1)
    {
        n = n -1;
    }
    
    if(n == 20)
    {   
        n1 = 1;
        n = 19;
    }
    
    if(n == -1)
    {
        n = 0;
        n1=0;
    }
}

int main(void)
{
    CyGlobalIntEnable; 
 
    Timer_Start();
    IDAC_Start();
    
    isr_StartEx(MySinusDac);
    
    for(;;)
    {}
}