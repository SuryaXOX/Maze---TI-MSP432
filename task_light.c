/*
 * task_light.c
 *
 * Created: 29th April 2021
 * Author: Anirudh Jayendra
 */

#include <main.h>

volatile int color = LCD_COLOR_RED;
float lux = 0.0;

TaskHandle_t Task_Circle_Handle;

void Task_Light_Init(void){
    i2c_init();
    opt3001_init();
}

void Task_Light(void){
    while(1){
        lux = opt3001_read_lux();

        // Check light intensity and set color accordingly - <500 to >1500
        if(lux < 500.0)
        {
            color = LCD_COLOR_BLUE; // turn on BLUE
        }
        else if (lux < 600.0)
        {
            color = LCD_COLOR_BROWN; // turn on GREEN
        }
        else if (lux < 700.0)
        {
            color = LCD_COLOR_CYAN; // turn on GREEN
        }
        else if (lux < 800.0)
        {
            color = LCD_COLOR_GRAY; // turn on GREEN
        }
        else if (lux < 900.0)
        {
            color = LCD_COLOR_GREEN; // turn on GREEN
        }
        else if (lux < 1000.0)
        {
            color = LCD_COLOR_BLUE2; // turn on GREEN
        }
        else if (lux < 1100.0)
        {
            color = LCD_COLOR_MAGENTA; // turn on GREEN
        }
        else if (lux < 1200.0)
        {
            color = LCD_COLOR_GREEN2; // turn on GREEN
        }
        else if (lux < 1300.0)
        {
            color = LCD_COLOR_ORANGE; // turn on GREEN
        }
        else if (lux < 1400.0)
        {
            color = LCD_COLOR_WHITE; // turn on GREEN
        }
        else if (lux < 1500.0)
        {
            color = LCD_COLOR_YELLOW; // turn on GREEN
        }
        else
        {
            color = LCD_COLOR_RED; // turn on RED
        }

    }
}
