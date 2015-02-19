/* 
* @Project 		: Intelligent Home
* @Module Name 		: ihome_read
* @Author		: E. El Fakir
* @Date			: 2015-01-07 09:02:18
* @Last Modified by	: E. El Fakir
* @Last Modified time	: 2015-02-04 09:02:19
*/

// avoid implicit declaration of nanosleep
#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <sys/time.h>
#include "ihome_public.h"
boolean_t l_socket_failed;


void *ihome_read ( void *prm)
{

/* socket data */ 
struct hostent *server;
struct sockaddr_in serv_addr;
int bytes, sent, received, total, l_indx;

/* sent and received messages */
char response[500], *e1, *e2;

while(1)
  {
  	
  // update GPIO outputs
  for(l_indx=0; l_indx<nb_Of_Input_Elements; l_indx++)
	{
	pthread_mutex_lock( &inputs_Array_Of_Elements[l_indx].mutex ) ;
	inputs_Array_Of_Elements[l_indx].value = (bcm2835_gpio_lev(pins_in[l_indx]) == HIGH)? TRUE : FALSE ;
	pthread_mutex_unlock( &inputs_Array_Of_Elements[l_indx].mutex ) ;
	}

  // update command inputs array from web server
  /* create the socket */
    socket_read = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(host);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr_list[0],server->h_length);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr_list[0],server->h_length);

     l_socket_failed = FALSE ; 
     /* connect the socket */
     if (connect(socket_read,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
     {/* close the socket */
     close(socket_read);
       l_socket_failed = TRUE ;
     }
     
     if(l_socket_failed == FALSE )
{
  /* send the request */
/*  total = strlen(http_get_request);
  sent = 0;
/*  do {*/
//      bytes = write(socket_read,http_get_request+sent,total-sent);
      send(socket_read,http_get_request,total,0);
     /* if (bytes < 0)
      {
	print_error(0,"write");
      }
      if (bytes == 0)
          break;
      sent+=bytes;
  } while (sent < total);
*/
  /* receive the response */
  memset(response,0,sizeof(response));
  total = sizeof(response)-1;
  received = 0;
//  do {
      recv(socket_read,response,total,0);
      //bytes = read(socket_read,response+received,total-received);
    /*  if (bytes < 0)
      {
     close(socket_read);
	print_error(0,"read")
      }
      if (bytes == 0)
          break;
      received+=bytes;
  } while (received < total);
*/
  if (received >= total)
  {
     printf("received data > total in read task \n");
goto end_socket;
//  	print_error(0,"overflow read")
  }

 /* process response */
 e1 = strstr(response, "\r\n\r\n");
 //printf("r) %s\n",response);
 if(e1 != NULL)
 {
  if (e1[4] == '0')
  {
// 	printf("no web command\n");
  }
  else
  {
//	printf("%s\n",e1);
	e2 = strstr (e1, "web_command");
//	e1 = strstr (e2, "\r\n");
//	e2 = strstr (e1+2, "\r\n");
	int number_of_comma = 0;
//	printf("%s",e2);
	for(l_indx=0 ; l_indx<nb_Of_Command_Elements && ( *e2 != '\n') ;  e2++)
{
//	printf("char %c",*e2);

	if(number_of_comma == 2 && *e2 != ':' && *e2 != ',')
	commands_Array_Of_Elements[l_indx++].value = atoi(e2) ;

	if(*e2 == ',') number_of_comma++ ;
}
//	for(l_indx=0 ; l_indx<nb_Of_Command_Elements ; l_indx++)
//		printf("%d ",commands_Array_Of_Elements[l_indx].value);
// printf("%d\n",number_of_comma);

  }

 } 
//printf("Debug Read.c\n" );
end_socket:
    /* close the socket */
     close(socket_read);  
    nanosleep((struct timespec[]){{0, 50000000}}, NULL);
}
  }
}
