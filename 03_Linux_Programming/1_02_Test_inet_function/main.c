#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
// #include <sys/socket.h>

#define BUFF_SIZE	255

int main()
{
	// char host_name[BUFF_SIZE];
	// struct hostent *host_entry;
	// char *ip_buff;

	// gethostname(host_name, BUFF_SIZE);
	// host_entry = gethostbyname(host_name);

	// ip_buff = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

	// printf("%s\n", host_name);
	// printf("%s\n", ip_buff);

	char hostbuffer[256];
    struct hostent *host_entry;
    int hostname;
    struct in_addr **addr_list;
 
    // retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1) {
        perror("gethostname error");
        exit(1);
    }
    printf("Hostname: %s\n", hostbuffer);
 
    // Retrieve IP addresses
    host_entry = gethostbyname(hostbuffer);
    if (host_entry == NULL) {
        perror("gethostbyname error");
        exit(1);
    }
    addr_list = (struct in_addr **)host_entry->h_addr_list;
    for (int i = 0; addr_list[i] != NULL; i++) {
        printf("IP address %d: %s\n", i+1, inet_ntoa(*addr_list[i]));
    }

	return 0;
}
