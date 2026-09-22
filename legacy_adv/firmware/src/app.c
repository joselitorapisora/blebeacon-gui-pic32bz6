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
#include "app.h"
#include "configuration.h"
#include "definitions.h"
#include "app_ble.h"
#include "sensors/inc/temp_sensor.h"
#include <math.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

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
static TimerHandle_t customUpdateTimer = NULL;
static uint8_t app_liveAdvData[30] = CONFIG_BLE_GAP_ADV_DATA; // Copy initial define contents
static uint8_t app_advDataLen = 30;
static uint8_t myCounter = 0;

#define CUSTOMDATA_OFFSET 22
#define NODE_ID 001

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static void APP_CustomUpdateCallback(TimerHandle_t xTimer)
{
    APP_Msg_T appMsg;
    appMsg.msgId = APP_MSG_CUSTOM_TIMER;
    OSAL_QUEUE_Send(&appData.appQueue, &appMsg, 0);
}

void APP_CustomModAdv_CB(void)
{
    //SERCOM0_USART_Write((uint8_t *) "Timer cb.\r\n", 11);
    
    // | Node ID 1 byte | Counter 1 byte | Switch 1 byte | Temperature 2 bytes |
    app_liveAdvData[CUSTOMDATA_OFFSET + 0] = NODE_ID;
    app_liveAdvData[CUSTOMDATA_OFFSET + 1] = myCounter++; // Should wrap around 255
    app_liveAdvData[CUSTOMDATA_OFFSET + 2] = !(SWITCH1_Get());

    float temp_c = MCP9700_Temp_Celsius();
    int16_t temp_fixed88 = (int16_t) roundf(temp_c * 256.0f);
    app_liveAdvData[CUSTOMDATA_OFFSET + 3] = (uint8_t) (temp_fixed88 >> 8);
    app_liveAdvData[CUSTOMDATA_OFFSET + 4] = (uint8_t) (temp_fixed88 & 0xFF);

    BLE_GAP_AdvDataParams_T advParams;
    advParams.advLen = app_advDataLen;
    (void) memcpy(advParams.advData, app_liveAdvData, app_advDataLen);
    BLE_GAP_SetAdvData(&advParams);
}

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

    customUpdateTimer = xTimerCreate("SensorTmr", pdMS_TO_TICKS(1000), pdTRUE, (void *) 0, APP_CustomUpdateCallback);
    if (customUpdateTimer != NULL) xTimerStart(customUpdateTimer, 0);
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

    switch (appData.state)
    {
    case APP_STATE_INIT:
    {
        bool appInitialized = true;
        APP_BleStackInit();
        if (!(RTC_REGS->MODE0.RTC_CTRLA & RTC_MODE0_CTRLA_ENABLE_Msk))
        {
            RTC_Timer32Start();
        }
        BLE_GAP_SetAdvEnable(0x01, 0x00);
        SERCOM0_USART_Write((uint8_t *) "Advertising\r\n", 13);

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
            if (p_appMsg->msgId == APP_MSG_CUSTOM_TIMER)
            {
                APP_CustomModAdv_CB();
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


/*******************************************************************************
 End of File
 */
