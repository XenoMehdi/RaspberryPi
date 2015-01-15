/**
 *	API for iHome Software.
 *
 *  @Module   ihome_public
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
 *	
 */
#include <stdio.h>
#include <pthread.h>

/**********************/
/* Type Declaration   */
/**********************/
// Define the boolean type
typedef unsigned char boolean_t;
#define TRUE ( 1 == 1 )
#define FALSE ( 1 == 0 )
#define nb_OF_ACTIVE_MESSAGES 7

// LCD Pins
#define RS 3
#define EN 2

#define D4 0
#define D5 7
#define D6 9
#define D7 8
#define D_UNUSED 0

#define LCD_POWER_ON  6
#define LCD_BACKLIGHT 14

// define the structure of input object
typedef struct {
  boolean_t       value ;
  boolean_t       validity ;
  pthread_mutex_t mutex ;
} input_object_t ;

typedef enum {
  input_BUTTON_1,
  nb_Of_Input_Elements
} input_element_t ;

// define the structure of output object
typedef struct {
  boolean_t       value ;
  boolean_t       validity ;
  pthread_mutex_t mutex ;
} output_object_t ;

typedef enum {
  output_RLY_LAMP_1,
  output_RLY_LAMP_2,
  output_RLY_LAMP_3,
  output_RLY_LAMP_4,
  nb_Of_Output_Elements
} output_element_t ;

// define an lcd message structure
typedef struct {
  char lcd_line_1 [17] ;
  char lcd_line_2 [17] ;
} lcd_message_t ;

// define a monitoring message structure
typedef struct {
  char message [255] ;
} monitor_message_t ;

typedef enum {
  NO_ACTIVE_MESSAGE,
  MESSAGE_1,
  MESSAGE_2,
  MESSAGE_3,
  MESSAGE_4,
  MESSAGE_5,
  MESSAGE_6,
  MESSAGE_7,
  MESSAGE_8,
  MESSAGE_9,
  MESSAGE_10,
  nb_Of_Messages
} messages_elements_t ;

/* define a structure of message that contains a field for lcd_message      */
/* and a field for monitoring_message with the same meaning but with        */
/* different density, monitoring_message is more detailled than lcd_message */
typedef struct {
  lcd_message_t         lcd_message ;
  monitor_message_t     monitor_message ;
} messages_object_t ;

typedef struct {
  messages_elements_t   id_message ;
  boolean_t             printed_to_lcd ;
  boolean_t             sent_to_server ;
  pthread_mutex_t       mutex ;
} active_message_t ;

typedef enum {
  OFF,
  ON
} pin_state_t ;

// define a structure for software configuration
typedef  union {
    unsigned int word ;
    struct {
      pin_state_t turn_LCD_Power      :1 ;
      pin_state_t turn_LCD_Backlight  :1 ;
    } options ;
} sw_configuration_t ;

// Define configuration structure
/**********************/
/* Public Data        */
/**********************/
// Array of input elements.
extern input_object_t inputs_Array_Of_Elements [ nb_Of_Input_Elements ];
extern const input_object_t input_object_cst;

// Array of output elements.
extern output_object_t outputs_Array_Of_Elements [ nb_Of_Output_Elements ];
extern const output_object_t output_object_cst;

// List of defined messages 
extern const messages_object_t messages_list_cst [ nb_Of_Messages ] ;

// list of active messages to send to server and to print on LCD
extern active_message_t active_message_list [ nb_OF_ACTIVE_MESSAGES] ;
extern const active_message_t active_message_init_cst ;

// active software configuration
extern sw_configuration_t software_configuration ;

// default software configuration
extern const sw_configuration_t software_configuration_default ;

// LCD driver handler
extern int  lcd_handler ;
/**********************/
/* Public Functions   */
/**********************/

extern int   ihome_initialize ( void ) ;
extern void *ihome_monitor    ( void *prm) ;
extern void *ihome_read       ( void *prm) ;
extern void *ihome_update     ( void *prm) ;
extern void *ihome_write      ( void *prm) ;

