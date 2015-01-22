/**
 *  initialize the lcd with passed pins, return 0 if success and -1 if not.
 *
 *  @Module   ihome_lcd_initialize
 *  @author 	El Mehdi El Fakir
 *  @email		elmehdi@elfakir.me
 *  @website	--
 *  @link		  --
 *  @version 	v1.0
 *  @compiler GCC
 *  @hardware Raspberry Pi B+
 *  @license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) FEZ EMBEDDED SYSTEMS INDUSTRY, 2015
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 *	
 *	Version 1.0
 *	 - January 09, 2015
 *	 - first issue
 *	
 */

 #include "ihome_lcd.h"
 #include "ihome_public.h"
 #include <bcm2835.h>
 
 #define lcd_Write_4bits_M(cmd)     bcm2835_gpio_write(lcd_pins[2], (cmd & 0x01 != 0) ? HIGH : LOW); \
                                  bcm2835_gpio_write(lcd_pins[3], (cmd & 0x02 != 0) ? HIGH : LOW); \
                                  bcm2835_gpio_write(lcd_pins[4], (cmd & 0x04 != 0) ? HIGH : LOW); \
                                  bcm2835_gpio_write(lcd_pins[5], (cmd & 0x08 != 0) ? HIGH : LOW); \ 
                                  bcm2835_gpio_write(lcd_pins[1], HIGH); \
                                  bcm2835_gpio_write(lcd_pins[1], LOW);
 
 #define lcd_Write_M(cmd)         lcd_Write_4bits_M( (cmd & 0xf0) >> 4 ); lcd_Write_4bits_M( (cmd & 0x0f) ); delayMicroseconds(400);
 
 int  ihome_lcd_initialize (const unsigned int *pins)
 {
 int lreturn = 0 ;
  for(int l_indx=0; l_indx<7; l_indx++)
  {
  bcm2835_gpio_fsel(pins[l_indx], BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_set_pud(pins[l_indx], BCM2835_GPIO_PUD_UP);
  }
  
  //turn LCD power and backlight ON or OFF
  if (software_configuration.options.turn_LCD_Backlight == ON)
  {
  bcm2835_gpio_write(lcd_pins[6], HIGH);
  }
  else
  {
  bcm2835_gpio_write(lcd_pins[6], LOW);
  }
  
  // lcd initialization - Reset phase
  bcm2835_gpio_write(lcd_pins[0], LOW); // Set RS to 0 for command
  lcd_Write_4bits_M ( 0x03 );             // Send 0x03 for 15ms
  delay(15);
  lcd_Write_4bits_M ( 0x03 );             // Send 0x03 for 1ms
  delay(1);
  lcd_Write_4bits_M ( 0x03 );             // Send 0x03 for 1ms
  delay(1);
  lcd_Write_4bits_M ( 0x02 );             // Send 0x02 for 1ms
  delay(1);
  
  // lcd initialization - Configuration phase
  lcd_Write_M(0x28);  // 4-bit mode - 2 line - 5x7 font.
  lcd_Write_M(0x0c);  // Display no cursor - no blink.
  lcd_Write_M(0x06);  // Automatic Increment - No Display shift.
  lcd_Write_M(0x80);  // Address DDRAM with 0 offset 80h.
  
  return lreturn;
 }
