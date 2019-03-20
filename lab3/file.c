

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <unistd.h>

#define HELP "./file [file1] [file2] [file3]"

#define PARENT_READ_BLOCK 10
#define CHILD_READ_BLOCK 20

#define WAIT 100000

int main(int argc, char** argv)
{
	char *block;
	int i;
	short bytes, fd1, fd2, fd3;

	
	
	if(argc != 4){
		printf("Invalid argument count. Please use the following standart\n"HELP"\n" );
		exit(1);
	}

	if((fd1 = open(argv[1], O_RDONLY)) == -1){
		perror("Error while opening [file1]!");
		exit(1);
	}

	if(!fork()){
		if((fd3 = open(argv[3], O_CREAT|O_WRONLY|O_TRUNC, 0666)) == -1){
			perror("Error while creating [file3]");
			exit(1);
		}
		block = (char*)malloc((char)CHILD_READ_BLOCK);
		while(1){
			bytes = read(fd1, block, CHILD_READ_BLOCK);
			switch(bytes){
				case 0:
					printf("Child: File 1: EOF\n");
					close(fd3);
					goto exit;
				break;
				case CHILD_READ_BLOCK:
					i = WAIT;
					while(i--);
					if(write(fd3, block, CHILD_READ_BLOCK) != CHILD_READ_BLOCK){
						perror("Error during write into File 3");
						exit(1);
					}
				break;
				case -1:
					perror("Opps!");
					goto exit;
				break;
				default:
					if(bytes > 0){ 
						write(fd3, block, bytes);
						printf("Child: File1: EOF with %d bytes\n", bytes);
					}
					else{
						printf("Child: Error during read File 1. bytes: %d\n",bytes);
					}
					goto exit;
				break;
			}
		}

		goto exit;
	}
	if((fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0666)) == -1){
		perror("Error while creating [file2]");
		exit(1);
	}
	block = (char*)malloc((char)PARENT_READ_BLOCK);
	while(1){
		bytes = read(fd1, block, PARENT_READ_BLOCK);

		switch(bytes){
			case 0:
				printf("Parent: File 1: EOF\n");
				close(fd2);
				wait(0);
				close(fd1);
				goto exit;
			break;
			case PARENT_READ_BLOCK:
				i = WAIT;
				while(i--);
				if(write(fd2, block, PARENT_READ_BLOCK) != PARENT_READ_BLOCK){
					perror("Error during write into File 2");
					goto exit;
				}
			break;
			case -1:
				perror("Opps!");
			break;
			default:
				if(bytes > 0){
					write(fd2, block, bytes);
					printf("Parent: File1: EOF with %d bytes\n", bytes);
				}
				else{
					printf("Parent: Error during read File 1.bytes: %d\n",bytes);
				}
				goto exit;
			break;
		}
	}

	exit:
	free(block);
	exit(1);


}