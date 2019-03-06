/* 
* 
*/




#include <stdio.h>
#include <fcntl.h>

main(argc , argv)
int argc; 
char** argv;

{
	int fdrd, fdwt;
	char c;
	char parent = 'P';
	char child = 'C';
	int pid;
	unsigned long i;

	if(argc != 3) exit(1);

	if((fdrd = open(argv[1], O_RDONLY)) == -1) exit(1);
	if((fdwt = creat(argv[2], 0666)) == -1) exit(1);
	printf("Parent: creating child process \n");

	pid = fork();
	if(pid == 0)
	{
		printf("Child process starts, id: %d\n", getpid());
		for(;;)
		{
			if(read(fdrd, &c, 1) != 1) break;
			for(i = 0; i < 50000; i++);
			write(1, &child, 1);
			write(fdwt, &c, 1);

		}
		exit(0);
	}
	else{
		printf("Parent starts, id: %d\n", getpid());
		for(;;)
		{
			if(read(fdrd, &c, 1) != 1) break;
			for(i = 0; i < 50000; i++);
				write(1, &parent, 1);
			write(fdwt, &c, 1);

		}

		wait(0);
	}
}