/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_initialize                                              *
*                                                                              *
*  Description : initialize all software's datas.                              *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
********************************************************************************

#include "ihome_public.h"


void *ihome_initialize ( void )
{

// local data
unsigned int l_indx = 0 ;

// initialize the input array
for ( l_indx = 0 ; l_indx < nb_Of_Input_Elements ; l_indx++ )
{
  inputs_Array_Of_Elements [l_indx] = input_object_cst ;
}

// initialize the output array
for ( l_indx = 0 ; l_indx < nb_Of_Output_Elements ; l_indx++ )
{
  outputs_Array_Of_Elements [l_indx] = output_object_cst ;
}

// initialize the active messages array
for ( l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
{
  active_message_list [l_indx] = active_message_default_cst ;
}

}
