#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define MAX_SLEEP_TIME 2

static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;

void printSigSet(FILE *of, const char *prefix, const sigset_t *sigset)
{
	int sig, cnt;

	cnt = 0;

	for(sig = 1; sig < NSIG /*32*/; sig++)
	{
		if(sigismember(sigset, sig))
		{
			cnt++;

			fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
		}
	}

	if(cnt == 0)
		fprintf(of, "%s<empty signal set >\n", prefix);
}

void signal_handler(int sig)
{
	sigset_t pendingMask;

	if(sig == SIGINT)
		gotSigint = 1;
	else
	{
		sigCnt[sig]++;

		if(sigpending(&pendingMask) == -1)
			fprintf(stderr, "sigpending\n");

		printSigSet(stdout, "\t\t",  &pendingMask);			

		sleep(MAX_SLEEP_TIME);
	}
}

int main(int argc, char *argv[])
{
	int i;
	struct sigaction sigact;
	//sigset_t pendingMask;

	printf("%s: PID is %ld\n", argv[0], (long)getpid());

	sigact.sa_handler = signal_handler;
	sigfillset(&sigact.sa_mask);	
	//sigact.sa_flags = SA_RESETHAND | SA_RESTART;
	sigact.sa_flags = SA_RESTART;

	sigaction(SIGUSR2, &sigact, NULL);
	sigaction(SIGINT, &sigact, NULL);

	while(!gotSigint)
		continue;

	for(i = 1; i < NSIG; i++)
	{
		if(sigCnt[i] != 0)
			printf("%s: signal %d caught %d time%s \n", argv[0], i, sigCnt[i], (sigCnt[i] == 1) ? "" : "s");
	}

	exit(EXIT_SUCCESS);

	return 0;
}


