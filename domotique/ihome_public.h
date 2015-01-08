/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_public                                                  *
*                                                                              *
*  Description : API for iHome Software.                                       *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
********************************************************************************
#include <pthread.h>

/**********************/
/* Type Declaration   */
/**********************/
// Define the boolean type
typedef unsigned char boolean_t;
#define TRUE ( 1 == 1 )
#define FALSE ( 1 == 0 )
#define nb_OF_ACTIVE_MESSAGES 5

// define the structure of input object
typedef struct input_object_s{
  boolean_t       value ;
  boolean_t       validity ;
  pthread_mutex_t mutex ;
} input_object_t ;

typedef enum input_element_e{
  input_BUTTON_1,
  nb_Of_Input_Elements
} input_element_t ;

// define the structure of output object
typedef struct output_object_s{
  boolean_t       value ;
  boolean_t       validity ;
  pthread_mutex_t mutex ;
} output_object_t ;

typedef enum output_element_e{
  output_RLY_LAMP_1,
  output_RLY_LAMP_2,
  output_RLY_LAMP_3,
  output_RLY_LAMP_4,
  nb_Of_Output_Elements
} output_element_t ;

// define an lcd message structure
typedef struct lcd_message_s{
  char lcd_line_1 [16] ;
  char lcd_line_2 [16] ;
} lcd_message_t ;

// define a monitoring message structure
typedef struct monitor_message_s{
  char message [255] ;
} monitor_message_t ;

typedef enum messages_elements_e{
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
typedef struct messages_object_s{
  messages_elements_t   id_message ;
  lcd_message_t         lcd_message ;
  monitor_message_t     monitor_message ;
} messages_object_t ;

typedef struct active_message_s{
  messages_elements_t   id_message ;
  boolean_t             printed_to_lcd ;
  boolean_t             sent_to_server ;
} active_message_t ;
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
extern const active_message_t active_message_default_cst ;
/**********************/
/* Public Functions   */
/**********************/

extern void *ihome_initialize ( void ) ;
extern void *ihome_monitor    ( void ) ;
extern void *ihome_read       ( void ) ;
extern void *ihome_update     ( void ) ;
extern void *ihome_write      ( void ) ;

