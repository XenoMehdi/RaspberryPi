/*******************************************************************************
* Copyright FEZ EMBEDDED SYSTEMS INDUSTRY (c) 2015       All Rights Reserved   *
********************************************************************************/

/*******************************************************************************
* PROJECT : Intelligent Home (Raspberry Pi B+)                                 *
********************************************************************************
*                                                                              *
*  Module Name : ihome_update                                                  *
*                                                                              *
*  Description : update outputs array depending on inputs array.               *
*                                                                              *
*  Written by  : E. EL FAKIR                                 Date : 07/01/2015 *
*                                                                              *
********************************************************************************/
#include <time.h>
#include "ihome_public.h"

void *ihome_update ( void *prm)
{
while(1)
{
  printf("Update thread\n");
  sleep(2);
}
}
