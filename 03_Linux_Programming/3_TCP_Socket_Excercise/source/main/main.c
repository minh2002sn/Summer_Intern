#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define ERROR_CHECK(ret, msg)						    \
do{	                                                    \
	if((ret) == -1)								        \
	{											        \
		fprintf(stderr, "%s[%d] ", __FILE__, __LINE__);	\
		perror(msg);						            \
		exit(EXIT_FAILURE);						        \
	}											        \
} while(0)

int main()
{
    int ret;
    char buff[255] = {};
    int fd = open("./input/test.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    ERROR_CHECK(fd, "open()");

    // for(int i = 0; i < 10; i++)
    // {
    //     for(char j = 'A'; j <= 'X'; j++)
    //     {
    //         ret = write(fd, &j, 1);
    //         ERROR_CHECK(ret, "write()");
    //     }
    //     for(char j = 'a'; j <= 'x'; j++)
    //     {
    //         ret = write(fd, &j, 1);
    //         ERROR_CHECK(ret, "write()");
    //     }
    // }

    int i = 1;
    while((ret = read(fd, buff, 31)) > 0)
    {
        ret = read(fd, buff, 31);
        printf("%02d. [%d] %s\n", i++, ret, buff);
        // printf("%d\n", ret);
    }

    


    close(fd);

    return 0;
}