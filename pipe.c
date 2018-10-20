 #include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <unistd.h>

int main(void)
{
	int pfd[2];  /* 파이프용 파일 지시자*/
	char buf[30];


    
    /*파이프 생성*/
	if(pipe(pfd) == -1){
			perror("pipe error");
			exit(1);
			
		}



	printf("Writing to the file descriptor #%d\n", pfd[1]);
	write(pfd[1], "pip", 5);

	printf("Reading from the file descriptor #%d\n", pfd[0]);
	read(pfd[0], buf, 5);


	printf("%s\n", buf);


	return 0;
	}
