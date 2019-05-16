#include "common.h"


int main(int argc, char *argv[])
{
    static struct MEMORY sharmemory;
    static __u_short init_val[2] = {N_SLOTS, 0};
    int semid, shmid;
    int child;
    char *shmptr;
    int prod_id, cons_id, parent_id;
    //union semun arguments;
    
    union semun {
            int val;
            struct semid_ds *buf;
            unsigned short  *array;
} arguments;

    printf("Parent process starting...\n");
    if(argc != 2) {printf("Usage: %s num_of_messages\n", argv[0]); exit(1);}
    if(atoi(argv[1]) > MAXMSGS){printf("Too many messages...\n"); exit(1);}
    printf("%d messages will be produced and consumed\n", atoi(argv[1]));

    parent_id = getpid();
    sharmemory.head = sharmemory.tail = 0;

    shmid = shmget(parent_id, sizeof(sharmemory), IPC_CREAT|0666);
    if(semid < 0){perror("shmget problem"); exit(1);}
    shmptr = shmat(shmid, 0 , 0);
    if(shmptr == (char*) -1){perror("shmat problem"); exit(1);}

    memcpy(shmptr, (char*)&sharmemory, sizeof(sharmemory));
    printf("Shared memory is ready...\n");

    semid = semget(parent_id, 2, IPC_CREAT|0666);
    if(semid == -1){perror("semget problem"); exit(1);}
    arguments.array =init_val;
    if(semctl(semid, 0, SETALL, arguments) == -1){perror("semctl problem"); exit(1);}
    printf("Semaphores are ready...\n");

    prod_id = fork();
    if(cons_id == -1){perror("fork problem 1 in parent"); exit(-1);}
    if(prod_id == 0)execl("producer", "producer", argv[1], NULL);

    cons_id = fork();
    if(cons_id == -1){perror("fork problem 2 in parent"); exit(1);}
    if(cons_id == 0)execl("consumer", "consumer", argv[1], NULL);

    printf("Parent process is waiting...\n");
    wait(0);
    wait(0);

    shmdt(shmptr);
    shmctl(shmid, IPC_RMID, 0);
    semctl(semid, 0, IPC_RMID, 0);
    printf("\nAll process terminated...\n");
    exit(0);
    return 0;
}

