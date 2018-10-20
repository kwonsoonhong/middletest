#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





int main(void)
{
	int pfd[2];


	if(pipe(pfd) == -1){
		perror("pipe error");
		exit(1);
	}

	if(!fork()) {
		close(1);
		dup(pfd[1]);
		close(pfd[0]);

		execlp("ls", "ls", NULL);
		}


	else{
		close(0);
		dup(pfd[0]);
		close(pfd[1]);



		execlp("wc", "wc", "-l", NULL);
	}


	return 0;
}
