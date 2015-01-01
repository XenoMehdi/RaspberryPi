#include <stdio.h>

#include "lcd_public.h"
#include "ip_public.h"

#define TRUE  ( 1 == 1 )
#define FALSE ( 1 == 0 )


char *ip_address;


int main(){

ip_address = malloc(16*sizeof(char));

get_ip_address(&ip_address);
lcd_initialize(ip_address);

return 0;
}
