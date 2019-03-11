

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){

	int i =0;
	pid_t pid, parent, child, myparent;

	pid = fork();

	if(pid == 0){
		child = getpid();
		i = 2;
		printf("Child: my ID = %d, i = %d\n", child, i);
		myparent = getppid();
		printf("Child: my parent ID = %d\n", myparent);
		sleep(10);
		child = getpid();
		printf("\n Child after sleping: my ID = %d\n", child);
		myparent = getppid();
		printf("\n Child after sleping: my parent ID = %d\n", myparent);
		execl("simple", "simple", 0);
	}
	else{
		sleep(3);
		parent = getpid();
		printf("Parent: my ID = %d, i = %d\n", parent, i);
		printf("Parent terminating...\n");
	}
}