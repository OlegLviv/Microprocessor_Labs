
#include "project.h"

int i = 0;

CY_ISR(MyInterrupt)
{ 
    LCD_lol_Position(1, 7);
    LCD_lol_PrintNumber(i++);
}

int main(void)
{
    CyGlobalIntEnable; 

    Timer_lol_Start();

        LCD_lol_Init();
        LCD_lol_Position(0, 5);
        LCD_lol_PrintString("test");
        
        isr_lol_StartEx(MyInterrupt);
        for(;;){}
}
