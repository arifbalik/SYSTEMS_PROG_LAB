#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define MSGNUMBER 10
#define SLOT_LEN 50
#define N_SLOTS 6
#define MAXMSGS 25

struct MEMORY{
	char buffer[N_SLOTS][SLOT_LEN];
	int head, tail;
};

struct sembuf acquire = {0, -1, SEM_UNDO},
			  release = {0, 1, SEM_UNDO};

enum {AVAIL_SLOTS, TO_CONSUME};


