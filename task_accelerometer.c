/*
 * task_led.c
 *
 *  Created on: 28th April 2021
 *      Author: Anirudh Jayendra
 */

#include <main.h>


 TaskHandle_t Task_Accelerometer_Handle;
 TaskHandle_t Task_Accelerometer_Timer_Handle;

 volatile uint32_t ACCELEROMETER_X_DIR = 0;
 volatile uint32_t ACCELEROMETER_Y_DIR = 0;

/******************************************************************************
* This function will run the same configuration code that you would have
* written for HW02.
******************************************************************************/
 void Task_Accelerometer_Init(void)
 {
     // Configure the X direction as an analog input pin.
     P6->SEL0 |= BIT1;
     P6->SEL1 &= ~BIT1;

     // Configure the Y direction as an analog input pin.
     P4->SEL0 |= BIT0;
     P4->SEL1 &= ~BIT0;

     // Configure CTL0 to sample 16-times in pulsed sample mode.
     // NEW -- Indicate that this is a sequence of samples.
     ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_1;

     // Configure CTL1 to return 12-bit values
     ADC14->CTL1 = ADC14_CTL1_RES_2;         // Use sampling timer, 12-bit conversion results

     // Associate the X direction analog signal with MEM[0]
     ADC14->MCTL[0] |= ADC14_MCTLN_INCH_14;

     // Associate the Y direction analog signal with MEM[1]
     // NEW -- Make sure to indicate this is the end of a sequence.
     ADC14->MCTL[1] |= ADC14_MCTLN_INCH_13 | ADC14_MCTLN_EOS;

     // Enable interrupts AFTER a value is written into MEM[1].
     ADC14->IER0 |= ADC14_IER0_IE1 ;

     // Enable ADC Interrupt
     NVIC_EnableIRQ(ADC14_IRQn);

     // Interrupt priorities must NOT be set to 0.  It is preferred if they are set to a value that is > than 1 too.
     NVIC_SetPriority(ADC14_IRQn,2);

     // Turn ADC ON
     ADC14->CTL0 |= ADC14_CTL0_ON;

 }

 /******************************************************************************
 * Used to start an ADC14 Conversion
 ******************************************************************************/
 void Task_Accelerometer_Timer(void *pvParameters)
 {
     while(1)
     {
         /*
          * Start the ADC conversion
          */
         ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

         /*
          * Delay 5mS
          */
         vTaskDelay(pdMS_TO_TICKS(5));

     }
 }


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the accelerometer on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters)
{
    SHIP_MSG_t msg;
//    SHIP_MSG_t prev_msg = SHIP_CMD_CENTER;
    uint32_t ulEventsToProcess;
    BaseType_t status;


    while(1)
    {
        /*
         * Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /*
         * Send message based
         * on the values of JOYSTICK_X_DIR and JOYSTIC_Y_DIR
         */
        if(ACCELEROMETER_X_DIR < VOLT_0P85)
        {
            msg.cmd = SHIP_CMD_LEFT;
            msg.value = 1;
        }
        else if(ACCELEROMETER_X_DIR > VOLT_2P50)
        {
            msg.cmd = SHIP_CMD_RIGHT;
            msg.value = 1;
        }
        else if(ACCELEROMETER_Y_DIR < VOLT_0P85)
        {
            msg.cmd = SHIP_CMD_DOWN;
            msg.value = 1;
        }
        else if(ACCELEROMETER_Y_DIR > VOLT_2P50)
        {
            msg.cmd = SHIP_CMD_UP;
            msg.value = 1;
        }
        else
        {
            msg.cmd = SHIP_CMD_CENTER;
        }

        /*
         * Send dir to Queue_Console if the the current direction
         * of the joystick does not match the previous direction of the joystick
         */
//        if(dir!=prev_dir){
        status = xQueueSend(Queue_Circle, &msg, portMAX_DELAY);
//        }

//        /*
//         * Update the prev_dir of the joystick
//         */
//        prev_dir = dir;
    }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    ACCELEROMETER_X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    ACCELEROMETER_Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt


    /* ADD CODE
     * Send a task notification to Task_Accelerometer_Bottom_Half
     */
    vTaskNotifyGiveFromISR(Task_Accelerometer_Handle, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}



