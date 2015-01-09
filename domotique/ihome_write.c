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

#include "ihome_public.h"

void *ihome_write ( void *prm)
{
  unsigned int l_indx ;
  // Update outputs
  
  // Update message displayed on lcd's screen
  for (l_indx = 0; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
  {
    // For each element of active messages, if id is different of NO_ACTIVE_MESSAGE then print message
    if (active_message_list[l_indx].id_message != NO_ACTIVE_MESSAGE)
    {
      if ( active_message_list[l_indx].printed_to_lcd == FALSE )
      {
        ihome_write_lcd ( messages_list_cst[l_indx].lcd_message ) ;
        sleep(0.5);
        pthread_mutex_lock(&active_message_list[l_indx].mutex);
        active_message_list[l_indx].printed_to_lcd = TRUE ;
        pthread_mutex_unlock(&active_message_list[l_indx].mutex);
      }
    }
  }
}
