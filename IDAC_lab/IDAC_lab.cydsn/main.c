#include "project.h"

/* sinus points */
const uint8 sinus[] = 
{
    128, 167, 203, 231, 249,
    255, 249, 231, 203, 167,
    128, 89, 53, 25, 7,
    1, 7, 25, 53, 89
};

/* sinus array pointer */
int32 n = 0;

/* k coefficients of mode */
float kMode1 = 0.9999625;
float kMode2 = 0.9999125;
float k = 0;

/* current amplitude */
float y = 0;

/* pin mode value */
uint8 pinModeVal;

/* ISR: calculating of current sinsus point */
CY_ISR(MySinusDac)
{
    float currentPoint = (sinus[n] - 127) * y + 127;
    IDAC_SetValue(currentPoint);
    
    n++;
    y = y * k;
    if(n == 20)
    {
        n = 0;
    }
}

/* ISR: start of sinus printing */
CY_ISR(BtnStart)
{
    y = 1;
    LCD_Position(1, 9);
    LCD_PrintString("Start");
    Timer_Stop_Start();
}

/* ISR: stop of sinsus printing */
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
    
    /* assigning default k value */    
    k = kMode1;
    
    /* Enable ISR for execution of printing sinus */
    isr_start_StartEx(BtnStart);
    
    /* Enable ISR for calculating of sinus points */
    isr_StartEx(MySinusDac);
    
    /* Enable ISR for stoping of sinus printing */
    isr_stop_StartEx(TimerStop);
    
    
    for(;;)
    {
       /* getting value of pin */
       pinModeVal = Pin_Mode_Read();
        
        /* disabling interrupt processes for avoiding printing of extra symbols in the end of LCD display */   
        isr_start_Disable();
        isr_stop_Disable();
        
        LCD_Position(1, 0);
        LCD_PrintString("Mode ");
        
        if(pinModeVal == 1)
        {
          LCD_Position(1, 5);
          LCD_PrintString("1:");
          k = kMode1;
        }
        else
        {
          LCD_Position(1, 5);
          LCD_PrintString("2:");
          k = kMode2;  
        }
        
        /* enabling interupting processes */
        isr_start_Enable();
        isr_stop_Enable();
    }
}