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
#define WAIT 10000

int main(int argc, char** argv){

	int fdrd, fdwt;
	int pid;
	char parent = 'P', child = 'C', c;
	unsigned long i = WAIT;

	if(argc > 3){
		printf("Too much parameter! Please use the command as follows;\n .\\sharefile.c [input_file] [output_file] \n");
		exit(1);
	}else if(argc < 3){
		printf("Not enough parameter! Please use the command as follows;\n .\\sharefile.c [input_file] [output_file] \n");
		exit(1);
	}

	if((fdrd = open(argv[1], O_RDONLY)) == -1){
		perror("Oops!");
		exit(1);
	}
	if((fdwt = creat(argv[2], 0666)) == -1){
		perror("Oops!");
		exit(1);
	}

	#ifdef DEBUG
		printf("fdrd: %d, fdwt: %d\n",fdrd,fdwt );
		printf("Parent: creating child process \n");
	#endif

	pid = fork();
	if(pid == 0){
		
		#ifdef DEBUG
			printf("Child process starts, id: %d\n", getpid());
		#endif
		while(1){
			if(read(fdrd, &c, 1) != 1){
				printf("\nChild: end of the text \n");
				break;
			} 
			while(--i);
			i = WAIT;
			write(1,"\nChild read:",12);
			write(1, &c, 1);
			write(fdwt, &c, 1);
		}
		#ifdef DEBUG
			printf("Exiting child process\n");
		#endif
		exit(0);
	}
	else{

		#ifdef DEBUG
			printf("Parent process starts, id: %d\n", getpid());
		#endif

		while(1){

		if(read(fdrd, &c, 1) != 1){
			#ifdef DEBUG
				printf("\nParent: end of the text \n");
			#endif
			break;
		} 
		while(--i);
		i = WAIT;
		write(1,"\nParent read:",13);
		write(1, &c, 1);
		write(fdwt, &c, 1);
	}

	wait(0);
	#ifdef DEBUG
			printf("Exiting parent process\n");
	#endif
		
	}
}