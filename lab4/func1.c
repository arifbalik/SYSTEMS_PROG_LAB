#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "timing.h"

void func1(void){
	int i;
	char* text = (char *)malloc(20);
	for (int i = 1; i < 10; ++i){
		#ifdef DRAW_TIMING_DIAGRAM
			pthread_mutex_lock(&lock);
			sprintf(text, "\t|\t\t|func1[%d]\t|\n",r1);
			pthread_mutex_unlock(&lock);
			
			time_line(text);
		#else // Original
			printf("Function func1 prints and then sleeps 4 s: %d\n", i);
		#endif
		sleep(4);
	}
	free(text);
	return;
}