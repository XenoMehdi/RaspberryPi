/**
 *  declaration of all Software's datas.
 *
 *  @Module   ihome_data
 *	@author 	El Mehdi El Fakir
 *	@email		elmehdi@elfakir.me
 *	@website	--
 *	@link		  --
 *	@version 	v1.0
 *	@compiler GCC
 *  @hardware Raspberry Pi B+
 *	@license	GNU GPL v3
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
// Array of input elements.
input_object_t inputs_Array_Of_Elements [ nb_Of_Input_Elements ];
const input_object_t input_object_cst   = { FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER } ;

// Array of output elements.
output_object_t outputs_Array_Of_Elements [ nb_Of_Output_Elements ];
const output_object_t output_object_cst = { FALSE, FALSE, PTHREAD_MUTEX_INITIALIZER } ;

// List of defined messages 
const messages_object_t messages_list_cst [ nb_Of_Messages ] = {
                {NO_ACTIVE_MESSAGE, {"",""}, "" },
                {MESSAGE_1, {"","LCD init fail"}, "LCD Initialization failed." },
                {MESSAGE_2, {"","LCD init success"}, "LCD Initialization success." },
                {MESSAGE_3, {"software init","successfully"}, "Initialization of Software's data success." }
};

// list of active messages to send to server and to print on LCD
active_message_t active_message_list [ nb_OF_ACTIVE_MESSAGES] ;
const active_message_t active_message_init_cst = {NO_ACTIVE_MESSAGE, FALSE, FALSE} ;

// active software configuration
sw_configuration_t software_configuration ;

// default software configuration
const sw_configuration_t software_configuration_default = 3 ; // set lcd and backlight on

// LCD driver handler
int  lcd_handler ;
