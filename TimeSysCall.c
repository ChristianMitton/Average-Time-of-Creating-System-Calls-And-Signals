#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	int callsToPerform = 100000;
	
	struct timeval programStart;
	struct timeval programEnd;

	struct timeval processStart;
	struct timeval processEnd;

	float totalTimeOfAllProcesses = 0;

	gettimeofday(&programStart, NULL);
	
	int i = 0;
	for(i = 0; i < callsToPerform; i++){
		gettimeofday(&processStart, NULL);
			
		getpid();

		gettimeofday(&processEnd, NULL);

		float processSeconds = (processEnd.tv_sec - processStart.tv_sec);
		float processMicroseconds = ((processSeconds * 1000000) + processEnd.tv_usec) - (processStart.tv_usec);	

		totalTimeOfAllProcesses += processMicroseconds;
	}

	gettimeofday(&programEnd, NULL);

	float avgTimePerProcesses = (totalTimeOfAllProcesses / callsToPerform);

	float programSeconds = (programEnd.tv_sec - programStart.tv_sec);
	float programMicroseconds = ((programSeconds * 1000000) + programEnd.tv_usec) - (programStart.tv_usec);

	printf("Syscalls Performed: %d\n",callsToPerform);

	printf("Total Elapsed Time: %f ms\n", programMicroseconds);

	printf("Average Time Per Syscall: %f ms\n", avgTimePerProcesses);

	return 0;
}
