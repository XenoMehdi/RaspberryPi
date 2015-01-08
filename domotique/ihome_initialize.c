/**
 *  initialize all software's datas.
 *
 *  @Module   ihome_initialize
 *	@author 	El Mehdi El Fakir
 *	@email		elmehdi@elfakir.me
 *	@website	--
 *	@link		  --
 *	@version 	v1.0
 *	@compiler GCC
 *  @hardware Raspberry Pi B+
 *	@license	GNU GPL v3
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
 *	 - January 08, 2015
 *	 - first issue
 */

#include "ihome_public.h"
#include <wiringPi.h>
#include <lcd.h>

void *ihome_initialize ( void )
{

// local data
unsigned int l_indx = 0 ;

// initialize the input array
for ( l_indx = 0 ; l_indx < nb_Of_Input_Elements ; l_indx++ )
{
  inputs_Array_Of_Elements [l_indx] = input_object_cst ;
}

// initialize the output array
for ( l_indx = 0 ; l_indx < nb_Of_Output_Elements ; l_indx++ )
{
  outputs_Array_Of_Elements [l_indx] = output_object_cst ;
}

// initialize the active messages array
for ( l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
{
  active_message_list [l_indx] = active_message_init_cst ;
}

// initialize LCD driver handler
lcd_handler = 0;

// initialize wiringPi library to use GPIOs
wiringPiSetup();

// initialize lcd driver
lcd_handler = lcdInit( 2, 16, 4, RS, EN, D4, D5, D6, D7, D_UNUSED, D_UNUSED, D_UNUSED, D_UNUSED) ;

//set LCD POWER and BACKLIGHT pins to out
pinMode(LCD_POWER_ON,   OUTPUT);
pinMode(LCD_BACKLIGHT,  OUTPUT);

//turn LCD power and backlight ON
digitalWrite (LCD_POWER_ON, HIGH) ;
digitalWrite (LCD_BACKLIGHT, HIGH) ;

if(lcd_handler == -1 )
{
  for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list.[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list.[l_indx].id_message = MESSAGE_1 ;
      l_indx = nb_OF_ACTIVE_MESSAGES
    }
  }
}
else 
{
  for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list.[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list.[l_indx].id_message = MESSAGE_2 ;
      l_indx = nb_OF_ACTIVE_MESSAGES
    }
  }
}

}
