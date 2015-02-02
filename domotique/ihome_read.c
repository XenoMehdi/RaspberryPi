/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_read                                                    *
*                                                                              *
*  Description : read all inputs and save them into an array.                  *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
*********************************************************************************/
#include <time.h>
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
  
  
    usleep(100000);
  }
}
