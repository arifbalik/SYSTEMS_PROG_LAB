

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	
	printf("NEW PROGRAM %s IS STARTED BY TH CHILD PROCESS\n", argv[0]);
	printf("Child: my ID = %d\n", getpid());
	printf("Child: my parent ID = %d\n", getppid());
	printf("Child: terminating...\n");
	exit(0);

}