/**
 *  initialize all software's datas.
 *
 *  @Module   ihome_initialize
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
#include "ihome_lcd.h"

int ihome_initialize ( void )
{

// local data
unsigned char l_return = 0;
unsigned int l_indx = 0 ;
bcm2835_init();

// initialize the GPIO for input and output modes
for(l_indx=0; l_indx<nb_Of_Input_Elements; l_indx++)
{
  bcm2835_gpio_fsel(pins_in[l_indx], BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(pins_in[l_indx], BCM2835_GPIO_PUD_DOWN);
}

for(l_indx=0; l_indx<nb_Of_Output_Elements; l_indx++)
{
  bcm2835_gpio_fsel(pins_out[l_indx], BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_set_pud(pins_out[l_indx], BCM2835_GPIO_PUD_DOWN);
}
// initialize the input array
for ( l_indx = 0 ; l_indx < nb_Of_Input_Elements ; l_indx++ )
{
  inputs_Array_Of_Elements [l_indx] = input_object_cst ;
}
for ( l_indx = 0 ; l_indx < nb_Of_Command_Elements ; l_indx++ )
{
  commands_Array_Of_Elements [l_indx] = input_object_cst ;
}
// initialize the output array
for ( l_indx = 0 ; l_indx < nb_Of_Output_Elements ; l_indx++ )
{
  outputs_Array_Of_Elements [l_indx] = output_object_cst ;
}

// initialize config array
config_Array_Of_Elements[0].type_of_output = NORMAL_RELAY ;
config_Array_Of_Elements[0].active_on_high = TRUE ;
config_Array_Of_Elements[0].time_before_activation = 0 ;
config_Array_Of_Elements[0].time_before_deactivation = 0 ;
config_Array_Of_Elements[0].repetition = 0 ;
config_Array_Of_Elements[0].interval_minutes = 0 ;
config_Array_Of_Elements[0].time_of_set = 0 ;
config_Array_Of_Elements[0].time_of_reset = 0 ;


// initialize the active messages array
for ( l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++ )
{
  active_message_list [l_indx] = active_message_init_cst ;
}

// set welcome and copyright messages to display
  for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list[l_indx].id_message = MESSAGE_1 ;
      l_indx = nb_OF_ACTIVE_MESSAGES ;
    }
  }
  for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list[l_indx].id_message = MESSAGE_2 ;
      l_indx = nb_OF_ACTIVE_MESSAGES ;
    }
  }


// initialize software configuration
software_configuration = software_configuration_default ;

// initialize lcd driver
lcd_handler = ihome_lcd_initialize(lcd_pins);



if(lcd_handler == -1 )
{
  for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list[l_indx].id_message = MESSAGE_3 ;
      l_indx = nb_OF_ACTIVE_MESSAGES ;
    }
  }
  l_return |= LCD_INIT_FAIL ;
}
else 
{
  for(l_indx = 0 ; l_indx < nb_OF_ACTIVE_MESSAGES ; l_indx++)
  {
    if ( active_message_list[l_indx].id_message == NO_ACTIVE_MESSAGE )
    {
      active_message_list[l_indx].id_message = MESSAGE_4 ;
      l_indx = nb_OF_ACTIVE_MESSAGES ;
    }
  }
}
#if 0
  /* create the socket */
  socket_monitor  = socket(AF_INET, SOCK_STREAM, 0);
  socket_read     = socket(AF_INET, SOCK_STREAM, 0);
  
  if (socket_monitor < 0 || socket_read < 0)
  l_return |= ERR_OPEN_SOCKET;

  /* lookup the ip address */
  server = gethostbyname(host);
  if (server == NULL)
  l_return |= ERR_OPEN_HOST;

  /* fill in the structure */
  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  memcpy(&serv_addr.sin_addr.s_addr,server->h_addr_list[0],server->h_length);

  /* connect the socket */
  if ( connect(socket_monitor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  l_return |= ERR_CONNECT_SOCKET;
  
  if (connect(socket_read, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  l_return |= ERR_CONNECT_SOCKET;
#endif
  return l_return ;
}
