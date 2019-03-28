#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "timing.h"

void func2(void){
	int i;
	char* text = (char *)malloc(20);;
	for (int i = 1; i < 8; ++i){
		#ifdef DRAW_TIMING_DIAGRAM
			pthread_mutex_lock(&lock);
			sprintf(text, "\t|\t\t|\t\t|func2[%d]\n",r1);
			pthread_mutex_unlock(&lock);
			time_line(text);
		#else // Original
			printf("Function func2 prints and then sleeps 3 s: %d\n", i);
		#endif
		sleep(3);
	}
	free(text);
	return;
}