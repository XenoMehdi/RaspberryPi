/**
 *	header file for lcd functions.
 *
 *  @Module   ihome_lcd
 *  @author 	El Mehdi El Fakir
 *  @email		elmehdi@elfakir.me
 *  @website	--
 *  @link		  --
 *  @version 	v1.0
 *  @compiler GCC
 *  @hardware Raspberry Pi B+
 *  @license	GNU GPL v3
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
 *	 - January 22, 2015
 *	 - first issue
 *	
 */
 #ifndef IHOME_LCD_H
 #define IHOME_LCD_H
 #include "ihome_public.h"

 extern int  ihome_lcd_initialize (const unsigned int *pins) ;
 extern void ihome_lcd_write (lcd_message_t lcd_message) ;
 
 #endif
