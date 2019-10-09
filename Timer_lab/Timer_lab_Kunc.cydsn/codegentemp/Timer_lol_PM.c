/*******************************************************************************
* File Name: Timer_lol_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_lol.h"

static Timer_lol_backupStruct Timer_lol_backup;


/*******************************************************************************
* Function Name: Timer_lol_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_lol_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_lol_SaveConfig(void) 
{
    #if (!Timer_lol_UsingFixedFunction)
        Timer_lol_backup.TimerUdb = Timer_lol_ReadCounter();
        Timer_lol_backup.InterruptMaskValue = Timer_lol_STATUS_MASK;
        #if (Timer_lol_UsingHWCaptureCounter)
            Timer_lol_backup.TimerCaptureCounter = Timer_lol_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_lol_UDB_CONTROL_REG_REMOVED)
            Timer_lol_backup.TimerControlRegister = Timer_lol_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_lol_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_lol_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_lol_RestoreConfig(void) 
{   
    #if (!Timer_lol_UsingFixedFunction)

        Timer_lol_WriteCounter(Timer_lol_backup.TimerUdb);
        Timer_lol_STATUS_MASK =Timer_lol_backup.InterruptMaskValue;
        #if (Timer_lol_UsingHWCaptureCounter)
            Timer_lol_SetCaptureCount(Timer_lol_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_lol_UDB_CONTROL_REG_REMOVED)
            Timer_lol_WriteControlRegister(Timer_lol_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_lol_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_lol_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_lol_Sleep(void) 
{
    #if(!Timer_lol_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_lol_CTRL_ENABLE == (Timer_lol_CONTROL & Timer_lol_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_lol_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_lol_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_lol_Stop();
    Timer_lol_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_lol_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_lol_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_lol_Wakeup(void) 
{
    Timer_lol_RestoreConfig();
    #if(!Timer_lol_UDB_CONTROL_REG_REMOVED)
        if(Timer_lol_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_lol_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
