

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

#define WAIT 10

int read_write(int fd_read, int fd_write, int size){
	char* block;
	int i;
	short bytes;

	block = (char*)malloc((char)size);

	bytes = read(fd_read, block, size);
	switch(bytes){
		case 0:
			printf("File 1: EOF\n");
			goto eof;
		break;
		case -1:
			perror("Error during read from File 1");
			goto error;
		break;
		default:
			if(bytes == size){
				i = WAIT;
				while(i--);
				if(write(fd_write, block, size) != size){
				perror("Error during write into File 3");
				goto error;
				}
				return 1; //ready for the next sequence
			}else if(bytes > 0){ 
				write(fd_write, block, bytes);
				printf("File1: EOF with %d bytes\n", bytes);
			}else{
				printf("Error during read File 1. bytes: %d\n",bytes);
				goto error;
			}
			goto eof;
		break;
	}

	error:
	free(block);
	exit(1);

	eof:
	free(block);
	return 0;
}

int main(int argc, char** argv)
{
	short fd1, fd2, fd3;
	if(argc != 4){
		printf("Invalid argument count. Help\n"HELP"\n" );
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

		while(read_write(fd1, fd3, CHILD_READ_BLOCK));
		
		close(fd3);
		exit(1);
	}

	if((fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0666)) == -1){
		perror("Error while creating [file2]");
		exit(1);
	}
	
	while(read_write(fd1, fd2, PARENT_READ_BLOCK));
	
	close(fd2);
	wait(0);
	close(fd3);
	
}