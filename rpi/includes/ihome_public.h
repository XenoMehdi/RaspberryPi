/**
 *  API for iHome Software.
 *
 *  @Module   ihome_public
 *  @author   El Mehdi El Fakir
 *  @email    elmehdi@elfakir.me
 *  @website  --
 *  @link     --
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
 *  Version 1.0
 *   - January 08, 2015
 *   - first issue
 *
 */
#ifndef IHOME_PUBLIC_H
#define IHOME_PUBLIC_H
#include <signal.h>

#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
#include <cJSON.h>


#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

// xenomai problem with c99
typedef char *caddr_t;
#include <native/task.h>

/**********************/
/* Data Definitions   */
/**********************/
RT_TASK write_thread ;
RT_TASK read_thread ;
RT_TASK monitor_thread ;
RT_TASK update_thread ;
RT_TASK write_messages_thread ;
RT_TASK op_led_thread ;

/*  Write RT Task */
#define WRITE_TASK_PRIO   70
#define WRITE_MODE    T_FPU|T_JOINABLE
#define WRITE_TASK_STKSZ  4096
#define WRITE_TASK_NAME   "Write rt Task"

/*  Write Messages RT Task */
#define WRITE_MESSAGES_TASK_PRIO   50
#define WRITE_MESSAGES_MODE    T_FPU|T_JOINABLE
#define WRITE_MESSAGES_TASK_STKSZ  4096
#define WRITE_MESSAGES_TASK_NAME   "Write Messages rt Task"

/*  Read RT Task  */
#define READ_TASK_PRIO    90
#define READ_MODE     T_FPU|T_JOINABLE
#define READ_TASK_STKSZ   4096
#define READ_TASK_NAME    "Read rt Task"

/*  Monitor RT Task */
#define MONITOR_TASK_PRIO 60
#define MONITOR_MODE    T_FPU|T_JOINABLE
#define MONITOR_TASK_STKSZ  4096
#define MONITOR_TASK_NAME "Monitor rt Task"

/*  Update RT Task  */
#define UPDATE_TASK_PRIO  80
#define UPDATE_MODE     T_FPU|T_JOINABLE
#define UPDATE_TASK_STKSZ 4096
#define UPDATE_TASK_NAME  "Update rt Task"

/*  Update RT Task  */
#define OP_LED_TASK_PRIO  50
#define OP_LED_MODE     T_FPU|T_JOINABLE
#define OP_LED_TASK_STKSZ 4096
#define OP_LED_TASK_NAME  "Operationa LED rt Task"

#define nb_Of_Threads 6
/**********************/
/* Type Declaration   */
/**********************/
// Define the boolean type
typedef unsigned char boolean_t;
#define TRUE ( 1 == 1 )
#define FALSE ( 1 == 0 )

#define HW 0
#define SW 1

#define MAX_SIZE_INPUT_PINS  50
#define MAX_SIZE_INPUT_CMD   50
#define MAX_SIZE_OUTPUT_PINS 50
#define MAX_SIZE_INOUT_NAMES (MAX_SIZE_OUTPUT_PINS + MAX_SIZE_INPUT_PINS + MAX_SIZE_INPUT_CMD)

#define print_error(x,s)  printf("ERROR writing message to socket {%s}\n",s); exit(x);
//#define log_print(x) {  printf("%s\n",x); }
#define log_print(x) {  /*time_t t = time(NULL);*/ \
/*      struct tm tm = *localtime(&t); */\
      log_file_desc = fopen("/root/log/log.txt", "a+"); \
      if(log_file_desc != NULL) {\
      /*fprintf(log_file_desc,"[%d/%d/%d %d:%d:%d] %s",tm.tm_mday, tm.tm_mon+1, tm.tm_year +1900, tm.tm_hour, tm.tm_min, tm.tm_sec, x); */\
      fprintf(log_file_desc,"%s", x); \
      fclose(log_file_desc);} \
      }

#define nb_OF_ACTIVE_MESSAGES 7
#define nb_Of_Config_Elements 1

