/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_update                                                  *
*                                                                              *
*  Description : update outputs array depending on inputs array.               *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
********************************************************************************/
#include <time.h>
#include "ihome_public.h"

void *ihome_update ( void *prm)
{

while(1)
{
context_object_t *l_ptr ;

for( l_ptr = &context_pile ; l_ptr != NULL ; l_ptr = l_ptr->next )
{
	if ( l_ptr->config->type_of_output == NORMAL_RELAY )
	{
		l_ptr->output->value = (l_ptr->config->active_on_high == TRUE) ? 
					l_ptr->input->value : !l_ptr->input->value ;
	}
}

usleep(100000);
}
}
