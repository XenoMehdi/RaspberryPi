#include "ihome_lcd.h"
#include "ihome_public.h"

void ihome_signal_term()
{
	log_print("SIGTERM : stop programm\n");
	rt_task_delete ( &write_thread );
	rt_task_delete ( &read_thread ) ;
	rt_task_delete ( &monitor_thread ) ;
	rt_task_delete ( &update_thread ) ;
	rt_task_delete ( &write_messages_thread ) ;
	rt_task_delete ( &op_led_thread ) ;
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
	rt_task_delete ( &write_thread );
	rt_task_delete ( &read_thread ) ;
	rt_task_delete ( &monitor_thread ) ;
	rt_task_delete ( &update_thread ) ;
	rt_task_delete ( &write_messages_thread ) ;
	rt_task_delete ( &op_led_thread ) ;
	ihome_lcd_write ( messages_list_cst[
	                      MESSAGE_9
	                  ].lcd_message ) ;

	return;
}

void ihome_signal_segmentation_fault()
{
	log_print("SIGSEGV : segmentation fault");
	exit(-1);

}