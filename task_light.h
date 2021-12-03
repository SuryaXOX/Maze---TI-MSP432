/*
 * task_light.h
 *
 * Created on: 29th April 2021
 * Author: Anirudh Jayendra
 */

#ifndef TASK_LIGHT_H_
#define TASK_LIGHT_H_

#include <main.h>

extern volatile int color;

extern TaskHandle_t Task_Light_Handle;

void Task_Light_Init();

void Task_Light();

#endif /* TASK_LIGHT_H_ */
