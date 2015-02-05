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
 *	Version 1.0
 *	 - January 08, 2015
 *	 - first issue
 *	
 *	Version 1.1
 *	 - January 22, 2015
 *	 - change usage of wiringPi by bcm2835 lib
 */
 #include "ihome_public.h"
 #include <sched.h>
 #include <pthread.h> 
 
 #define nb_Of_Threads 4
 
 pthread_t write_thread ;
 pthread_t read_thread ;
 pthread_t monitor_thread ;
 pthread_t update_thread ;
 
 pthread_attr_t write_attr ;
 pthread_attr_t read_attr ;
 pthread_attr_t monitor_attr ;
 pthread_attr_t update_attr ;
 
 struct sched_param write_param ;
 struct sched_param read_param ;
 struct sched_param monitor_param ;
 struct sched_param update_param ;
 
 int threads_rtn[nb_Of_Threads];
 int ihome_init_status ;
 int main( )
 {
 int l_indx ;

 ihome_init_status = ihome_initialize () ;

 pthread_attr_init ( &write_attr ) ;
 pthread_attr_init ( &read_attr ) ;
 pthread_attr_init ( &monitor_attr ) ;
 pthread_attr_init ( &update_attr ) ;

 pthread_attr_setinheritsched ( &write_attr, PTHREAD_EXPLICIT_SCHED ) ;
 pthread_attr_setinheritsched ( &read_attr, PTHREAD_EXPLICIT_SCHED ) ;
 pthread_attr_setinheritsched ( &monitor_attr, PTHREAD_EXPLICIT_SCHED ) ;
 pthread_attr_setinheritsched ( &update_attr, PTHREAD_EXPLICIT_SCHED ) ;

 pthread_attr_setschedpolicy  ( &write_attr, SCHED_RR ) ;
 pthread_attr_setschedpolicy  ( &read_attr, SCHED_RR ) ;
 pthread_attr_setschedpolicy  ( &monitor_attr, SCHED_RR ) ;
 pthread_attr_setschedpolicy  ( &update_attr, SCHED_RR ) ;

 write_param.sched_priority = 40;
 read_param.sched_priority  = 60 ;
 monitor_param.sched_priority = 70 ;
 update_param.sched_priority = 50 ;

 pthread_attr_setschedparam ( &write_attr, &write_param ) ;
 pthread_attr_setschedparam ( &read_attr, &read_param ) ;
 pthread_attr_setschedparam ( &monitor_attr, &monitor_param ) ;
 pthread_attr_setschedparam ( &update_attr, &update_param ) ;

 threads_rtn [0] = pthread_create (&write_thread,    &write_attr,   ihome_write,    NULL) ;
 threads_rtn [1] = pthread_create (&read_thread,     &read_attr,    ihome_read,     NULL) ;
 threads_rtn [2] = pthread_create (&monitor_thread,  &monitor_attr, ihome_monitor,  NULL) ;
 threads_rtn [3] = pthread_create (&update_thread,   &update_attr,  ihome_update,   NULL) ;

 if ( (threads_rtn [0] || threads_rtn [1] || threads_rtn [2] || threads_rtn [3] ) == 0 )
 {
 printf("Starting iHome...\n");
 }
 else 
 {
 printf("creation of threads fail\n");
 return -1;
 }

 if(  ihome_init_status == 0 )
 {
 for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list[l_indx].id_message = MESSAGE_5 ;
      l_indx = nb_OF_ACTIVE_MESSAGES ;
    }
  }
 }

  pthread_join(write_thread,    NULL) ;
  pthread_join(read_thread,     NULL) ;
  pthread_join(monitor_thread,  NULL) ;
  pthread_join(update_thread,   NULL) ;

 pthread_attr_destroy ( &write_attr ) ;
 pthread_attr_destroy ( &read_attr ) ;
 pthread_attr_destroy ( &monitor_attr ) ;
 pthread_attr_destroy ( &update_attr ) ;
 
 /* close the created sockets */
 close(socket_monitor);
 close(socket_read);

 /* close bcm2835 drivers */
 bcm2835_close();
  
 return 0;
 }
