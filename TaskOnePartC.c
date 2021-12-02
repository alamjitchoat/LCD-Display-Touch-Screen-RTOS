/*
*Alamjit Choat
* 1962902
* 08/10/2020
* This program uses a LCD screen and a ADC to calculate the tiva
board's temperatures and print them to the screen.
*/

#include <stdio.h>
#include "lab4.h"
#include "SSD2119_Display.h"
#include "Lab_3_Header.h"
#include "Lab_3_Driver.h"

// main method to create two external buttons on the LCD screen used to 
//   manipulate the frequency and print the correct values. 
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
    init_ADC();
    Touch_Init();   
    unsigned short RED = ((0xAA>>3)<<11) | ((0x00>>2)<<5) | (0x00>>3);
    unsigned short BLUE = ((0x00>>3)<<11) | ((0x00>>2)<<5) | (0xAA>>3);
    float tempC = 0;
    float tempF = 0;
    char buffer[100];
    
    while (1) {  
    unsigned long x = Touch_ReadX();
    unsigned long y = Touch_ReadY();      
    LCD_DrawFilledRect(0, 0, 40, 40, RED);
    LCD_DrawFilledRect(200, 0, 40, 40, BLUE);
    LCD_SetCursor(00, 60);
      if (ADCRIS == 0x08) {
        tempC = (147.5 - (247.5 * ADCSSFIFO3) / 4096.0);
        tempF = (tempC * (9/5)) + 32;
        ADCISC = 0x08;
        ADCACTSS |= 0x08; 
      }
      if (((x > 600) && (x < 1100)) && y > 1500) {
          freq = PRESET3;
          PLL_Init(freq);        
      } else if (((x > 1600) && (x < 2000)) && y > 1500) {
          freq = PRESET1;      
          PLL_Init(freq);        
      }
      sprintf(buffer, "The current temperature is %.2f C, %.2f F.\n\r The current clock frequency is %d MHz.\n", tempC, tempF, freq);
      LCD_PrintString(buffer);
    }
}

// method to initalize the ADC.
void init_ADC(void) {
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  RCGCADC |= 0x1; // Enable the ADC clock
  ADCACTSS = 0x0; // Disabling the sample sequencer
  ADCCC = 0x2; // Select PISOC in ADCCC
  ADCEMUX |= (0xf << 12); // Software trigger
  ADCSSMUX3 = 0x0; // Select ADC input channel
  ADCSSCTL3 |= 0xE; //Single ended option
  ADCACTSS |= 0x08; //Enable sequencer SS3
  ADCPSSI |= 0x08; // New conversion 
  ADCSSTSH3 = 0x4; 
}
