
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){

	pid_t pid, w;
	int i, status;
	char value[3];
	for(i = 0; i < 3; ++i){
		if((pid = fork())){
			sprintf(value, "%d", i);
			execl("child", "child", value, 0);
		}else {
			printf("Parent created child process = %d\n", pid); 
		}
	}
	while(!(w = wait(&status))) printf("Parent: child ID = %d returned status = %04X\n", w, status);
}