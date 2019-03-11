

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mach-o/getsect.h>

#define SHW_ADR(ID, I) (printf("ID %s \t is at virtual address: %8X\n", ID, &I))

extern int etext, edata, end;

char *cptr = "This message is output by the function showit()\n";
char buffer1[25];

int showit();

int main(int argc, char** argv){

	int i = 0;

	printf("\n Address etext: %8X\n", get_etext());
	printf("Address edata: %8X\n", get_edata());
	printf("Address end: %8X\n", get_end());

	SHW_ADR("main", main);
	SHW_ADR("showit", showit);
	SHW_ADR("cptr", cptr);
	SHW_ADR("buffer1", buffer1);
	SHW_ADR("i", i);

	strcpy(buffer1, "A demonstration\n");
	write(1, buffer1, strlen(buffer1) + 1);
	showit(cptr);

}

int showit(char* p){
	char* buffer2;

	SHW_ADR("buffer2", buffer2);

	if((buffer2 = (char*)malloc((unsigned)strlen(p) + 1)) != NULL){
		printf("Allocated memory at %X\n", buffer2);
		strcpy(buffer2, p);
		printf("%s", buffer2);
		free(buffer2);
	}
	else{
		printf("Allocation error\n");
		exit(1);
	}

}