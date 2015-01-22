/**
 *	write to lcd the message passed as parameter.
 *
 *  @Module   ihome_lcd_write
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
  
 #define lcd_Write_4bits_M(cmd)     bcm2835_gpio_write(lcd_pins[2], (cmd & 0x01 != 0) ? HIGH : LOW); \
                                    bcm2835_gpio_write(lcd_pins[3], (cmd & 0x02 != 0) ? HIGH : LOW); \
                                    bcm2835_gpio_write(lcd_pins[4], (cmd & 0x04 != 0) ? HIGH : LOW); \
                                    bcm2835_gpio_write(lcd_pins[5], (cmd & 0x08 != 0) ? HIGH : LOW); \ 
                                    bcm2835_gpio_write(lcd_pins[1], HIGH); \
                                    bcm2835_gpio_write(lcd_pins[1], LOW);
 
 #define lcd_Write_M(cmd)   bcm2835_gpio_write(lcd_pins[0], HIGH); \
                            lcd_Write_4bits_M( (cmd & 0xf0) >> 4 ); \
                            lcd_Write_4bits_M( (cmd & 0x0f) ); \
                            delayMicroseconds(400);
 
 #define lcd_clear_M()      bcm2835_gpio_write(lcd_pins[0], LOW);  \
                            lcd_Write_4bits_M( 0x01 );
 
 #define lcd_move_first_line _M()   bcm2835_gpio_write(lcd_pins[0], LOW); \
                                    lcd_Write_4bits_M( 0x80 );
 
 #define lcd_move_second_line _M()  bcm2835_gpio_write(lcd_pins[0], LOW); \
                                    lcd_Write_4bits_M( 0xc0);    
 void ihome_lcd_write ( lcd_message_t lcd_message )
 {
  lcd_clear_M ()

// move to first line and write first message
lcd_move_first_line _M()
do{
     lcd_Write_M(lcd_message.lcd_line_1[l_indx])
 }
 while(lcd_message.lcd_line_1[++l_indx] != '\0');

 // move to second line and write second message
 lcd_move_second_line _M()
 do{
    lcd_Write_M(lcd_message.lcd_line_2[l_indx])
 }
 while(lcd_message.lcd_line_1[++l_indx] != '\0');
 
 }
