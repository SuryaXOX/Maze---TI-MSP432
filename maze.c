/*
 * maze.c
 *
 *  Created on: Apr 23, 2021
 *      Author: 13478
 */

#include <main.h>

TaskHandle_t Task_Maze_Handle;
QueueHandle_t Queue_Maze;


// Function used to initialize the maze
extern void maze_init()
{


    // Horizontal Lines
    lcd_draw_rectangle(30, 3, 77,LINE_WIDTH,LCD_COLOR_WHITE);
    lcd_draw_rectangle(120,3, 33,LINE_WIDTH,LCD_COLOR_WHITE);

    lcd_draw_rectangle(65, 30, 77,LINE_WIDTH,LCD_COLOR_WHITE);

    lcd_draw_rectangle(100, 55, 77,LINE_WIDTH,LCD_COLOR_WHITE);

    lcd_draw_rectangle(52, 80, 51,LINE_WIDTH,LCD_COLOR_WHITE);
    lcd_draw_rectangle(120, 80, 25,LINE_WIDTH,LCD_COLOR_WHITE);

    lcd_draw_rectangle(40, 105, 25,LINE_WIDTH,LCD_COLOR_WHITE);

    lcd_draw_rectangle(15, 128, 25,LINE_WIDTH,LCD_COLOR_WHITE);
    lcd_draw_rectangle(100, 128, 88,LINE_WIDTH,LCD_COLOR_WHITE);

    lcd_draw_rectangle(105,105, 11,LINE_WIDTH,LCD_COLOR_WHITE);
    lcd_draw_rectangle(32,56, 11,LINE_WIDTH,LCD_COLOR_WHITE);

    // Vertical Lines
    lcd_draw_rectangle(2,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);
    lcd_draw_rectangle(129,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);

    lcd_draw_rectangle(100,117, LINE_WIDTH, 23,LCD_COLOR_WHITE);
    lcd_draw_rectangle(27,117, LINE_WIDTH, 24,LCD_COLOR_WHITE);

    lcd_draw_rectangle(77,105, LINE_WIDTH, 48,LCD_COLOR_WHITE);

    lcd_draw_rectangle(103,16, LINE_WIDTH, 27,LCD_COLOR_WHITE);
    lcd_draw_rectangle(27,43, LINE_WIDTH, 27,LCD_COLOR_WHITE);

    lcd_draw_rectangle(62,60, LINE_WIDTH, 10,LCD_COLOR_WHITE);
    lcd_draw_rectangle(35,24, LINE_WIDTH, 11,LCD_COLOR_WHITE);
    lcd_draw_rectangle(60,9, LINE_WIDTH, 11,LCD_COLOR_WHITE);
    lcd_draw_rectangle(45,85, LINE_WIDTH, 11,LCD_COLOR_WHITE);
    lcd_draw_rectangle(90,49, LINE_WIDTH, 11,LCD_COLOR_WHITE);
    lcd_draw_rectangle(110,60, LINE_WIDTH, 11,LCD_COLOR_WHITE);
    lcd_draw_rectangle(108,86, LINE_WIDTH, 10,LCD_COLOR_WHITE);
    lcd_draw_rectangle(53,110, LINE_WIDTH, 10,LCD_COLOR_WHITE);

}

void Task_Maze(void *pvParameters)
{
    BaseType_t status;
    int msg;

    while(1)
    {

        /* ADD CODE
         * wait until we receive a message in  Queue_Maze
         */
        status = xQueueReceive(Queue_Maze, &msg, 0);

        if(msg == 1) // Invalid Movement - Boundary has been touched
        {
            //ece353_MKII_RGB_LED(true, false, false); // LED Turns RED

            ece353_MKII_Buzzer_On(); // Turn the Buzzer On
        }
        else if(msg == 0) // Valid Movement
        {
            //ece353_MKII_RGB_LED(false, true, false); // LED Turns GREEN

            ece353_MKII_Buzzer_Off(); // Turn the Buzzer Off
        }
    }
}
