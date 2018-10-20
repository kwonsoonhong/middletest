#include <signal.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 

void sig_int(int signo);
void sig_usr(int signo);

int main()
{
	int i = 0;
	struct sigaction intsig, usrsig;

	usrsig.sa_handler = sig_usr;
	sigemptyset(&usrsig.sa_mask);
	usrsig.sa_flags = 0;

	intsig.sa_handler = sig_int;
	sigemptyset(&intsig.sa_mask);
	intsig.sa_flags = 0;

	// SIGINT에 대해서 sig_int를 등록한다. 
	if (sigaction(SIGINT, &intsig, 0) == -1)
	{
		printf ("signal(SIGINT) error");
		return -1;
	}    

	// SIGUSR2에 대해서 usrsig를 등록한다. 
	if (sigaction(SIGUSR2, &usrsig, 0) == -1)
	{
		printf ("signal(SIGUSR2) error");
		return -1;
	}    

	while(1)
	{
		printf("%d\n", i);
		i++;
		sleep(1);
	}
}

void sig_int(int signo)
{
	sigset_t sigset, oldset;

	// 핸들러가 수행되는 동안 수신되는 모든 시그널에 대해서
	// 블럭한다.  
	sigfillset(&sigset);
	if (sigprocmask(SIG_BLOCK, &sigset, &oldset) < 0)
	{
		printf("sigprocmask %d error \n", signo);
	}
	fprintf(stderr, "SIGINT !!!!\n");
	sleep(10);
}

void sig_usr(int signo)
{
	printf("sig_usr2\n");
}
