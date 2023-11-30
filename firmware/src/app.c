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

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"


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




// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
 
/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************



/* TODO:  Add any necessary local functions.
*/


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

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

        /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            lcd_init();         // Initialisation de l'�cran LCD
            lcd_bl_on();        // Allumer le r�tro�clairage de l'�cran LCD
            lcd_gotoxy(1,1);
            printf_lcd("TP0 Led+AD 2023-24");
            lcd_gotoxy(1,2);
            printf_lcd("Antonio Do Carmo");
            
            LEDS_ON();          // Allumer les LED
            
            DRV_TMR0_Start();           // D�marrer le Timer 0
                                    
            bool appInitialized = true;         // Drapeau indiquant si l'application est initialis�e
            
            if (appInitialized)
            {
                APP_UpdateState(APP_STATE_WAIT);            // Mettre � jour l'�tat � APP_STATE_WAIT
            }
            break;
        }
        
        case  APP_STATE_WAIT:
        {
            // Aucune t�che sp�cifique dans cet �tat, simplement en attente
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            appData.AdcRes = BSP_ReadAllADC();          // Lire les valeurs de tous les canaux ADC
            
            lcd_gotoxy(1,3);
            printf_lcd("CH0: %4d",appData.AdcRes.Chan0);        // Afficher la valeur du canal ADC 0
            
            lcd_gotoxy(11,3);
            printf_lcd("CH1: %4d",appData.AdcRes.Chan1);        // Afficher la valeur du canal ADC 1
            
            APP_UpdateState(APP_STATE_WAIT);            // Mettre � jour l'�tat � APP_STATE_WAIT

            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/*******************************************************************************
  Fonction :
    void LEDS_ON(void)

  R�sum� :
    Allume toutes les LEDs du chenillard.

  Description :
    Cette fonction est responsable d'allumer toutes les LEDs du chenillard. 
    Elle active s�par�ment chaque LED en utilisant la fonction 
    BSP_LEDOn.

  Precondition:
    Le BSP doit �tre initialis�

  Param�tres:
    Aucun.

  R�sultat:
    Aucun.

  Remarques:
    Aucun.
*/

void LEDS_ON(void){
    BSP_LEDOn(BSP_LED_0);
    BSP_LEDOn(BSP_LED_1);
    BSP_LEDOn(BSP_LED_2);
    BSP_LEDOn(BSP_LED_3);
    BSP_LEDOn(BSP_LED_4);
    BSP_LEDOn(BSP_LED_5);
    BSP_LEDOn(BSP_LED_6);
    BSP_LEDOn(BSP_LED_7);   
    }

/*******************************************************************************
  Fonction :
    void LEDS_OFF(void)

  R�sum� :
    Eteint toutes les LEDs du chenillard.

  Description :
    Cette fonction est responsable d'�teindre toutes les LEDs du chenillard. 
    Elle desactive s�par�ment chaque LED en utilisant la fonction 
    BSP_LEDOff.

  Precondition:
    Le BSP doit �tre initialis�

  Param�tres:
    Aucun.

  R�sultat:
    Aucun.

  Remarques:
    Aucun.
*/

void LEDS_OFF(){
    BSP_LEDOff(BSP_LED_0);
    BSP_LEDOff(BSP_LED_1);
    BSP_LEDOff(BSP_LED_2);
    BSP_LEDOff(BSP_LED_3);
    BSP_LEDOff(BSP_LED_4);
    BSP_LEDOff(BSP_LED_5);
    BSP_LEDOff(BSP_LED_6);
    BSP_LEDOff(BSP_LED_7);  
}

/*******************************************************************************
  Fonction :
    void APP_UpdateState(APP_STATES NewState)

  R�sum� :
    Met � jour l'�tat de l'application avec le nouvel �tat sp�cifi�.

  Description :
    Cette fonction est charg�e de mettre � jour l'�tat de l'application avec le 
    nouvel �tat fourni en param�tre. Elle affecte directement la variable 
    globale "appData.state" avec la valeur de "NewState".

  Precondition:
    Le BSP doit �tre initialis�

  Param�tres:
    Aucun.

  R�sultat:
    Aucun.

  Remarques:
    Aucun.
*/

void APP_UpdateState ( APP_STATES NewState ){
    
    appData.state = NewState;
}

/*******************************************************************************
  Fonction :
    void LEDS(void)

  R�sum� :
    G�re le chenillard en allumant successivement une LED � la fois.

  Description :
    Cette fonction est responsable de la gestion du chenillard en allumant 
    successivement une LED � la fois dans un ordre d�fini. Elle utilise une 
    variable statique "counter_leds" pour suivre l'�tat actuel du chenillard 
    et effectue les op�rations n�cessaires pour �teindre la LED courante et 
    allumer la suivante en fonction de cette variable.

  Precondition:
    Aucun.

  Param�tres:
    NewState : Nouvel �tat de l'application � d�finir.

  R�sultat:
    Aucun.

  Remarques:
    Aucun.
*/

void LEDS(){
    
    static int counter_leds = 0;
    
    switch(counter_leds)
    {        
        case 0:
            BSP_LEDOff(BSP_LED_7);
            BSP_LEDOn(BSP_LED_0);
            break;
        case 1:
            BSP_LEDOff(BSP_LED_0);
            BSP_LEDOn(BSP_LED_1);
            break;
        case 2:
            BSP_LEDOff(BSP_LED_1);
            BSP_LEDOn(BSP_LED_2);
            break;
        case 3:
            BSP_LEDOff(BSP_LED_2);
            BSP_LEDOn(BSP_LED_3);
            break;
        case 4:
            BSP_LEDOff(BSP_LED_3);
            BSP_LEDOn(BSP_LED_4);
            break;
        case 5:
            BSP_LEDOff(BSP_LED_4);
            BSP_LEDOn(BSP_LED_5);
            break;
        case 6:
            BSP_LEDOff(BSP_LED_5);
            BSP_LEDOn(BSP_LED_6);
            break;
        case 7:    
            BSP_LEDOff(BSP_LED_6);
            BSP_LEDOn(BSP_LED_7);
            break;
    }

    if(counter_leds != 7)
    {
        counter_leds++;
    }
    else
    {
        counter_leds = 0;
    } 
}

/*******************************************************************************
 End of File
 */
