/*
 * task_print1.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Surya Santhan Thenarasu
 */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_

#include "main.h"

#define VOLT_0P85  1800      // 0.85 /(3.3/4096)
#define VOLT_2P50  2200      // 2.50 /(3.3/4096)

 extern volatile bool PS2;

extern TaskHandle_t Task_Accelerometer_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;

/******************************************************************************
* Configure the IO pins for BOTH the X and Y directions of the analog
* Accelerometer.  The X direction should be configured to place the results in
* MEM[0].  The Y direction should be configured to place the results in MEM[1].
*
* After BOTH analog signals have finished being converted, a SINGLE interrupt
* should be generated.
*
* Parameters
*      None
* Returns
*      None
******************************************************************************/
 void Task_Accelerometer_Init(void);

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters);


/******************************************************************************
* Examines the ADC data from the Accelerometer on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters);



#endif /* TASK_ACCELEROMETER_H_ */
