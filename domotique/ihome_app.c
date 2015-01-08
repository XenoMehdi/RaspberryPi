/**
 *	activation point for iHome Software.
 *
 *  @Module   ihome_app
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
 *	
 */
 #include "ihome_public.h"
 
 #define nb_Of_Threads 4
 
 pthread_t write_thread ;
 pthread_t read_thread ;
 pthread_t monitor_thread ;
 pthread_t update_thread ;
 
 int threads_rtn[nb_Of_Threads];
 
 int main( )
 {
 int l_indx ;
 
 ihome_initialize () ;
 
 threads_rtn [0] = pthread_create (write_thread,    NULL, ihome_write,    NULL) ;
 threads_rtn [1] = pthread_create (read_thread,     NULL, ihome_read,     NULL) ;
 threads_rtn [2] = pthread_create (monitor_thread,  NULL, ihome_monitor,  NULL) ;
 threads_rtn [3] = pthread_create (update_thread,   NULL, ihome_update,   NULL) ;
 
 if ( (threads_rtn [0] || threads_rtn [1] || threads_rtn [2] || threads_rtn [3] ) == 0 )
 {
 printf("creation of threads success\n");
 }
 else 
 {
 printf("creation of threads fail\n");
 return -1;
 }
 
 for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list[l_indx].id_message = MESSAGE_3 ;
      l_indx = nb_OF_ACTIVE_MESSAGES
    }
  }
  
  pthread_join(write_thread,    NULL) ;
  pthread_join(read_thread,     NULL) ;
  pthread_join(monitor_thread,  NULL) ;
  pthread_join(update_thread,   NULL) ;
  
 return 0;
 }
