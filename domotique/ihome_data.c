/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_data                                                    *
*                                                                              *
*  Description : declaration of all Software's datas.                          *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
********************************************************************************
#include "ihome_public.h"

/**********************/
/* Public Data        */
/**********************/
// Array of input elements.
input_object_t inputs_Array_Of_Elements [ nb_Of_Input_Elements ];
const input_object_t input_object_cst   = { FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER } ;

// Array of output elements.
output_object_t outputs_Array_Of_Elements [ nb_Of_Output_Elements ];
const output_object_t output_object_cst = { FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER } ;

// List of defined messages 
const messages_object_t messages_list_cst [ nb_Of_Messages ] = {
                {MESSAGE_1, {"software init","successfully"}, "Initialization of Software's data success." }
};

// list of active messages to send to server and to print on LCD
active_message_t active_message_list [ nb_OF_ACTIVE_MESSAGES] ;
const active_message_t active_message_default_cst = {0, FALSE, FALSE} ;
