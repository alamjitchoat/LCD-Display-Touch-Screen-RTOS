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

// main method used to calculate the values and print them to the LCD.
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
    init_switches();
    
    // unsigned short COLOR = ((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3); Task 1A
    // LCD_ColorFill(COLOR); Task 1A 
    float tempC = 0;
    float tempF = 0; 
    char buffer[100];
    
    while (1) {
      if (ADCRIS == 0x08) {
        tempC = (147.5 - (247.5 * ADCSSFIFO3) / 4096.0);
        tempF = (tempC * (9/5)) + 32;
        ADCISC = 0x08;
        ADCACTSS |= 0x08; 
      }
      if (GPIODATA_J == 0x01) {
          freq = PRESET3;
          PLL_Init(freq);        
      } else if (GPIODATA_J == 0x02) {
          freq = PRESET1;       
          PLL_Init(freq);        
      }
      sprintf(buffer, "The current temperature is %.2f C, %.2f F.\n\r The current clock frequency is %d MHz.\n", tempC, tempF, freq);
      LCD_PrintString(buffer);
    }
}

// method to initalize the onboard switches
void init_switches(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1120; 
  delay++; 
  delay++; 
  
  GPIODIR_J = 0x00;
  GPIODEN_J = 0x03;
  GPIOPUR_J = 0x03; 
}

// method to initalize the ADC
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

