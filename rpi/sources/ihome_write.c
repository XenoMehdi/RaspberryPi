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
//#include "ihome_lcd.h"


void ihome_write ( void *prm)
{
  log_print("Write RT Task succes\n");
  unsigned int l_indx ;//, no_message_to_display, cycle_counter = 400; // 400*50 ms = 2s
  cJSON *output, *field, *array;
  char *out, *tmp;

  rt_task_set_periodic(NULL, TM_NOW, 50000000); // 50ms

  while (1) {
    output = cJSON_CreateObject();
    array = cJSON_CreateArray();
    cJSON_AddItemToObject(output, "Outputs", array);

    // update GPIO outputs
    for (l_indx = 0; l_indx < (nb_Of_Output_Elements); l_indx++) // avoid out[7], it's used by op_led task
    {
      if(l_indx == 7) continue;
      
      bcm2835_gpio_write(pins_out[l_indx].pin, ((pins_out[l_indx].value == TRUE ) ? HIGH : LOW ));
      //sprintf(tmp, "output %d", l_indx + 1);
      
      field = cJSON_CreateObject();
      cJSON_AddItemToArray(array, field);
      cJSON_AddStringToObject(field, "name", "to get from a table of names");

      cJSON_AddStringToObject(field, "type",   "RELAY");
      cJSON_AddStringToObject(field, "value", ((pins_out[l_indx].value == TRUE ) ? "ON" : "OFF"));
      cJSON_AddNumberToObject(field, "pin number", pins_out[l_indx].pin);
      
    }

    out = cJSON_Print(output);
    cJSON_Delete(output);

    FILE *input_file = fopen("/root/outputs_states.json", "w+");
    if (input_file != NULL)
    { fprintf(input_file, "%s\n", out);
      fclose(input_file);
    }
    free(out);


    //no_message_to_display = TRUE ;
    // Update message displayed on lcd's screen
    /* for (l_indx = 0; l_indx < nb_OF_ACTIVE_MESSAGES && cycle_counter == 400; l_indx++ )
     {
       // For each element of active messages, if id is different of NO_ACTIVE_MESSAGE then print message

       if (active_message_list[l_indx].id_message != NO_ACTIVE_MESSAGE)
       {
         if ( active_message_list[l_indx].printed_to_lcd == FALSE )
         {
           ihome_lcd_write ( messages_list_cst[
                               active_message_list[l_indx].id_message
                             ].lcd_message ) ;
           // pthread_mutex_lock(&active_message_list[l_indx].mutex);

           // pthread_mutex_unlock(&active_message_list[l_indx].mutex);
           //nanosleep((struct timespec[]) {{2, 0}}, NULL);
           cycle_counter = 0 ;
           active_message_list[l_indx].printed_to_lcd = TRUE ;
         }
       }
       if(l_indx == nb_OF_ACTIVE_MESSAGES-1)
         no_message_to_display = FALSE ;
     }

     //log_print("display messages on LCD\n");
     if (no_message_to_display == FALSE )
       ihome_lcd_write ( messages_list_cst[NO_ACTIVE_MESSAGE].lcd_message );
    */
    rt_task_wait_period(NULL);
    //  cycle_counter = (cycle_counter++) % 401;
  }
}
