/**
 *  private data to monitor task.
 *
 *  @Module   ihome_monitor_private
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
#include "ihome_public.h"
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */


/**********************/
/* Private Data       */
/**********************/

/* server configuration */
extern int   port ;
extern char *host ;
extern char *http_request ;

/* socket data */ 
extern struct hostent *server;
extern struct sockaddr_in serv_addr;
extern int sockfd, bytes, sent, received, total, l_indx;

/* sent and received messages */
extern char message[1024],response[500], *e1, *e2;

/* http post request fields */
extern char *private_key ;
extern char input_buffer  [ 2*nb_Of_Input_Elements - 1 ];
extern char output_buffer [ 2*nb_Of_Output_Elements - 1 ];
extern char message_buffer [ 57*nb_OF_ACTIVE_MESSAGES - 2 ]; // 55 char per message + 2 for , & space

