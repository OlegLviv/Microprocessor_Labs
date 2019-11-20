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

float k = 0.9999625;
float y = 0;

CY_ISR(MySinusDac)
{
    float temp = (sinus[n] - 127) * y + 127;
    IDAC_SetValue(temp);
    
    n++;
    y = y * k;
    if(n == 20)
    {
        n = 0;
    }
}

CY_ISR(BtnStart)
{
    y=1;
            LCD_Position(1, 9);
        LCD_PrintString("Start");
        Timer_Stop_Start();
}

CY_ISR(TimerStop)
{
                LCD_Position(1, 9);
        LCD_PrintString("     ");
        y = 0;
        Timer_Stop_Stop();
}

int main(void)
{
    CyGlobalIntEnable; 
    
    Timer_Start();
    IDAC_Start();
    
        LCD_Init();
        LCD_Position(0, 3);
        LCD_PrintString("Rising exp");
    isr_start_StartEx(BtnStart);
    isr_StartEx(MySinusDac);
    
    isr_stop_StartEx(TimerStop);
    
    
    for(;;)
    {}
}