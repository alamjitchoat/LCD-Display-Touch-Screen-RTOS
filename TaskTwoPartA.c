/*
*Alamjit Choat
* 1962902
* 08/10/2020
* This program uses a LCD screen and a timer to implement the traffic light
    scenario from the previous lab.  
*/

#include <stdio.h>
#include "lab4.h"
#include "SSD2119_Display.h"
#include "Lab_3_Header.h"
#include "Lab_3_Driver.h"

// state idle everythings off
// state green ability to go to yellow and oscillate between red and green
// state yellow go from yellow to red
// state red delay than enter state green
enum states {green, yellow, red, idle}state;

// main method used to switch between states and use the
//      LCD screen accordingly. 
int main() {
    // Select system clock frequency preset
    //
    // For lab task requirement:
    //   - Select PRESET 2 (60 MHz) to be the initial system clock frequency
    //   - Clock frequency stay at 60 MHz if no user switches are pressed
    //   - Change clock frequency to 12 MHz if SW 1 is pressed
    //   - Change clock frequency to 120 MHz if SW 2 is pressed
    enum frequency freq = PRESET2;
    PLL_Init(freq);             // PLL must be configured before everthing else
    LCD_Init();
    Touch_Init(); 
    initTimer();
   
    unsigned short RED = ((0xAA>>3)<<11) | ((0x00>>2)<<5) | (0x00>>3);
    unsigned short BLUE = ((0x00>>3)<<11) | ((0x00>>2)<<5) | (0xAA>>3);
    unsigned short YELLOW = ((0xFF>>3)<<11) | ((0xFF>>2)<<5) | (0x55>>3);
    unsigned short GREEN = ((0x00>>3)<<11) | ((0xAA>>2)<<5) | (0x00>>3);
    unsigned short BLACK = 0;
    
    state = idle;
    int numOfSeconds;
    int timerCounter = 0; // keeps track of red button
    int timerCounter2 = 0; // keeps track of my blue button 
    LCD_DrawFilledRect(0, 0, 40, 40, RED);
    LCD_DrawFilledRect(200, 0, 40, 40, BLUE); 
    
    while (1) {  
      unsigned long x = Touch_ReadX();
      unsigned long y = Touch_ReadY();       
      if((GPTMRIS_0 & 0x01) == 0x01){
        GPTMICR_0 |= 0x01;
        numOfSeconds++;
      if (((x > 600) && (x < 1100)) && y > 1500)  {
        timerCounter++;
      } else if (((x > 1600) && (x < 2000)) && y > 1500) {
        timerCounter2++; 
      }
    }
    switch(state) {
       case green:
          LCD_DrawFilledCircle(100, 100, 50, GREEN);
          if (numOfSeconds == 5) {
            state = red;
            numOfSeconds = 0;
          } else if (timerCounter2 == 2) {
            state = yellow;
            numOfSeconds = 0;
            timerCounter = 0;
            timerCounter2 = 0;
          } else if (timerCounter == 2) {
            state = idle;
            numOfSeconds = 0;
            timerCounter = 0;
            timerCounter2 = 0;
          }
         break;
      case yellow:
        LCD_DrawFilledCircle(100, 100, 50, YELLOW);
        if (numOfSeconds == 5) {
          state = red;
          numOfSeconds = 0;
          timerCounter = 0;
          timerCounter2 = 0;
        }
        break;
      case red:
        LCD_DrawFilledCircle(100, 100, 50, RED); 
        if (numOfSeconds == 5) {
           state = green;
           numOfSeconds = 0;
        } else if (timerCounter == 2) {
           state = idle; 
           numOfSeconds = 0;
           timerCounter = 0;
           timerCounter2 = 0;
        }
        break;
      case idle:
          LCD_DrawFilledCircle(100, 100, 50, BLACK);
          if (timerCounter == 2) { 
              state = red; 
              timerCounter = 0;
              timerCounter2 = 0;
              numOfSeconds = 0;
          }
          break; 
      }
   }
}

// method to initalize the timer 
void initTimer(void) {
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  RCGCTIMER = 0x01; 
  GPTMCTL_0 = 0x00;
  GPTMCFG_0 = 0x00000000;
  GPTMTAMR_0 = 0x2;
  GPTMTAILR_0 = 0x3938700;
  GPTMCTL_0 = 0x01;
}
