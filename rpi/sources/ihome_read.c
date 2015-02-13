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


void *ihome_read ( void *prm)
{

/* socket data */ 

int bytes, sent, received, total, l_indx;

/* sent and received messages */
char message[1024],response[500], *e1, *e2;


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
  
  
    nanosleep((struct timespec[]){{0, 100000000}}, NULL);
  }
}
