#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static void sig_usr(int signo){
	if(signo == SIGUSR1)
		printf("SIGUSR1 received from its child\n");
	else if(signo == SIGUSR2)
		printf("SIGUSR2 received from its child\n");

}

int main(void){
	if(!fork())
	{
		int ppid;
		kill(ppid, SIGUSR1);

		exit(0);
	}

	else{
		if(signal(SIGUSR1, sig_usr) == SIG_ERR)
			perror("Cannot catch SIGUSR1\n");
		if(signal(SIGUSR2, sig_usr) == SIG_ERR)
			perror("cannot catch SIGUSR2\n");

		sleep(60);


	}





