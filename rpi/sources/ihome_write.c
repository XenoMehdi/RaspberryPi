/**
 *  description : write data output to gpio.
 *
 *  @Module     ihome_write
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
 *   - January 16, 2015
 *   - first issue
 *
 */
// avoid implicit declaration of nanosleep
#define _POSIX_C_SOURCE 199309L

#include <sys/time.h>
#include "ihome_public.h"
//#include "ihome_lcd.h"


void ihome_write ( void *prm)
{
  log_print("Write RT Task succes\n");
  unsigned int l_indx ;

  rt_task_set_periodic(NULL, TM_NOW, 50000000); // 50ms

  while (1) {

    // update GPIO outputs
    for (l_indx = 0; l_indx < nb_Of_Output_Elements; l_indx++)
    {
      bcm2835_gpio_write(pins_out[l_indx].pin, ((pins_out[l_indx].value == TRUE ) ? HIGH : LOW ));
    }

    // write outputs into json file
    ihome_write_outputs_to_file();

    rt_task_wait_period(NULL);

  }
}
