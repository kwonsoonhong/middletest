#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>




static void sig_usr(int signo){
	if(signo == SIGUSR1)
		printf("received SIGUSR1\n");

	else if(signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else if(signo == SIGTERM)
		printf("received SIGTERM die hard!!!!!;)\n");
}
int main(void){
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		perror("cat't catch SIGUSR1");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		perror("can't catch SIGUSR2");
	if(signal(SIGTERM, sig_usr) == SIG_ERR)
		perror("cannot catch SIGTERM\n");
	for(; ;)
		sleep(60);


}

