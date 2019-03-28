
#define DRAW_TIMING_DIAGRAM
extern struct timeval time1, time2;
extern int r1;
extern pthread_mutex_t lock;

static void time_line(const char *text){

	pthread_mutex_lock(&lock);
	gettimeofday(&time2, 0);
	printf("|%ldsec", (time2.tv_sec - time1.tv_sec));
	printf("%s",text);
	pthread_mutex_unlock(&lock);
}

