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

/**********************/
/* Public Data        */
/**********************/
// Array of input elements.
extern input_object_t inputs_Array_Of_Elements [ nb_Of_Input_Elements ];
extern const input_object_t input_object_cst;

// Array of output elements.
extern output_object_t outputs_Array_Of_Elements [ nb_Of_Output_Elements ];
extern const output_object_t output_object_cst;

/**********************/
/* Public Functions   */
/**********************/

extern void *ihome_initialize ( void ) ;
extern void *ihome_monitor    ( void ) ;
extern void *ihome_read       ( void ) ;
extern void *ihome_update     ( void ) ;
extern void *ihome_write      ( void ) ;

