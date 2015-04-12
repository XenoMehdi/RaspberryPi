/**
 *  declaration of all Software's datas.
 *
 *  @Module             ihome_data
 *  @author             El Mehdi El Fakir
 *  @email              elmehdi@elfakir.me
 *  @website    --
 *  @link               --
 *  @compiler   GCC
 *  @hardware   Raspberry Pi B+
 *  @license    GNU GPL v3
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
 *      Version 1.0
 *       - January 08, 2015
 *       - first issue
 */

#include "ihome_public.h"

/**********************/
/* Public Data        */
/**********************/
// Arrays of I/O pins
unsigned int  lcd_pins [6] = { 22, 27, 17, 4, 3, 2} ; // RS, E, D4,D5, D6, D7
//unsigned int  pins_in  [nb_Of_Input_Elements]  = { 9, 11, 18, 23, 24, 25,  8,  7};
//unsigned int  pins_out [nb_Of_Output_Elements] = { 5,  6, 13, 19, 26, 12, 16, 20, 10}; // 10 = Backlight, 20 = op_led
digital_pin_t  pins_in  [MAX_SIZE_INPUT_PINS] ;
digital_pin_t  pins_out [MAX_SIZE_OUTPUT_PINS] ;
digital_pin_t  cmd_in   [MAX_SIZE_INPUT_CMD] ;
unsigned char *inout_names [MAX_SIZE_INOUT_NAMES] ;

unsigned int nb_Of_Input_Elements = 0;
unsigned int nb_Of_Command_Elements = 0;
unsigned int nb_Of_Output_Elements = 0;

// Array of input elements.
object_t inputs_Array_Of_Elements [ MAX_SIZE_INPUT_PINS + MAX_SIZE_INPUT_CMD ];
const object_t input_object_cst   = { 0, NULL, NULL, 0} ;

// Array of output elements.
object_t outputs_Array_Of_Elements [ MAX_SIZE_OUTPUT_PINS ];
const object_t output_object_cst = { 0, NULL, NULL, 0} ;

// List of defined messages
const messages_object_t messages_list_cst [ nb_Of_Messages ] = {
  {{"     iHome", "    Running"}, {"iHome+is+running"} }, // NO_ACTIVE_MESSAGE
  {{"    WELCOME", ""}, {"Welcome"} },                    // MESSAGE_1
  {{" COPYRIGHT 2015", "     F.E.S.I"}, {"Copyright+2015+F.E.S.I"} }, // MESSAGE_2
  {{"", "LCD INIT FAILED"}, {"LCD+Initialization+failed"} },              // MESSAGE_3
  {{"", "LCD INIT SUCCESS"}, {"LCD+Initialization+success"} },            // MESSAGE_4
  {{" SOFTWARE INIT", "  SUCCESSFULLY"}, {"Initialization+of+Software+data+success"} }, // MESSAGE_5
  {{"SEND DATA TO", "phant.io FAIL"}, {""} }, // MESSAGE_6
  {{"TURN OUTPUT %D", "    ON    "}, {"Turn+Output+%d+ON"}},       // MESSAGE_7
  {{"TURN OUTPUT %D", "    OFF    "}, {"Turn+Output+%d+OFF"}},       // MESSAGE_8
  {{"the system is", "going down..."}, {"Turn+Output+%d+OFF"}}// MESSAGE_9
  // MESSAGE_10
};

// lcd handler
int lcd_handler = 0;

// list of active messages to send to server and to print on LCD
active_message_t active_message_list [ nb_OF_ACTIVE_MESSAGES] ;
const active_message_t active_message_init_cst = {NO_ACTIVE_MESSAGE, FALSE, FALSE} ;

// active software configuration
sw_configuration_t software_configuration ;

// default software configuration
const sw_configuration_t software_configuration_default = {3} ; // set lcd and backlight on

// initialize context pile with the first input, output and confiduration in the array : to be updated
config_object_t config_Array_Of_Elements [ nb_Of_Config_Elements ];
context_object_t *context_pile ;
context_object_t context_1 = { &inputs_Array_Of_Elements[0],
                               &outputs_Array_Of_Elements[0],
                               &config_Array_Of_Elements[0],
                               NULL,
                               NULL
                             };

context_object_t context_2 = { &inputs_Array_Of_Elements[1],
                               &outputs_Array_Of_Elements[1],
                               &config_Array_Of_Elements[0],
                               NULL,
                               NULL
                             };
context_object_t context_3 = { &inputs_Array_Of_Elements[0],
                               &outputs_Array_Of_Elements[2],
                               &config_Array_Of_Elements[0],
                               NULL,
                               NULL
                             };
context_object_t context_4 = { &inputs_Array_Of_Elements[1],
                               &outputs_Array_Of_Elements[3],
                               &config_Array_Of_Elements[0],
                               NULL,
                               NULL
                             };
context_object_t context_5 = { &inputs_Array_Of_Elements[7],
                               &outputs_Array_Of_Elements[8],
                               &config_Array_Of_Elements[0],
                               NULL,
                               NULL
                             };


/* server configuration */
int   port =    80;
char *host =    "data.sparkfun.com";
//int   port =    8080;
//char *host =    "192.168.1.99";
//char *private_key="wVKpKplDbXfY092Ekzq6H0v9adPQ"; // local
char *private_key = "2mP7ZjdbvVcbn8m92Vm9"; // sparkfun
char *http_post_request =
//sparkfun
  "POST /input/ZGKndY934ZCGMvVqbxVq?private_key=%s&input_buffer=%s&message_buffer=%s&output_buffer=%s&cmd_buffer=rpi_cmd: HTTP/1.1\n\n";
//local
//"POST /input/lqopopxBV0fLw2abxBAmTwPYlKXz?private_key=%s&input_buffer=%s&message_buffer=%s&output_buffer=%s&cmd_buffer=rpi_cmd: HTTP/1.1\n\n";
//local
//char *http_get_request = "GET /output/lqopopxBV0fLw2abxBAmTwPYlKXz.jsonp?page=1&eq[message_buffer]=web_command&gt[timestamp]=now-2min HTTP/1.1\n\n" ;
//sparkfun
char *http_get_request = "GET /output/ZGKndY934ZCGMvVqbxVq.jsonp?page=1&eq[message_buffer]=web_command&gt[timestamp]=now-1min HTTP/1.1\n\n" ;

int   socket_monitor ;
int   socket_read ;

/* Log file descriptor */
FILE *log_file_desc;

// variable to handle signal : if true the main is always in while
boolean_t program_is_running = TRUE;
