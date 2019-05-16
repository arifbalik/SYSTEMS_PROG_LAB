#include "common.h"

int main(int argc, char *argv[])
{
    static char *messages[MSGNUMBER] =
    {
        "Fist message", "Second message", "Third message", "Fourth message",
        "Fifth message", "Sixth message", "Seventh message", "Eighth message",
        "Ninth message", "Tenth message"
    };

    static char local[SLOT_LEN];
    static struct MEMORY *memptr;
    char *shmptr;

    int myparid = getppid();

    int semid, shmid;
    int i, j, sleeptime;
    int maxmsg;
    int curmsg;

    printf("PRODUCER started...\n");
    maxmsg = atoi(argv[1]);

    srand((unsigned) getpid());

    shmid = shmget(myparid, 0, 0);
    if(shmid < 0){perror("shmget problem in producer"); exit(1);}
    shmptr = shmat(shmid, 0, 0);
    if(shmptr == (char *)-1){perror("shmat problem in producer"); exit(1);}
    memptr = (struct MEMORY *) shmptr;


    semid = semget(myparid, 2, 0);
    if(semid == -1){perror("producer: semget problem"); exit(1);}

    for (curmsg = 0; curmsg < maxmsg; curmsg++)
    {
        memset(local, '\0', sizeof(local));
        sleeptime = rand() % 6;
        sleep(sleeptime);
        i = curmsg % MSGNUMBER;
        strcat(local, messages[i]);
        printf("Message prepared by producer: %s\n", local);

        acquire.sem_num = AVAIL_SLOTS;
        j = semop(semid, &acquire, 1);
        if(j == -1){perror("semop problem 1 in producer"); exit(1);}

        strcpy(memptr->buffer[memptr->tail], local);
        memptr->tail = (memptr->tail + 1) % N_SLOTS;

        release.sem_num = TO_CONSUME;
        j = semop(semid, &release, 1);
        if(j == -1){perror("semop problem 2 in producer"); exit(1);}
    }

    printf("\n Producer terminated...\n");
    exit(0);
    return 0;
}
