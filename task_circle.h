/*
 * task_space_ship.h
 *
 *  Created on: Nov 3, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_CIRCLE_H_
#define TASK_CIRCLE_H_

#include <main.h>

typedef enum {
    SHIP_CMD_LEFT,
    SHIP_CMD_RIGHT,
    SHIP_CMD_UP,
    SHIP_CMD_DOWN,
    SHIP_CMD_CENTER,
    SHIP_CMD_SPEED
} SHIP_CMD_t;

typedef struct {
    SHIP_CMD_t cmd;
    uint8_t     value;
}SHIP_MSG_t;

extern TaskHandle_t Task_Circle_Handle;
extern QueueHandle_t Queue_Circle;

/******************************************************************************
 * This function will initialize Queue_Space_Ship
 ******************************************************************************/
void Task_Circle_Init(void);

// Function used to initialize the maze
void maze_init();

// Function used to initialize the maze with a blank screen
void maze_blank();

// Function that flashes a red LED and turns on the buzzer if there is any invalid movement
void invalid_movement();

// Function that turn LED green and turns off the buzzer if there is any valid movement
void valid_movement();

/******************************************************************************
* Helper Function for Check_Boundaries(int x, int y, int z)
* Return true if the circle is within the boundaries
******************************************************************************/
bool Check_Boundaries_Helper(int a, int b);

/******************************************************************************
* Depending on the ADC data, this function checks if the circle moves within the given boundaries
* Return true if the circle is within the boundaries
******************************************************************************/
bool Check_Boundaries(int x, int y, int z);

/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to the
 ******************************************************************************/
void Task_Circle(void *pvParameters);

#endif /* TASK_CIRCLE_H_ */
