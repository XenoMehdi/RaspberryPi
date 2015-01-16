/**
 *  declaration of all Software's datas.
 *
 *  @Module   ihome_data
 *  @author   El Mehdi El Fakir
 *  @email	  elmehdi@elfakir.me
 *  @website  --
 *  @link		  --
 *  @version  v1.0
 *  @compiler GCC
 *  @hardware Raspberry Pi B+
 *  @license  GNU GPL v3
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
 *	 - January 08, 2015
 *	 - first issue
 */
 
#include "ihome_public.h"

/**********************/
/* Public Data        */
/**********************/
// Arrays of I/O pins
unsigned int  pins_in  [nb_Of_Input_Elements]  = {15, 16, 1, 4, 5, 6, 10, 11};
unsigned int  pins_out [nb_Of_Output_Elements] = {21, 22, 23, 24, 25, 26, 27};

// Array of input elements.
input_object_t inputs_Array_Of_Elements [ nb_Of_Input_Elements ];
const input_object_t input_object_cst   = { FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER } ;

// Array of output elements.
output_object_t outputs_Array_Of_Elements [ nb_Of_Output_Elements ];
const output_object_t output_object_cst = { FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER } ;

// List of defined messages 
const messages_object_t messages_list_cst [ nb_Of_Messages ] = {
                {{"     iHome","    Running"}, {"iHome+is+running"} },
		{{"    WELCOME",""}, {"Welcome"} },
		{{" COPYRIGHT 2015","     F.E.S.I"}, {"Copyright+2015+F.E.S.I"} },
                {{"","LCD INIT FAILED"}, {"LCD+Initialization+failed"} },
                {{"","LCD INIT SUCCESS"}, {"LCD+Initialization+success"} },
                {{" SOFTWARE INIT","  SUCCESSFULLY"}, {"Initialization+of+Software+data+success"} },
                {{"SEND DATA TO","phant.io FAIL"}, {""} }
};

// list of active messages to send to server and to print on LCD
active_message_t active_message_list [ nb_OF_ACTIVE_MESSAGES] ;
const active_message_t active_message_init_cst = {NO_ACTIVE_MESSAGE, FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER} ;

// active software configuration
sw_configuration_t software_configuration ;

// default software configuration
const sw_configuration_t software_configuration_default = {3} ; // set lcd and backlight on

// LCD driver handler
int  lcd_handler ;

// initialize context pile with the first input, output and confiduration in the array : to be updated
config_object_t config_Array_Of_Elements [ nb_Of_Config_Elements ];
context_object_t context_pile = { 
					&inputs_Array_Of_Elements[0],
			                &outputs_Array_Of_Elements[0],
			                &config_Array_Of_Elements[0],
			                NULL,
			                NULL };

