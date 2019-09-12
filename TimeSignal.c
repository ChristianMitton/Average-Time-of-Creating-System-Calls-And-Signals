#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

static int numExceptions = 100000;
static int exceptionsCount = 100000;

static float totalTimeOfAllSignals = 0;

struct timeval programStart;
struct timeval programEnd;

void handle_sigfpe(int signum){

	struct timeval signalStart;
	struct timeval signalEnd;

	gettimeofday(&signalStart, NULL);

	if(exceptionsCount == 0){
		gettimeofday(&programEnd, NULL);

		float programSeconds = (programEnd.tv_sec - programStart.tv_sec);
		float programMicroseconds = ((programSeconds * 1000000) + programEnd.tv_usec) - (programStart.tv_usec);

		float avgTimePerException = (totalTimeOfAllSignals / numExceptions);

		printf("Exceptions Occurred: %d\n",numExceptions);

		printf("Total Elapsed Time: %f ms\n", programMicroseconds);

		printf("Average Time Per Exception: %f ms\n", avgTimePerException);

		exit(0);
	}	

	gettimeofday(&signalEnd, NULL);

	float signalSeconds = (signalEnd.tv_sec - signalStart.tv_sec);
	float signalMicroseconds = ((signalSeconds * 1000000) + signalEnd.tv_usec) - (signalStart.tv_usec);	
	totalTimeOfAllSignals += signalMicroseconds;	

	exceptionsCount -= 1;
}

int main(int argc, char *argv[]){	

	gettimeofday(&programStart, NULL);

	int x = 5;
	int y = 0;
	int z = 0;
	
	signal(SIGFPE, handle_sigfpe);
	z = x / y;
	z++;
	return 0;

}
