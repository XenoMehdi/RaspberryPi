/*
* @Project    : Intelligent Home
* @Module Name    : ihome_read
* @Author   : E. El Fakir
* @Date     : 2015-01-07 09:02:18
* @Last Modified by : E. El Fakir
* @Last Modified time : 2015-02-04 09:02:19
*/

// avoid implicit declaration of nanosleep
#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <sys/time.h>
#include "ihome_public.h"

void ihome_read ( void *prm)
{
  log_print("Read RT Task succes\n");
  /* socket data */
  struct hostent *server;
  struct sockaddr_in serv_addr;
  int bytes, sent, received, total, l_indx;

  /* sent and received messages */
  char response[1000], *e1, *e2, *e3;

  rt_task_set_periodic(NULL, TM_NOW, 50000000); // 50ms
  while (1)
  {
    // update GPIO outputs
    for (l_indx = 0; l_indx < nb_Of_Input_Elements; l_indx++)
    {
      //pthread_mutex_lock( &inputs_Array_Of_Elements[l_indx].mutex ) ;
      pins_in[l_indx].value = (bcm2835_gpio_lev(pins_in[l_indx].pin) == HIGH) ? TRUE : FALSE ;
      //pthread_mutex_unlock( &inputs_Array_Of_Elements[l_indx].mutex ) ;
    }
    //log_print("read input from pins and fill inputs array\n");
#if 0

    /* create the socket */
    socket_read = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(host);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
//log_print("create socket for reading\n");
//l_socket_failed = FALSE ;
    /* connect the socket */
    if (connect(socket_read, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    { /* close the socket */
      close(socket_read);
      //l_socket_failed = TRUE ;

      log_print("read socket failed to connect.\n");
      continue ;
    }
    // update command inputs array from web server
    //if(l_socket_failed == FALSE )
    //{
    /* send the request */
    /*  total = strlen(http_get_request);
      sent = 0;
      do {*/
//      bytes = write(socket_read,http_get_request+sent,total-sent);
    send(socket_read, http_get_request, total, 0);
    //log_print("send message via socket_read\n");

    /* if (bytes < 0)
     {
    print_error(0,"write");
     }
     if (bytes == 0)
         break;
     sent+=bytes;
    } while (sent < total);
    */
    /* receive the response */
    memset(response, 0, sizeof(response));
    total = sizeof(response) - 1;
    received = 0;
//  do {
    recv(socket_read, response, total, 0);
    //log_print("receive message via socket_read\n");

    //bytes = read(socket_read,response+received,total-received);
    /*  if (bytes < 0)
      {
     close(socket_read);
    print_error(0,"read")
      }
      if (bytes == 0)
          break;
      received+=bytes;
    } while (received < total);
    */
    /* close the socket */
    close(socket_read);

    if (received >= total)
    {
      log_print("received data > total in read task \n");
      continue ;
    }

    /* process response */
    e1 = strstr(response, "\r\n\r\n");
    if (e1 != NULL)
    {
      //printf("%s\n\n**********************\n\n",response);
      // if the received message start with 0 then no command has been received in last minute
      if (e1[4] == '0')
      {
        //  nothing to do

      }

      // else, a web command has been detected, then it should be decoded
      else
      {

        e2 = strstr (e1, "w_cmd:");
        if (e2 != NULL)
        {

//  e1 = strstr (e2, "\r\n");
//  e2 = strstr (e1+2, "\r\n");
          //    int number_of_comma = 0;
//  printf("%s",e2);
          // start with the first char after "w_cmd:"
          for (l_indx = 0, e3 = e2 + 6 ; l_indx < nb_Of_Command_Elements && ( *e3 != ',') ;  e3++)
          {
            if ( *e3 != ':' )
            {
              if (*e3 != 'x')
                commands_Array_Of_Elements[l_indx++].value = (atoi(e3) == 1 ) ? TRUE : FALSE ;
              else
                l_indx++;
            }
          }


//  for(l_indx=0 ; l_indx<nb_Of_Command_Elements ; l_indx++)
//    printf("%d ",commands_Array_Of_Elements[l_indx].value);
// printf("%d\n",number_of_comma);
        }
      }
    }
#endif


    FILE *f = fopen("/root/inputs_states.json", "r"); // open file
    if (!f)
    {
      //  printf("unable to open inputs file\n");
    }
    else
    {
      fseek(f, 0, SEEK_END); // move char pointer to the end of file - 0
      long len = ftell(f); // get the number of char before the char pointer
      fseek(f, 0, SEEK_SET); // move char pointer to the start of file + 0

      char *data = (char*) malloc(len + 1); // allocate memory space for data
      fread(data, 1, len, f);
      fclose(f);

      char *value;
      cJSON *json, *inputs_array, *inputs_array_item, *inputs_array_item_value ;
      json = cJSON_Parse(data);
      free(data);

      if (!json) {
        log_print("Error json parsing read task: ["); log_print(cJSON_GetErrorPtr());
      }
      else
      {
        if ( nb_Of_Command_Elements != cJSON_GetArraySize(inputs_array) )
        {
          log_print("number of command input in config file is different to the one in inputs.json file");
          ihome_signal_term();
        }
        else
        {
          inputs_array = cJSON_GetObjectItem(json, "Inputs");
          for (l_indx = 0 ; (l_indx < nb_Of_Command_Elements) ;  l_indx++)
          {
            inputs_array_item = cJSON_GetArrayItem(inputs_array, l_indx);
            inputs_array_item_value = cJSON_GetObjectItem(inputs_array_item, "value");

            for (int l_indx_j = 0; l_indx_j < nb_Of_Command_Elements; l_indx_j++)
            {
              if (cJSON_GetObjectItem(inputs_array_item, "pin")->valueint == cmd_in[l_indx_j].pin)
                cmd_in[l_indx_j].value = (strcmp(inputs_array_item_value->valuestring, "ON") == 0 ) ? TRUE : FALSE ;
            }

          }
        }
      }
//    cJSON_Delete(inputs_array);
      cJSON_Delete(json);
    }

    //nanosleep((struct timespec[]) {{0, 50000000}}, NULL);
    rt_task_wait_period(NULL);
  }
}
