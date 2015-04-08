/**
 *  description : the main algorithm of iHome software.
 *
 *  @Module     ihome_update
 *  @author   El Mehdi El Fakir
 *  @email    elmehdi@elfakir.me
 *  @website  --
 *  @link     --
  * @version  v1.0
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
 *   - January 08, 2015
 *   - first issue
 *
 */
// avoid implicit declaration of nanosleep
#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <sys/time.h>
#include "ihome_public.h"

void ihome_update ( void *prm)
{
  log_print("Update RT Task succes\n");
  unsigned int l_indx ;
  rt_task_set_periodic(NULL, TM_NOW, 50000000);


  while (1)
  {

    context_object_t *l_ptr ;

    for ( l_ptr = context_pile ; l_ptr != NULL ; l_ptr = l_ptr->next )
    {
      if ( l_ptr->config->type_of_output == NORMAL_RELAY )
      {
        l_ptr->output->value = (l_ptr->config->active_on_high == TRUE) ?
                               l_ptr->input->value : !l_ptr->input->value ;
      }
    }
    for (l_indx = 0; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
    {
      // For each element of active messages, if id is different of NO_ACTIVE_MESSAGE then print message
      if (active_message_list[l_indx].id_message != NO_ACTIVE_MESSAGE)
      {
        if ( active_message_list[l_indx].printed_to_lcd == TRUE
             &&  active_message_list[l_indx].sent_to_server == TRUE )
        {
          active_message_list[l_indx].id_message = NO_ACTIVE_MESSAGE ;
        }
      }
    }

    //nanosleep((struct timespec[]){{0, 5000000}}, NULL);
    rt_task_wait_period(NULL);

  }
}
