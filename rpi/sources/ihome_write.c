/**
 *  description : write data output to gpio.
 *
 *  @Module     ihome_write
 *  @author   El Mehdi El Fakir
 *  @email    elmehdi@elfakir.me
 *  @website  --
 *  @link     --
 *  @version  v1.0
 *  @compiler GCC
 *  @hardware Raspberry Pi B+
 *  @license  GNU GPL v3
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
 *  Version 1.0
 *   - January 16, 2015
 *   - first issue
 *
 */
// avoid implicit declaration of nanosleep
#define _POSIX_C_SOURCE 199309L

#include <sys/time.h>
#include "ihome_public.h"
#include "ihome_lcd.h"


void *ihome_write ( void *prm)
{
  unsigned int l_indx, no_message_to_display ;

  while (1) {
    // update GPIO outputs
    for (l_indx = 0; l_indx < nb_Of_Output_Elements; l_indx++)
    {
      bcm2835_gpio_write(pins_out[l_indx], ((outputs_Array_Of_Elements[l_indx].value == TRUE ) ? HIGH : LOW ));
    }
    no_message_to_display = TRUE ;
    // Update message displayed on lcd's screen
    for (l_indx = 0; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
    {
      // For each element of active messages, if id is different of NO_ACTIVE_MESSAGE then print message

      if (active_message_list[l_indx].id_message != NO_ACTIVE_MESSAGE)
      {
        if ( active_message_list[l_indx].printed_to_lcd == FALSE )
        {
          ihome_lcd_write ( messages_list_cst[
                              active_message_list[l_indx].id_message
                            ].lcd_message ) ;
          no_message_to_display = FALSE ;
          pthread_mutex_lock(&active_message_list[l_indx].mutex);
          active_message_list[l_indx].printed_to_lcd = TRUE ;
          pthread_mutex_unlock(&active_message_list[l_indx].mutex);
          nanosleep((struct timespec[]) {{2, 0}}, NULL);
        }
      }

    }
    //log_print("display messages on LCD\n");
    if (no_message_to_display == FALSE )
      ihome_lcd_write ( messages_list_cst[NO_ACTIVE_MESSAGE].lcd_message );
    nanosleep((struct timespec[]) {{0, 5000000}}, NULL);

  }
}
