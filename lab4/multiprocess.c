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
pthread_mutex_t lock;

int main(int argc, char **argv){
	pthread_t td1, td2;
	int pid, c_pid;
	int p;
	float delta;
	char* text = (char *)malloc(20);

	#ifdef DRAW_TIMING_DIAGRAM
		system("clear");
	#else
		printf("Single threaded process starts here...\n");
	#endif

	gettimeofday(&time1, 0);
	
	pid = fork();

	if(pid < 0){
		perror("Error during child1 creation");
		exit(1);
	}
	if(pid == 0){
		p = pthread_create(&td1, NULL, (void *)func1, NULL);
		
		if(p != 0){
			perror("Thread 1 creation problem");
			exit(1);
		}
		pthread_join(td1, NULL);
		exit(1);
	}

	pid = fork();

	if(pid < 0){
		perror("Error during child2 creation");
		exit(1);
	}
	if(pid == 0){
		p = pthread_create(&td2, NULL, (void *)func2, NULL);

		if(p != 0){
			perror("Thread 2 creation problem");
			exit(1);
		}
		pthread_join(td2, NULL);
		exit(1);
	}

	for (int j = 1; j < 4; ++j){
		pthread_mutex_lock(&lock);
			r1 = 100 + j;
		pthread_mutex_unlock(&lock);
		#ifdef DRAW_TIMING_DIAGRAM
			sprintf(text, "\t|main[%d]\t|\t\t|\n",r1);
			time_line(text);
		#else
			printf("Main function of the process works: %d\n", j);
		#endif
		sleep(3);
	}

	while ((c_pid = wait(0)) > 0);

	pthread_mutex_lock(&lock);
	gettimeofday(&time2, 0);
	delta = (time2.tv_sec - time1.tv_sec);
	pthread_mutex_unlock(&lock);
	printf("Main: Total elapsed time = %f seconds\n", delta);
	printf("Main thread terminated...\n");

	return 0;
}