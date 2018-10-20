#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signo);

int main() 
{ 
	struct sigaction act;

	/* 시그널이 오면 signalHandler를 실행하도록 설정 */
	act.sa_handler = signalHandler;
	/* 모든 시그널은 시그널을 처리하는 동안 블록되도록 설정 */
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
	/* SIGINT에 대해 act 행동을 하도록 설정 */
	sigaction(SIGINT, &act, NULL);
	printf("call sigaction\n");
	while(1)
		sleep(5);
}

void signalHandler(int signo)
{
	printf("start handler\n");
	sleep(3);
	printf("end handler\n");
}

