/*******************************************************************************
* File Name: LCD_lol_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_lol.h"


static LCD_lol_BACKUP_STRUCT LCD_lol_backup;


/*******************************************************************************
* Function Name: LCD_lol_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_lol_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_lol_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_lol_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_lol_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_lol_Sleep(void) 
{
    LCD_lol_backup.enableState = LCD_lol_enableState;
    LCD_lol_SaveConfig();
    LCD_lol_Stop();
}


/*******************************************************************************
* Function Name: LCD_lol_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  LCD_lol_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_lol_Wakeup(void) 
{
    LCD_lol_RestoreConfig();

    if(LCD_lol_backup.enableState == 1u)
    {
        LCD_lol_Enable();
    }
}


/* [] END OF FILE */
