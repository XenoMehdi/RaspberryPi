#include "ihome_public.h"

void ihome_signal_term()
{
	log_print("SIGTERM : stop programm\n");
	pthread_cancel ( write_thread );
	pthread_cancel ( read_thread ) ;
	pthread_cancel ( monitor_thread ) ;
	pthread_cancel ( update_thread ) ;
	ihome_lcd_write ( messages_list_cst[
                              MESSAGE_9
                            ].lcd_message ) ;
	return;
}


void ihome_signal_hup()
{
	log_print("SIGHUP : ihome main program is hup\n");
	return;
}

void ihome_signal_int()
{
	log_print("SIGINT : ihome main program is init\n");
	printf("you have just pressed ctrl+c : bye \n");
	pthread_cancel ( write_thread );
	pthread_cancel ( read_thread ) ;
	pthread_cancel ( monitor_thread ) ;
	pthread_cancel ( update_thread ) ;
	ihome_lcd_write ( messages_list_cst[
                              MESSAGE_9
                            ].lcd_message ) ;
	
	return;
}