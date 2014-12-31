#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <wiringPi.h>
#include <lcd.h>




#define TRUE  ( 1 == 1 )
#define FALSE ( 1 == 0 )

#define RS 3
#define EN 2

#define D4 0
#define D5 7
#define D6 9
#define D7 8
#define D_UNUSED 0

#define LED 12
#define LCD_A 14

int  lcd_hundler;
char key;
int  ip_hundler;
struct ifreq ifr;
char *ip_address;

void get_ip_address(char **ip);

int main(){

ip_address = malloc(16*sizeof(char));

get_ip_address(&ip_address);

// Setup the wiringPi library
wiringPiSetup();
// Set LED and LCDÃ_Aas outputs
pinMode(LED, OUTPUT);
pinMode(LCD_A, OUTPUT);
// Trigger GPIO.10 ON
digitalWrite (LED, HIGH) ;
// Initialize Lcd
lcd_hundler = lcdInit( 2, 16, 4, RS, EN, D4, D5, D6, D7, D_UNUSED, D_UNUSED, D_UNUSED, D_UNUSED) ;
// display the result of lcd initialization
if(lcd_hundler == -1)
{
printf("Lcd init fail..\n");
digitalWrite (LCD_A, LOW) ;
}
else
{
// set cursor on the initial position
lcdHome (lcd_hundler) ;
// clear lcd
lcdClear (lcd_hundler) ;
// turn off cursor blinking
lcdCursorBlink (lcd_hundler, FALSE) ;
// turn display on (TRUE)
lcdDisplay (lcd_hundler, TRUE) ;

// write Hello on screen 
lcdPosition (lcd_hundler, 0, 0) ; lcdPuts (lcd_hundler, "  FEZ EMBEDDED  ") ;
lcdPosition (lcd_hundler, 0, 1) ; lcdPuts (lcd_hundler, "SYSTEMS INDUSTRY") ;

printf("Lcd init succes..\n");
digitalWrite (LCD_A, HIGH) ;
}

sleep(3);
// clear lcd
lcdClear (lcd_hundler) ;
lcdPosition (lcd_hundler, 0, 0) ; lcdPuts (lcd_hundler, "    F.E.S.I     ") ;
lcdPosition (lcd_hundler, 2, 1) ; lcdPuts (lcd_hundler, ip_address) ;

while(1)
{
scanf("%c", &key);

if (( key == 'n' ) || (key == 'N'))
{
digitalWrite (LCD_A, HIGH) ;
}

if (( key == 'f' ) || (key == 'F'))
{
digitalWrite (LCD_A, LOW) ;
}

}
return 0;
}




void get_ip_address(char **ip){

 ip_hundler = socket(AF_INET, SOCK_DGRAM, 0);

 /* I want to get an IPv4 IP address */
 ifr.ifr_addr.sa_family = AF_INET;
 /* I want IP address attached to "eth0" */
 strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
 ioctl(ip_hundler, SIOCGIFADDR, &ifr);
 close(ip_hundler);

 *ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

 printf("IP address on wlan0: %s\n", *ip);
}
