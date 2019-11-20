/*******************************************************************************
* File Name: Timer_Stop_PM.c
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

#include "Timer_Stop.h"

static Timer_Stop_backupStruct Timer_Stop_backup;


/*******************************************************************************
* Function Name: Timer_Stop_SaveConfig
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
*  Timer_Stop_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Stop_SaveConfig(void) 
{
    #if (!Timer_Stop_UsingFixedFunction)
        Timer_Stop_backup.TimerUdb = Timer_Stop_ReadCounter();
        Timer_Stop_backup.InterruptMaskValue = Timer_Stop_STATUS_MASK;
        #if (Timer_Stop_UsingHWCaptureCounter)
            Timer_Stop_backup.TimerCaptureCounter = Timer_Stop_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Stop_UDB_CONTROL_REG_REMOVED)
            Timer_Stop_backup.TimerControlRegister = Timer_Stop_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Stop_RestoreConfig
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
*  Timer_Stop_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Stop_RestoreConfig(void) 
{   
    #if (!Timer_Stop_UsingFixedFunction)

        Timer_Stop_WriteCounter(Timer_Stop_backup.TimerUdb);
        Timer_Stop_STATUS_MASK =Timer_Stop_backup.InterruptMaskValue;
        #if (Timer_Stop_UsingHWCaptureCounter)
            Timer_Stop_SetCaptureCount(Timer_Stop_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Stop_UDB_CONTROL_REG_REMOVED)
            Timer_Stop_WriteControlRegister(Timer_Stop_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Stop_Sleep
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
*  Timer_Stop_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Stop_Sleep(void) 
{
    #if(!Timer_Stop_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Stop_CTRL_ENABLE == (Timer_Stop_CONTROL & Timer_Stop_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Stop_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Stop_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Stop_Stop();
    Timer_Stop_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Stop_Wakeup
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
*  Timer_Stop_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Stop_Wakeup(void) 
{
    Timer_Stop_RestoreConfig();
    #if(!Timer_Stop_UDB_CONTROL_REG_REMOVED)
        if(Timer_Stop_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Stop_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
