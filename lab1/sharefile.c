/*
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define DEBUG
#define WAIT 500000

int main(int argc, char** argv){

	FILE *fdrd, *fdwt;
	int pid;
	char parent = 'P', child = 'C', c;
	unsigned long i = WAIT;

	if(argc != 3) exit(1);


	#ifdef DEBUG
		printf("Parent: creating child process \n");
	#endif

	pid = fork();
	if(pid == 0){
		if((int)(fdrd = fopen(argv[1], "r")) == 0){
			perror("Oops!");
			exit(1);
		}
		if((int)(fdwt = fopen(argv[2], "w+")) == -1){
			perror("Oops!");
			exit(1);
		}
		#ifdef DEBUG
			printf("Child process starts, id: %d\n", getpid());
		#endif
		while(1){
			c = fgetc(fdrd);
			if(feof(fdrd)){
				printf("End of the text \n");
				break;
			} 
			while(--i);
			i = WAIT;
			fputc((int)child, fdwt);
			//fputc(1, &child, 1);
			fputc((int)c, fdwt);
		}
		#ifdef DEBUG
			printf("Exiting child process\n");
		#endif
		exit(0);
	}
	else{
		if((int)(fdrd = fopen(argv[1], "r")) == 0){
				perror("Oops!");
				exit(1);
		}
		if((int)(fdwt = fopen(argv[2], "w+")) == -1){
			perror("Oops!");
			exit(1);
		}
		#ifdef DEBUG
			printf("Parent starts, id: %d\n", getpid());
		#endif
		while(1){
			c = fgetc(fdrd);
			if(feof(fdrd)){
				printf("End of the text \n");
				break;
			} 
			while(--i);
			i = WAIT;
				
			//write(1, &parent, 1);
			fputc((int)parent, fdwt);
			fputc((int)c, fdwt);
			
		}
		#ifdef DEBUG
			printf("Exiting parent process\n");
		#endif
		wait(0);
		fclose(fdrd);
		fclose(fdwt);
	}
}