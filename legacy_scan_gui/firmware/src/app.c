// DOM-IGNORE-BEGIN
/*******************************************************************************
 * Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. It is your
 * responsibility to comply with third party license terms applicable to your
 * use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <string.h>
#include <stdio.h>
#include "app.h"
#include "definitions.h"
#include "app_ble.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define FIXED_STR_SIZE 16

volatile bool g_gfxUpdatePending = false;
volatile bool g_gfxInitPending = true;
volatile uint8_t g_advNodeID = 8;
volatile uint8_t g_advCounter = 0;
volatile uint8_t g_advSwitch = 0;
volatile uint8_t g_advTempHigh = 0;
volatile uint8_t g_advTempLow = 0;

static leFixedString fixedStringNodeID;
static leFixedString fixedStringCounter;
static leFixedString fixedStringSwitch;
static leFixedString fixedStringTemp;
static leChar fixedStringStatbuffNodeID[FIXED_STR_SIZE] = {0};
static leChar fixedStringStatbuffCounter[FIXED_STR_SIZE] = {0};
static leChar fixedStringStatbuffSwitch[FIXED_STR_SIZE] = {0};
static leChar fixedStringStatbuffTemp[FIXED_STR_SIZE] = {0};

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
 */

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void)
{
    appData.state = APP_STATE_INIT;
    appData.appQueue = xQueueCreate(64, sizeof (APP_Msg_T));
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void)
{
    APP_Msg_T appMsg[1];
    APP_Msg_T *p_appMsg;
    p_appMsg = appMsg;

    /* Check the application's current state. */
    switch (appData.state)
    {
        /* Application's initial state. */
    case APP_STATE_INIT:
    {
        bool appInitialized = true;
        APP_BleStackInit();
        BLE_GAP_SetScanningEnable(true, BLE_GAP_SCAN_FD_ENABLE, BLE_GAP_SCAN_MODE_OBSERVER, 100);
        //SERCOM0_USART_Write((uint8_t *) "Scanning \r\n", 11);
        if (appInitialized)
        {
            appData.state = APP_STATE_SERVICE_TASKS;
        }
        break;
    }
    case APP_STATE_SERVICE_TASKS:
    {
        if (OSAL_QUEUE_Receive(&appData.appQueue, &appMsg, OSAL_WAIT_FOREVER))
        {
            if (p_appMsg->msgId == APP_MSG_BLE_STACK_EVT)
            {
                // Pass BLE Stack Event Message to User Application for handling
                APP_BleStackEvtHandler((STACK_Event_T *) p_appMsg->msgData);
            }
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

void Screen0_OnUpdate(void)
{
    char cStrBuff[FIXED_STR_SIZE];
    if (g_gfxInitPending)
    {
        leFixedString_Constructor(&fixedStringNodeID, fixedStringStatbuffNodeID, FIXED_STR_SIZE);
        fixedStringNodeID.fn->setFont(&fixedStringNodeID, (leFont*) & aptos_light_l);
        leFixedString_Constructor(&fixedStringCounter, fixedStringStatbuffCounter, FIXED_STR_SIZE);
        fixedStringCounter.fn->setFont(&fixedStringCounter, (leFont*) & aptos_light_l);
        leFixedString_Constructor(&fixedStringSwitch, fixedStringStatbuffSwitch, FIXED_STR_SIZE);
        fixedStringSwitch.fn->setFont(&fixedStringSwitch, (leFont*) & aptos_light_l);
        leFixedString_Constructor(&fixedStringTemp, fixedStringStatbuffTemp, FIXED_STR_SIZE);
        fixedStringTemp.fn->setFont(&fixedStringTemp, (leFont*) & aptos_light_l);
        g_gfxInitPending = false;
    }
    if (g_gfxUpdatePending)
    {
        //SERCOM0_USART_Write((uint8_t *) "On_Update\r\n", 11);
        snprintf(cStrBuff, 16, "%lu", g_advNodeID);
        fixedStringNodeID.fn->setFromCStr(&fixedStringNodeID, cStrBuff);
        Screen0_LabelWidget_NodeID->fn->setString(Screen0_LabelWidget_NodeID, (leString*) & fixedStringNodeID);
        snprintf(cStrBuff, 16, "%lu", g_advCounter);
        fixedStringCounter.fn->setFromCStr(&fixedStringCounter, cStrBuff);
        Screen0_LabelWidget_Counter->fn->setString(Screen0_LabelWidget_Counter, (leString*) & fixedStringCounter);
        snprintf(cStrBuff, 16, "%lu", g_advSwitch);
        fixedStringSwitch.fn->setFromCStr(&fixedStringSwitch, cStrBuff);
        Screen0_LabelWidget_Switch->fn->setString(Screen0_LabelWidget_Switch, (leString*) & fixedStringSwitch);

        int16_t temp_fixed88 = (int16_t) ((g_advTempHigh << 8) | g_advTempLow);
        float temp_c = (float) temp_fixed88 / 256.0f;
        snprintf(cStrBuff, 16, "%.1f °C", temp_c);
        fixedStringTemp.fn->setFromCStr(&fixedStringTemp, cStrBuff);
        Screen0_LabelWidget_Temp->fn->setString(Screen0_LabelWidget_Temp, (leString*) & fixedStringTemp);

        BLE_GAP_SetScanningEnable(true, BLE_GAP_SCAN_FD_ENABLE, BLE_GAP_SCAN_MODE_OBSERVER, 100);
        g_gfxUpdatePending = false;
    }
}

/*******************************************************************************
End of File
 */
