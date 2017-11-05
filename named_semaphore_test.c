#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_NAME "/sem_mytest1"

int main (int argc, char *argv[])
{
    sem_t *sem;
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("child pid:%d\n", getpid());

        sem = sem_open(SEM_NAME, O_CREAT|O_EXCL, 0644, 1);
        if (sem == NULL)
        {
            sem = sem_open(SEM_NAME,0);
            if (sem == NULL)
            {
                fprintf(stderr, "sem_open failure\n");
                sem_close(sem);
                exit(0);
            }
        }

        printf("[%d]sem_wait\n", getpid());
        if (0!=sem_wait(sem))
        {
            fprintf(stderr, "sem_wait error\n");
            exit(-1);
        }
        printf("[%d]do something....\n", getpid());
        if (0!=sem_post(sem))
        {
            fprintf(stderr, "sem_post error\n");
            exit(-1);
        }
        printf("[%d] sem_post done\n", getpid());
    }
    else if(pid<0)
    {
        fprintf(stderr, "fork error\n");

    }
    else
    {
        printf("parent pid:%d\n", getpid());

        sem = sem_open(SEM_NAME, O_CREAT|O_EXCL, 0644, 1);
        if (sem == NULL)
        {
            sem = sem_open(SEM_NAME,0);
            if (sem == NULL)
            {
                fprintf(stderr, "sem_open failure\n");
                sem_close(sem);
                exit(0);
            }
        }

        printf("[%d]sem_wait\n", getpid());
        if (0!=sem_wait(sem))
        {
            fprintf(stderr, "sem_wait error\n");
            exit(-1);
        }
        printf("[%d]do something....\n", getpid());
        sleep(5); 
        if (0!=sem_post(sem))
        {
            fprintf(stderr, "sem_post error\n");
            exit(-1);
        }
        printf("[%d] sem_post done\n", getpid());
         
    }
    sem_close(sem);
    sem_unlink(SEM_NAME);
}

