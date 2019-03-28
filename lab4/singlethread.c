#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "timing.h"

void func1(void);
void func2(void);


int r1 = 0, r2 = 0;
struct timeval time1, time2;
pthread_mutex_t lock; //we need this for func1 and func2 to work

int main(int argc, char **argv){
	char* text = (char *)malloc(20);
	#ifdef DRAW_TIMING_DIAGRAM
		system("clear");
	#else
		printf("Single threaded process starts here...\n");
	#endif

	gettimeofday(&time1, 0);
	
	for (int j = 1; j < 4; ++j){
		#ifdef DRAW_TIMING_DIAGRAM
			sprintf(text, "\t|main[%d]\t|\t\t|\n",r1);
			time_line(text);
		#else
			printf("Main function of the process works: %d\n", j);
		#endif
		
		sleep(3);
	}
	

	func1();
	func2();
	gettimeofday(&time2, 0);
	printf("Main: Total elapsed time = %ld seconds\n", time2.tv_sec - time1.tv_sec);
	printf("Main thread terminated...\n");

	free(text);
	return 0;
}