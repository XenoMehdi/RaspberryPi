/**
 *  activation point for iHome Software.
 *
 *  @Module     ihome_app
 *  @author     El Mehdi El Fakir
 *  @email      elmehdi@elfakir.me
 *  @website    --
 *  @link       --
 *  @compiler   GCC
 *  @hardware   Raspberry Pi B+
 *  @license    GNU GPL v3
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
 *  Version 1.1
 *   - January 22, 2015
 *   - change usage of wiringPi by bcm2835 lib
 */
#include "ihome_public.h"
#include <sys/mman.h>


int threads_rtn[nb_Of_Threads];
int ihome_init_status ;
int main( )
{
  int l_indx ;
  ihome_init_status = ihome_initialize () ;
  log_print("initialization\n") ;


  threads_rtn [0] = rt_task_create (&write_thread,    WRITE_TASK_NAME,   WRITE_TASK_STKSZ,    WRITE_TASK_PRIO, WRITE_MODE); //T_JOINABLE, ihome_write, NULL) ;
  threads_rtn [1] = rt_task_create (&read_thread,     READ_TASK_NAME,    READ_TASK_STKSZ,     READ_TASK_PRIO,  READ_MODE); //T_JOINABLE, ihome_read, NULL) ;
  threads_rtn [2] = rt_task_create (&monitor_thread,  MONITOR_TASK_NAME,   MONITOR_TASK_STKSZ,    MONITOR_TASK_PRIO, MONITOR_MODE); //T_JOINABLE, ihome_monitor, NULL) ;
  threads_rtn [3] = rt_task_create (&update_thread,   UPDATE_TASK_NAME,   UPDATE_TASK_STKSZ,    UPDATE_TASK_PRIO, UPDATE_MODE); //T_JOINABLE, ihome_update, NULL) ;
  threads_rtn [4] = rt_task_create (&write_messages_thread,   WRITE_MESSAGES_TASK_NAME,   WRITE_MESSAGES_TASK_STKSZ,    WRITE_MESSAGES_TASK_PRIO, WRITE_MESSAGES_MODE); //T_JOINABLE, ihome_write_messages, NULL) ;
  threads_rtn [4] = rt_task_create (&op_led_thread,   OP_LED_TASK_NAME,   OP_LED_TASK_STKSZ,    OP_LED_TASK_PRIO, OP_LED_MODE);

  if ( (threads_rtn [0] || threads_rtn [1] || threads_rtn [2] || threads_rtn [3] || threads_rtn [4] || threads_rtn [5] ) == 0 )
  {
    log_print("creation of rt tasks succes\n");

    rt_task_start(&write_thread, ihome_write, NULL);
    rt_task_start(&read_thread, ihome_read, NULL);
    rt_task_start(&monitor_thread, ihome_monitor, NULL);
    rt_task_start(&update_thread, ihome_update, NULL);
    rt_task_start(&write_messages_thread, ihome_write_messages, NULL);
    rt_task_start(&op_led_thread, ihome_op_led, NULL);
  }
  else
  {
    log_print("creation of rt tasks fail\n");
    return -1;
  }

  if (  ihome_init_status == 0 )
  {
    for (l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
    {
      if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
      {
        active_message_list[l_indx].id_message = MESSAGE_5 ;
        l_indx = nb_OF_ACTIVE_MESSAGES ;
      }
    }
  }


  rt_task_join ( &write_thread ) ;
  rt_task_join ( &read_thread ) ;
  rt_task_join ( &monitor_thread ) ;
  rt_task_join ( &update_thread ) ;
  rt_task_join ( &write_messages_thread ) ;
  rt_task_join ( &op_led_thread ) ;

  /* close the created sockets */
//close(socket_monitor);
//close(socket_read);

  /* close bcm2835 drivers */
  bcm2835_close();
  log_print("the end\n");
// fclose(log_file_desc);
  return 0;
}
