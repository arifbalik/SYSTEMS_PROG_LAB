/*
 * Systems Programming Course
 * Lab #1
 * Concurrent File Acces by Parent and Child Processes
 * Arif Ahmet Balik - 180303019
 * Text Editor : Sublime Text 3
 * Last Update : 7 March 2019
 * All the files can be found at github.com/arifbalik/SYSTEM_PROG_LAB
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <unistd.h>

#define __FDRD 3
#define __FDWT 4

/* 
 * Uncomment to enable debug mode. 
 * When disabled it saves 3000 microseconds!!!
 */
#define DEBUG 
#define WAIT 50000

#define HELP "Please use the command as follows;\n" \
			 ".\\sharefile.c [input_file] [output_file]"

int main(int argc, char** argv){

	#ifdef DEBUG
		struct timeval  t1, t2;
		gettimeofday(&t1, NULL);
	#endif

	char pid, c, error;
	unsigned long i = WAIT;

	if(argc > 3){
		printf("Too much parameter!" HELP "\n");
		exit(1);
	}else if(argc < 3){
		printf("Not enough parameter!" HELP "\n");
		exit(1);
	}

	if(open(argv[1], O_RDONLY) == -1 || 
	   open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0666) == -1){
		perror("Oops!");
		exit(1);
	}

	#ifdef DEBUG
		printf("Parent: creating child process \n");
	#endif

	pid = fork();
	if(pid == 0){
		
		#ifdef DEBUG
			printf("Child process starts, id: %d\n", getpid());
		#endif
		while(1){
			error = read(__FDRD, &c, 1);
			if(error == -1){
				perror("Oops!");
				break;
			} else if(!error){
				#ifdef DEBUG
					printf("\nChild: End of the file!\n");
				#endif
				break;
			}
			while(--i);
			i = WAIT;
			#ifdef DEBUG
				write(1,"\nChild have read:",17);
				write(1, &c, 1);
			#endif
			if(write(__FDWT, &c, 1) == -1) perror("Oops!");
		}
		#ifdef DEBUG
			printf("\nExiting child process\n");
		#endif
		exit(0);
	}
	else{

		#ifdef DEBUG
			printf("Parent process starts, id: %d\n", getpid());
		#endif

		while(1){
		error = read(__FDRD, &c, 1);
		if(error == -1){
			perror("Oops!");
			break;
		} else if(!error){
			#ifdef DEBUG
				printf("\nParent: End of the file!\n");
			#endif
			break;
		}
		while(--i);
		i = WAIT;
		#ifdef DEBUG
			write(1,"\nParent have read:",18);
			write(1, &c, 1);
		#endif
		if(write(__FDWT, &c, 1) == -1) perror("Oops!");
	}

	wait(0);
	close(__FDRD);
	close(__FDWT);

	#ifdef DEBUG
		gettimeofday(&t2, NULL);
		printf ("Execution time = %f uSeconds\n", 
			(double) (t2.tv_usec - t1.tv_usec));
		printf("Exiting parent process\n");
	#endif
		
	}
}