#define ERR_CONNECT_SOCKET  0x01
#define ERR_OPEN_HOST       0x02
#define ERR_OPEN_SOCKET     0x04
#define LCD_INIT_FAIL       0x08

// define the structure of pin with it's value
typedef struct {
  unsigned int    pin ;
  unsigned int    value ;
} digital_pin_t ;

// define the structure of an object I/O
typedef struct {
  unsigned int     id ;
  digital_pin_t   *pin ; // if type is HW else  = NULL
  char   *name ;
  boolean_t        hw_sw ; //  either a physical = 0 I/O pin or input from gui = 1
} object_t ;


// define the structure of configuration object
typedef struct {
  char          type_of_output  ;
  boolean_t     active_on_high  ;
  unsigned int  time_before_activation ;
  unsigned int  time_before_deactivation ;
  unsigned char repetition       ;
  unsigned int  interval_minutes ;
  unsigned int  time_of_set ;
  unsigned int  time_of_reset  ;
} config_object_t ;

// define the structure of contexte object
typedef struct context_object_s {
  object_t *input ;
  object_t *output ;
  config_object_t *config ;
  struct context_object_s *prev ;
  struct context_object_s *next ;
} context_object_t ;

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
} active_message_t ;

typedef enum {
  OFF,
  ON
} pin_state_t ;

// define a structure for software configuration
typedef  union {
  unsigned int word ;
  struct {
    pin_state_t turn_LCD_Power      : 1 ;
    pin_state_t turn_LCD_Backlight  : 1 ;
  } options ;
} sw_configuration_t ;

// Define configuration structure
/**********************/
/* Public Data        */
/**********************/
// threads
// Arrays of I/O pins
extern unsigned int lcd_pins [] ;
extern digital_pin_t pins_in [MAX_SIZE_INPUT_PINS]  ;
extern digital_pin_t pins_out [MAX_SIZE_OUTPUT_PINS] ;
extern digital_pin_t cmd_in [MAX_SIZE_INPUT_CMD] ;
extern char inout_names [MAX_SIZE_INOUT_NAMES][50] ;

extern unsigned int nb_Of_Input_Elements ;
extern unsigned int nb_Of_Command_Elements ;
extern unsigned int nb_Of_Output_Elements ;

// lcd handler
extern int lcd_handler;

// variable to handle the sigterm signal, if = false the main while should stop and programm stops
extern boolean_t program_is_running ;

// Array of input elements.
extern object_t inputs_Array_Of_Elements [ MAX_SIZE_INPUT_PINS + MAX_SIZE_INPUT_CMD ];
extern const object_t input_object_cst;

// Array of output elements.
extern object_t outputs_Array_Of_Elements [ MAX_SIZE_OUTPUT_PINS ];
extern const object_t output_object_cst;

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

// initial context object
extern config_object_t config_Array_Of_Elements[nb_Of_Config_Elements];
extern context_object_t *context_pile;
extern context_object_t context_1, context_2, context_3, context_4, context_5 ;

/**********************/
/* Public Functions   */
/**********************/

extern int  ihome_initialize ( void ) ;
extern void ihome_monitor    ( void *prm) ;
extern void ihome_read       ( void *prm) ;
extern void ihome_update     ( void *prm) ;
extern void ihome_write      ( void *prm) ;
extern void ihome_write_messages     ( void *prm) ;
extern void ihome_op_led     ( void *prm) ;
extern void ihome_get_config_from_file( void );
extern void ihome_write_outputs_to_file(void);
extern void ihome_write_inputs_to_file(void);

/* Socket data */
extern int   port ;
extern char *host ;
extern char *http_post_request ;
extern char *http_get_request ;
extern char *private_key ;

extern int   socket_monitor ;
extern int   socket_read ;

/* Log file descriptor */
extern FILE *log_file_desc;

// functions to run when a signal is caught
extern void ihome_signal_term();
extern void ihome_signal_hup();
extern void ihome_signal_int();
extern void ihome_signal_segmentation_fault();

#endif
