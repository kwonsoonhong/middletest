#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>




#define FIFO_NAME "FIFO_FD"


int main(void)
{
	char buf[100];
	int num, fd;


	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
		perror("mknod error");
	}




	printf("Writer: waiting for a reader.\n");
	fd = open(FIFO_NAME, o_WRONLY);

	printf("Writer: the reader ready\n");
	printf("Writer: your input:");


	while(fgets(buf, sizeof(buf), stdin), !feof(stdin)){
		if(num = write(fd, buf, strlen(buf)) == -1)
			perror("write error");
		else
			printf("Writer: wrote %d bytes\n", num);
	}


	return 0;
}
