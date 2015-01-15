/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_write                                                   *
*                                                                              *
*  Description : write all outputs from array into MCU registers.              *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
********************************************************************************/
#include <time.h>
#include "ihome_public.h"
#include <wiringPi.h>

unsigned int  pins[8] = {15, 16, 1, 4, 5, 6, 10, 11};

void *ihome_write ( void *prm)
{
  unsigned int l_indx, activate_sleep, no_message_to_display ;
  for(l_indx=0; l_indx<nb_Of_Output_Elements; l_indx++)
	{
	pinMode(pins[l_indx], OUTPUT);
	}

  while(1){
  // update GPIO outputs
  for(l_indx=0; l_indx<nb_Of_Output_Elements; l_indx++)
	{
	digitalWrite(pins[l_indx], (outputs_Array_Of_Elements[l_indx].value == 1 ) ? HIGH : LOW );
	}

    no_message_to_display = 1 ;
  // Update message displayed on lcd's screen
  for (l_indx = 0; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
  {
    // For each element of active messages, if id is different of NO_ACTIVE_MESSAGE then print message
    activate_sleep = 0 ;
    pthread_mutex_lock(&active_message_list[l_indx].mutex);
    if (active_message_list[l_indx].id_message != NO_ACTIVE_MESSAGE)
    {
      if ( active_message_list[l_indx].printed_to_lcd == FALSE )
      {
        ihome_write_lcd ( messages_list_cst[
			active_message_list[l_indx].id_message
			].lcd_message ) ;
        active_message_list[l_indx].printed_to_lcd = TRUE ;
	activate_sleep = 1 ; no_message_to_display = 0 ;
      }
    }
    pthread_mutex_unlock(&active_message_list[l_indx].mutex);

    if(activate_sleep == 1 ) 
	usleep(2000000) ;
    else
	usleep(100000) ;
  }
    // if no message to display, display home message
    if(no_message_to_display == 1 )
	ihome_write_lcd ( messages_list_cst[NO_ACTIVE_MESSAGE] );
 }
}
