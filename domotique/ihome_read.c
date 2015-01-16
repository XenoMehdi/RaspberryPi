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
  while(1)
  {
  // update GPIO outputs
  for(l_indx=0; l_indx<nb_Of_Input_Elements; l_indx++)
	{
	inputs_Array_Of_Elements[l_indx].value = (digitalRead(pins_in[l_indx]) == HIGH)? TRUE : FALSE );
	}
    usleep(100000);
  }
}
