/*
 * task_space_ship.c
 *
 *  Created on: Nov 3, 2020
 *      Author: Joe Krachey, modified by Anirudh Jayendra April 9th 2021
 */

#include <main.h>

#define CIRCLE_QUEUE_LEN  2
#define LINE_WIDTH 1

TaskHandle_t Task_Circle_Handle;
QueueHandle_t Queue_Circle;

extern volatile uint16_t COUNT = 0;
extern volatile uint8_t x = 85;
extern volatile uint8_t y = 15;
extern volatile uint8_t BLANK = 0;

/******************************************************************************
 * This function will initialize Queue_Space_Ship and initialize the LCD
 ******************************************************************************/
void Task_Circle_Init(void)
{
    Queue_Circle = xQueueCreate(CIRCLE_QUEUE_LEN,sizeof(SHIP_MSG_t));

    // ADD CODE to initialize the LCD
    Crystalfontz128x128_Init();
}

// Function used to initialize the maze with a blank screen
void maze_blank()
{
        lcd_draw_rectangle(30, 3, 77,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(120,3, 33,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(65, 30, 77,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(100, 55, 77,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(52, 80, 51,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(120, 80, 25,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(40, 105, 25,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(15, 128, 25,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(100, 128, 88,LINE_WIDTH,LCD_COLOR_BLACK);
        lcd_draw_rectangle(2,65, LINE_WIDTH, 128,LCD_COLOR_BLACK);
        lcd_draw_rectangle(129,65, LINE_WIDTH, 128,LCD_COLOR_BLACK);
        lcd_draw_rectangle(100,117, LINE_WIDTH, 23,LCD_COLOR_BLACK);
        lcd_draw_rectangle(27,117, LINE_WIDTH, 24,LCD_COLOR_BLACK);
        lcd_draw_rectangle(77,105, LINE_WIDTH, 48,LCD_COLOR_BLACK);
        lcd_draw_rectangle(103,16, LINE_WIDTH, 27,LCD_COLOR_BLACK);
        lcd_draw_rectangle(27,43, LINE_WIDTH, 27,LCD_COLOR_BLACK);
}
// Function used to initialize the maze
void maze_init()
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

    // Vertical Lines

    lcd_draw_rectangle(2,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);
    lcd_draw_rectangle(129,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);

    lcd_draw_rectangle(100,117, LINE_WIDTH, 23,LCD_COLOR_WHITE);
    lcd_draw_rectangle(27,117, LINE_WIDTH, 24,LCD_COLOR_WHITE);

   lcd_draw_rectangle(77,105, LINE_WIDTH, 48,LCD_COLOR_WHITE);

    lcd_draw_rectangle(103,16, LINE_WIDTH, 27,LCD_COLOR_WHITE);
    lcd_draw_rectangle(27,43, LINE_WIDTH, 27,LCD_COLOR_WHITE);

}

// Function that flashes a red LED and turns on the buzzer if there is any invalid movement
void invalid_movement()
{
    bool b = true;

    ece353_MKII_RGB_LED(true, false, false); // Turns on the RED LED

    ece353_MKII_Buzzer_On(); // Turns on the buzzer

    COUNT++;

    while(b)
    {
        if(ece353_MKII_S2()) // Re-centers the circle when S2 has been pressed
        {
            b = false;

            lcd_draw_image(
                    x,
                    y,
                    circleWidthPixels,
                    circleHeightPixels,
                    circleBitmaps,
                    LCD_COLOR_BLACK,
                    LCD_COLOR_BLACK);

            x = 85;
            y = 15;
        }
    }
}

// Function that turn LED green and turns off the buzzer if there is any valid movement
void valid_movement()
{
    ece353_MKII_RGB_LED(false, true, false); // Turn on the GREEN LED

    ece353_MKII_Buzzer_Off(); // Turns on the buzzer
}

/******************************************************************************
* Helper Function for Check_Boundaries(int x, int y, int z)
* Return true if the circle is within the boundaries
******************************************************************************/
bool Check_Boundaries_Helper(int a, int b)
{
    // Vertical Lines

    if( (a>18) && (a<36) && (b>96) && (b<128) )   //     lcd_draw_rectangle(27,117, LINE_WIDTH, 24,LCD_COLOR_WHITE);
    {
        return false;

    }
    else if( (a>68) && (a<86) && (b>69) && (b<128) )  //     lcd_draw_rectangle(77,105, LINE_WIDTH, 48,LCD_COLOR_WHITE);
    {
        return false;

    }
    else if( (a>94) && (a<112) && (b>0) && (b<43) )      //    lcd_draw_rectangle(103,16, LINE_WIDTH, 27,LCD_COLOR_WHITE);

    {
        return false;

    }
    else if( (a>18) && (a<36) && (b>21) && (b<66) )      //    lcd_draw_rectangle(27,43, LINE_WIDTH, 27,LCD_COLOR_WHITE);

    {
        return false;

    }
    else if( (a>91) && (a<109) && (b>94) && (b<128) )      //     lcd_draw_rectangle(100,117, LINE_WIDTH, 23,LCD_COLOR_WHITE);

    {
        return false;

    }
    else if( (a>120) && (a<128) && (b>0) && (b<128) )      //     lcd_draw_rectangle(129,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);

    {
        return false;

    }
    else if( (a>0) && (a<13) && (b>0) && (b<128) )      //     lcd_draw_rectangle(2,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);

    {
        return false;

    }
    else if( (a>120) && (a<128) && (b>0) && (b<128) )      //         lcd_draw_rectangle(129,65, LINE_WIDTH, 128,LCD_COLOR_WHITE);

    {
        return false;

    }
    // Horizontal Lines

    else if( (a>18) && (a<60) && (b>96) && (b<114) )      //          lcd_draw_rectangle(40, 105, 25,LINE_WIDTH,LCD_COLOR_WHITE);
      {
           return false;

      }
    else if ( (a>0) && (a<30) && (b>119) && (b<128) )      //         lcd_draw_rectangle(15, 128, 25,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>50) && (a<128) && (b>119) && (b<128) )      //           lcd_draw_rectangle(100, 128, 88,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>100) && (a<128) && (b>71) && (b<89) )      //           lcd_draw_rectangle(120, 80, 25,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>18) && (a<85) && (b>71) && (b<89) )      //            lcd_draw_rectangle(52, 80, 51,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>52) && (a<128) && (b>48) && (b<64) )      //            lcd_draw_rectangle(100, 55, 77,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>22) && (a<110) && (b>21) && (b<39) )      //             lcd_draw_rectangle(65, 30, 77,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>105) && (a<128) && (b>0) && (b<12) )      //              lcd_draw_rectangle(120,3, 33,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>0) && (a<75) && (b>0) && (b<14) )      //              lcd_draw_rectangle(30, 3, 77,LINE_WIDTH,LCD_COLOR_WHITE);
        {
             return false;

        }
    else if ( (a>18) && (a<60) && (b>120) && (b<128) )      //              lcd_draw_rectangle(40, 128, 25,LINE_WIDTH,LCD_COLOR_WHITE);
    {
        bool a = true;

        while(a)
        {

            while(BLANK == 0)
            {
            maze_blank();
            BLANK++;
            }

            // **  YOU WIN !!! **
            lcd_draw_image(
                               65,
                               65,
                               winWidthPixels,
                               winHeightPixels,
                               winBitmaps,
                               LCD_COLOR_ORANGE,
                               LCD_COLOR_BLACK
                       );
            lcd_draw_image(
                x,
                y,
                circleWidthPixels,
                circleHeightPixels,
                circleBitmaps,
                LCD_COLOR_BLACK,
                LCD_COLOR_BLACK);


            if(ece353_MKII_S1())
          {
                BLANK = 0;
                lcd_draw_image(
                                   65,
                                   65,
                                   winWidthPixels,
                                   winHeightPixels,
                                   winBitmaps,
                                   LCD_COLOR_BLACK,
                                   LCD_COLOR_BLACK
                           );

                lcd_draw_image(
                    x,
                    y,
                    circleWidthPixels,
                    circleHeightPixels,
                    circleBitmaps,
                    LCD_COLOR_BLACK,
                    LCD_COLOR_BLACK);

            x = 85;
            y = 13;

            a = false;
        COUNT = 0;
        }
        }
        return true;
    }


    else
     {
        return true;
     }
}

/******************************************************************************
* Depending on the ADC data, this function checks if the circle moves within the given boundaries
* Return true if the circle is within the boundaries
******************************************************************************/
bool Check_Boundaries(int x, int y, int z)
{
   int p;
   int q;

   if(z == 1) // move left
   {
       p = x - 1;
       q = y;
   }
   else if(z == 2) // move right
   {
       p = x + 1;
       q = y;
   }
   else if(z == 3) // move down
   {
       p = x;
       q = y + 1;
   }
   else if(z == 4) // move up
   {
       p = x;
       q = y - 1;
   }

   if(Check_Boundaries_Helper(p,q))
   {
       return true;
   }
   else
   {
       return false;
   }
}

/******************************************************************************
 * This task manages the movement of the space ship. The joystick task or the
 * console task can send messages to SHIP_QUEUE_LEN
 ******************************************************************************/
void Task_Circle(void *pvParameters)
{

    SHIP_MSG_t msg;
    BaseType_t status;
    int speed = 25;

    // Draw the initial starting image of the spaceship.
    lcd_draw_image(
            x,
            y,
            circleWidthPixels,
            circleHeightPixels,
            circleBitmaps,
            color,
            LCD_COLOR_BLACK
    );

    while(1)
    {
        // Wait until we receive a message in Queue_Console
        status = xQueueReceive(Queue_Circle, &msg, portMAX_DELAY);

        /*
         * Based on the message that was received, perform appropriate action
         */
        if (msg.cmd == SHIP_CMD_SPEED){
            speed = msg.value;
        }
        else if (msg.cmd == SHIP_CMD_LEFT){
            int i;
            for (i=0; i<msg.value; i++){
                // Check if within bounds
                if (x > 1+circleWidthPixels/2){
                if(Check_Boundaries(x, y, 1))
                {
                    // Update vals
                    x--;
                // Draw ship
                    lcd_draw_image(
                            x,
                            y,
                            circleWidthPixels,
                            circleHeightPixels,
                            circleBitmaps,
                            color,
                            LCD_COLOR_BLACK
                    );
                    valid_movement();
                }
                else
                {
                    lcd_draw_image(
                            x+1,
                            y,
                            circleWidthPixels,
                            circleHeightPixels,
                            circleBitmaps,
                            color,
                            LCD_COLOR_BLACK
                    );

                    invalid_movement();
                }
                maze_init();
                    // Delay
                    vTaskDelay(pdMS_TO_TICKS(speed));

                }
            }
        }

        else if (msg.cmd == SHIP_CMD_RIGHT){
            int i;
            for (i=0; i<msg.value; i++){
                // Check if within bounds
                if (x < 131-circleWidthPixels/2){
                if(Check_Boundaries(x, y, 2))
                {
                    // Update vals
                    x++;
                // Draw ship
                    lcd_draw_image(
                            x,
                            y,
                            circleWidthPixels,
                            circleHeightPixels,
                            circleBitmaps,
                            color,
                            LCD_COLOR_BLACK
                    );
                    valid_movement();
                }
                else
                {
                    lcd_draw_image(
                            x-1,
                            y,
                            circleWidthPixels,
                            circleHeightPixels,
                            circleBitmaps,
                            color,
                            LCD_COLOR_BLACK
                    );

                    invalid_movement();
                }
                maze_init();
                    // Delay
                    vTaskDelay(pdMS_TO_TICKS(speed));

                }
            }
        }

        else if (msg.cmd == SHIP_CMD_UP){
            int i;
            for (i=0; i<msg.value; i++){
                // Check if within bounds
                if (y > 2+circleHeightPixels/2){
                    if(Check_Boundaries(x, y, 4))
                    {
                // Update vals
                    y--;
                // Draw ship
                    lcd_draw_image(
                            x,
                            y,
                            circleWidthPixels,
                            circleHeightPixels,
                            circleBitmaps,
                            color,
                            LCD_COLOR_BLACK
                    );
                    valid_movement();
                    }
                    else
                    {
                        lcd_draw_image(
                                x,
                                y+1,
                                circleWidthPixels,
                                circleHeightPixels,
                                circleBitmaps,
                                color,
                                LCD_COLOR_BLACK
                        );

                        invalid_movement();
                    }
                    maze_init();
                    // Delay
                    vTaskDelay(pdMS_TO_TICKS(speed));

                }
            }
        }

        else if (msg.cmd == SHIP_CMD_DOWN){
            int i;
            for (i=0; i<msg.value; i++){
                // Check if within bounds
                if (y < 131-circleHeightPixels/2){
                    if(Check_Boundaries(x, y, 3))
                    {
                // Update vals
                    y++;
                // Draw ship
                    lcd_draw_image(
                            x,
                            y,
                            circleWidthPixels,
                            circleHeightPixels,
                            circleBitmaps,
                            color,
                            LCD_COLOR_BLACK
                    );
                    valid_movement();
                    }
                    else
                    {
                        lcd_draw_image(
                                x,
                                y-1,
                                circleWidthPixels,
                                circleHeightPixels,
                                circleBitmaps,
                                color,
                                LCD_COLOR_BLACK
                        );

                        invalid_movement();
                    }
                    maze_init();
                    // Delay
                    vTaskDelay(pdMS_TO_TICKS(speed));

                }
            }
        }

        else if  (msg.cmd == SHIP_CMD_CENTER){
            valid_movement();
            lcd_draw_image(
                    x,
                    y,
                    circleWidthPixels,
                    circleHeightPixels,
                    circleBitmaps,
                    color,
                    LCD_COLOR_BLACK
            );
            // Do nothing
        }

        if( COUNT == 3 )
        {
            // Print Defeat
            while(COUNT == 3)
            {

                while(BLANK == 0)
                {
                maze_blank();
                BLANK++;
                }
                // Turn on the Blue LED ** Game Over **
                lcd_draw_image(
                                        65,
                                        65,
                                        loseWidthPixels,
                                        loseHeightPixels,
                                        loseBitmaps,
                                        LCD_COLOR_ORANGE,
                                        LCD_COLOR_BLACK);

                if(ece353_MKII_S1()) // Re-centers the circle when S1 has been pressed
                {
                    BLANK = 0;
                    lcd_draw_image(
                                            65,
                                            65,
                                            loseWidthPixels,
                                            loseHeightPixels,
                                            loseBitmaps,
                                            LCD_COLOR_BLACK,
                                            LCD_COLOR_BLACK);
                COUNT = 0;
                }
            }


        }
    }
}


