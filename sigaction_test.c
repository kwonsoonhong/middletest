#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() 
{ 
	struct sigaction act;

	/* 시그널에 대해 어떤 동작을 할 건지를 설정하는 문장으로 
	   시그널을 무시하도록 하는 SIG_IGN을 설정 */
	act.sa_handler = SIG_IGN;
	/* act.sa_mask는 시그널을 처리하는 동안 블록시킬 시그널을 모아 놓은
	   시그널 집합인데, 시그널 집합을 비웠으므로 모든 시그널은 블록되지 않음 */
	sigemptyset(&act.sa_mask);
	/* 옵션을 설정하지 않음 */
	act.sa_flags = 0;
	/* SIGINT에 대해 act 행동을 하도록 설정 */
	sigaction(SIGINT, &act, NULL);

	while(1) { 
		printf("Hello World\n"); 
		sleep(1); 
	} 
}

