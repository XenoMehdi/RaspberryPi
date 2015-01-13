/**
 *  send monitoring message to IoT server.
 *
 *  @Module   ihome_monitor
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
 *	 - January 13, 2015
 *	 - first issue
 */

#include "ihome_public.h"

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

void error(const char *msg) { perror(msg); exit(0); }

void *ihome_monitor ( void *prm)
{
  /* first what are we going to send and where are we going to send it? */
    int portnbr =       80;
    char *host =        "data.sparkfun.com";
    char *message_fmt = 
  "POST /input/ZGKndY934ZCGMvVqbxVq?private_key=%s&input_buffer=%s&message_buffer=%s&output_buffer=%s HTTP/1.1\n\n";
    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, l_indx;
    char message[1024],response[500], *e1, *e2;
    while(1){
//printf("Monitor is running\n");
    /* fill in the parameters */
    sprintf(message,message_fmt,"2mP7ZjdbvVcbn8m92Vm9","0:0:0:0:0:0","iHome+monitoring","0:0:0:0:0:0:0");

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnbr);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr_list[0],server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response-received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

   /* process response */
   e1 = strstr(response, "\r\n\r\n");
   if(e1 != NULL)
   {
    e2 = strstr(e1, "1");
    if (e2 == NULL)
    e2 = strstr(e1, "0");
    
    if (e2 != NULL && e2[0] == '0')
    {
	for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  	{
    		if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    		{
      		active_message_list[l_indx].id_message = MESSAGE_6 ;
      		l_indx = nb_OF_ACTIVE_MESSAGES ;
    		}
    		else if ( active_message_list[l_indx].id_message == MESSAGE_6 )
      		{
		l_indx = nb_OF_ACTIVE_MESSAGES ;
		}
  	}
    }
   }
	sleep(10);
	}
}
