
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv){

	pid_t pid,w;
	int i, status;
	char value[3];

	for(i = 0; i < 3; ++i){
		if((pid = fork()) == 0){
			sprintf(value, "%d", i);
			execl("child", "child", value, 0);
		}
		else printf("Parent created child ID = %d\n", pid);
	}

	while((w = wait(&status)) && w != -1){
		if(w != -1) printf("Parent: child ID = %d returned status = %04X\n", w, status);
	}
}