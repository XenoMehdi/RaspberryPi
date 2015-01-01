#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>
#include <time.h>

#define RS 3
#define EN 2

#define D4 0
#define D5 7
#define D6 9
#define D7 8
#define D_UNUSED 0

#define LED 12
#define LCD_A 14

void lcd_initialize ( const char *ip ) ;
