#include "ip.h"

int  ip_hundler;
struct ifreq ifr;

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
