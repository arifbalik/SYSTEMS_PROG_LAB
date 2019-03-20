#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Set 1 to activate sleep, set 0 to activate wait mode
 *
 */
#define USE_SLEEP 0
#define SLEEP_INTV 10 //seconds

// 1: use execl, 0: use system
#define USE_EXECL 0

#define OPTIMIZE

int main(void)
{
	#ifdef OPTIMIZE
		system("echo Todays date is && date '+Date = %D Time = %H:%M'");
	#else
		pid_t pid;
		char *args[4];

		if((pid = fork()) < 0){
			perror("fork failed");
			exit(1);
		}

		if(pid == 0){
			#if (USE_EXECL)
				execl("/bin/echo","echo", "Today's","date", "is", 0);
				perror("exec failed in child");
			#else
				if(system("echo 'Today's date is"))
					perror("system failed in child");
			#endif
			exit(1);
		}

		#if (USE_SLEEP)
			sleep(SLEEP_INTV);
		#else
			wait(0);
		#endif

		args[0] = "date";
		args[1] = "+Date = %D Time = %H:%M";
		args[2] = NULL;

		execv("/bin/date", args);

		perror("exec failed in parent");
		exit(1);
	#endif

	
}