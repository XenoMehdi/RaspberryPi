/**
 *	description : the main algorithm of iHome software.
 *
 *  @Module     ihome_update
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
#include <time.h>
#include "ihome_public.h"

void *ihome_update ( void *prm)
{

while(1)
{

context_object_t *l_ptr ;

for( l_ptr = &context_pile ; l_ptr != NULL ; l_ptr = l_ptr->next )
{
if ( l_ptr->config->type_of_output == NORMAL_RELAY )
{
l_ptr->output->value = (l_ptr->config->active_on_high == TRUE) ? 
l_ptr->input->value : !l_ptr->input->value ;
}
}

usleep(100000);
}
}
