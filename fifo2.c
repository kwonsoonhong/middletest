#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



#define FIFO_NAME "FIFO_FD"




int main(void)
{
	char buf[100];
	int num, fd;



	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1)
	{
		perror("mknod error");
	}



	printf("Reader: waiting for a writer\n");
	fd = open(FIFO_NAME, O_RDONLY);


	printf("Reader:the writer ready.\n");




	do{
		if((num = read(fd, buf, 100)) == -1)
				perror("read error");

		else{
			buf[num] = '\0';
			printf("Reader: %d bytes read: %s", num,buf);
		}
	}	while (num >0);


		return 0;
	
}

				
