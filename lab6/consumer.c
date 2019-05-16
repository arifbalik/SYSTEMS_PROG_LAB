#include "common.h"
#define MAXSLEEPTIME 5

int main(int argc, char *argv[])
{
    static char local[SLOT_LEN];
    static struct MEMORY *memptr;
    char *shmptr;

    int myparid = getppid();
    int semid, shmid;
    int i, j, sleeptime;
    int maxmsg;
    int curmsg;

    printf("CONSUMER started...\n");
    maxmsg = atoi(argv[1]);
    srand((unsigned)getpid());

    shmid = shmget(myparid, 0, 0);
    if(shmid < 0){perror("shmget problem in consumer"); exit(1);}
    shmptr = shmat(shmid, 0, 0);
    if(shmptr == (char*)-1){perror("shmat problem in consumer"); exit(1);}
    memptr = (struct MEMORY *) shmptr;

    semid = semget(myparid, 2, 0);
    if(semid == -1){perror("Consumer: semget problem"); exit(1);}

    for (curmsg = 0; curmsg < maxmsg; curmsg++)
    {
        memset(local, '\0', sizeof(local));
        sleeptime = rand() % MAXSLEEPTIME;
        sleep(sleeptime);

        acquire.sem_num = TO_CONSUME;
        j = semop(semid, &acquire, 1);
        if(j == -1){perror("semop problem 1 in consumer"); exit(1);}

        strcpy(local, memptr->buffer[memptr->head]);
        memptr->head = (memptr->head + 1) % N_SLOTS;

        release.sem_num = AVAIL_SLOTS;
        j = semop(semid, &release, 1);
        if(j == -1){perror("semop problem 2 in consumer"); exit(1);}
        printf(".................................Consumer received: %s\n", local);
    }
    
    printf("\n Consumer terminated...\n");
    exit(0);
}
