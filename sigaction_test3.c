#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signo);
int signal_count=0;

int main() 
{ 
	struct sigaction new_act;
	struct sigaction old_act;

	new_act.sa_handler = signalHandler;
	/* new_act.sa_mask는 시그널을 처리하는 동안 블록시킬 시그널을 모아 놓은
	   시그널 집합인데, 시그널 집합을 비웠으므로 모든 시그널은 블록되지 않음 */
	sigemptyset(&new_act.sa_mask);
	new_act.sa_flags = 0;
	/* SIGINT에 대해 new_act로 설정하는데, 호출하기 전 행동 정보가 old_act에 저장 */
	sigaction(SIGINT, &new_act, &old_act);

	while(1) { 
		printf("waiting signal\n"); 
		sleep(1);
		if (signal_count == 3)
			/* SIGINT에 대해 old_act(예전 행동)로 설정 */
			sigaction(SIGINT, &old_act, NULL); 
	} 
}

void signalHandler(int signo)
{
	signal_count++;
	printf("Hi! signal %d\n", signal_count);
}

