/**
 *  declaration of data to monitor task.
 *
 *  @Module   ihome_monitor_data
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
 *	 - January 14, 2015
 *	 - first issue
 */
#include "ihome_private_private.h"


/**********************/
/* Private Data       */
/**********************/

/* server configuration */
int   port =    80;
char *host =    "data.sparkfun.com";
char *http_request = 
"POST /input/ZGKndY934ZCGMvVqbxVq?private_key=%s&input_buffer=%s&message_buffer=%s&output_buffer=%s HTTP/1.1\n\n";

/* socket data */ 
struct hostent *server;
struct sockaddr_in serv_addr;
int sockfd, bytes, sent, received, total, l_indx;

/* sent and received messages */
char message[1024],response[500], *e1, *e2;

/* http post request fields */
char *private_key = "2mP7ZjdbvVcbn8m92Vm9" ;
char input_buffer  [ 2*nb_Of_Input_Elements - 1 ];
char output_buffer [ 2*nb_Of_Output_Elements - 1 ];
char message_buffer [ 57*nb_OF_ACTIVE_MESSAGES - 2 ]; // 55 char per message + 2 for , & space

