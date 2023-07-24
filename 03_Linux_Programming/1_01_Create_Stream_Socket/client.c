#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERROR_CHECK(msg)						\
do{												\
	if((msg) == -1)								\
	{											\
		fprintf(stderr, "Line[%d] ", __LINE__);	\
		perror(__FILE__);						\
		exit(EXIT_FAILURE);						\
	}											\
} while(0)

#define LISTEN_BACKLOG                          50
#define BUFF_SIZE                               255

void chat_func(int socket_fd);

int main(int argc, char *argv[])
{
    int port_no = 0;
    struct sockaddr_in server_addr = {};
    int server_fd = 0;

    /* Read port number from command line */
    if(argc < 3)
    {
        printf("Not enough information are provided.\nCommand: ./server <server_address> <server_port_number>\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_no = atoi(argv[2]);
    }

    /* Init socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(server_fd);
    
    /* Init server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_no);
    inet_pton(AF_INET, argv[1], &(server_addr.sin_addr));

    /* Connect to server */
    ERROR_CHECK(connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)));

    /* Chat with client */
    chat_func(server_fd);

    return 0;
}

void chat_func(int socket_fd)
{
    char send_buff[BUFF_SIZE];
    char recv_buff[BUFF_SIZE];
    while(1)
    {
        memset(recv_buff, 0, BUFF_SIZE);
        memset(send_buff, 0, BUFF_SIZE);
        
        /* Response the message */
        printf("Please type the message: ");
        fgets(send_buff, BUFF_SIZE, stdin);
        ERROR_CHECK(write(socket_fd, send_buff, BUFF_SIZE));
        if(strncmp("exit", send_buff, 4) == 0)
        {
            break;
        }

        /* Read data from socket */
        /* Process block until there are data to read */
        ERROR_CHECK(read(socket_fd, recv_buff, BUFF_SIZE));
        printf("Message frome client: %s\n", recv_buff);
        if(strncmp("exit", recv_buff, 4) == 0)
        {
            break;
        }
    }
    /* Close server socket */
    close(socket_fd);
}
