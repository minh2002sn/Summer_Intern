#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LOG_SOCK_INFO(name, addr)                       \
printf(name " address: %s\n" name " port: %d\n", inet_ntoa(addr.sin_addr), addr.sin_port)

#define ERROR_CHECK(ret, msg)						    \
do{	                                                    \
	if((ret) == -1)								        \
	{											        \
		fprintf(stderr, "%s[%d] ", __FILE__, __LINE__);	\
		perror(msg);						            \
		exit(EXIT_FAILURE);						        \
	}											        \
} while(0)

#define LISTEN_BACKLOG                          50
#define BUFF_SIZE                               255

void chat_func(int new_socket_fd);

int main(int argc, char *argv[])
{
    int ret = 0;
    int port_no = 0;
    int server_fd = 0;
    struct sockaddr_in server_addr = {};
    int client_fd = 0;
    struct sockaddr_in client_addr = {};
    int client_addr_len = 0;
    int opt_val = 1;

    /* Read port number from command line */
    if(argc < 2)
    {
        printf("No port number is provided.\nCommand: ./server <port_number>\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_no = atoi(argv[1]);
    }

    /* Init socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(server_fd, "socket()");
    
    /* Init server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port =  htons(port_no);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    LOG_SOCK_INFO("Server", server_addr);
	// printf("Server address: %s\nServer port: %d\n", inet_ntoa(server_addr.sin_addr), port_no);

    /* Prevent "Address already in use" error */
    // ERROR_CHECK(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt_val, sizeof(opt_val)));
    // ERROR_CHECK(setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt_val, sizeof(opt_val)));
    ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));
    ERROR_CHECK(ret, "setsockopt()");

    /* Bind socket with server address */
    ret = bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, "bind()");

    /* Listen to client */
    ret = listen(server_fd, LISTEN_BACKLOG);
    ERROR_CHECK(ret, "listen()");

    /* Accept connection with client */
    client_addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    ERROR_CHECK(client_fd, "accept()");
    LOG_SOCK_INFO("Client", client_addr);
    // printf("Client address: %s\nClient port: %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

    /* Chat with client */
    chat_func(client_fd);

    /* Close server socket */
    close(server_fd);

    return 0;
}

void chat_func(int new_socket_fd)
{
    int ret = 0;
    char send_buff[BUFF_SIZE];
    char recv_buff[BUFF_SIZE];
    while(1)
    {
        memset(send_buff, 0, BUFF_SIZE);
        memset(recv_buff, 0, BUFF_SIZE);

        /* Read data from socket */
        /* Process block until there are data to read */
        ret = read(new_socket_fd, recv_buff, BUFF_SIZE);
        ERROR_CHECK(ret, "read()");
        // printf("Message frome client: %s\n", recv_buff);
        printf("Number of byte: %d\n", ret);
        for(int i = 0; i < ret; i++)
        {
            printf("%d ", recv_buff[i]);
        }
        printf("\n");

        if(strncmp("exit", recv_buff, 4) == 0)
        {
            break;
        }

        /* Response the message */
        printf("Please response the message: ");
        fgets(send_buff, BUFF_SIZE, stdin);
        ret = write(new_socket_fd, send_buff, BUFF_SIZE);
        ERROR_CHECK(ret, "write()");
        if(strncmp("exit", send_buff, 4) == 0)
        {
            break;
        }
    }
    /* Close client socket */
    close(new_socket_fd);
}
