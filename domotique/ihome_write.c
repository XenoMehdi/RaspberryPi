/**
 *	description : write data output to gpio.
 *
 *  @Module     ihome_write
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
 *	 - January 16, 2015
 *	 - first issue
 *	
 */
#include <time.h>
#include "ihome_public.h"
#include "ihome_lcd.h"


void *ihome_write ( void *prm)
{
  unsigned int l_indx, activate_sleep, no_message_to_display ;

  while(1){
  // update GPIO outputs
  for(l_indx=0; l_indx<nb_Of_Output_Elements; l_indx++)
	{
	bcm2835_gpio_write(pins_out[l_indx], ((outputs_Array_Of_Elements[l_indx].value == TRUE ) ? HIGH : LOW ));
	}

    no_message_to_display = 1 ;
  // Update message displayed on lcd's screen
  for (l_indx = 0; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
  {
    // For each element of active messages, if id is different of NO_ACTIVE_MESSAGE then print message
    activate_sleep = 0 ;
    pthread_mutex_lock(&active_message_list[l_indx].mutex);
    if (active_message_list[l_indx].id_message != NO_ACTIVE_MESSAGE)
    {
      if ( active_message_list[l_indx].printed_to_lcd == FALSE )
      {
        ihome_lcd_write ( messages_list_cst[
			active_message_list[l_indx].id_message
			].lcd_message ) ;
        active_message_list[l_indx].printed_to_lcd = TRUE ;
	activate_sleep = 1 ; no_message_to_display = 0 ;
      }
    }
    pthread_mutex_unlock(&active_message_list[l_indx].mutex);

    if(activate_sleep == 1 ) 
	usleep(2000000) ;
    else
	usleep(100000) ;
  }
    // if no message to display, display home message
    if(no_message_to_display == 1 )
	ihome_lcd_write ( messages_list_cst[NO_ACTIVE_MESSAGE] )
;
 }
}
