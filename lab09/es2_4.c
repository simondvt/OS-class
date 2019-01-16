#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sa, sb, sc, sd, sh, se, sf, sg, si;

void *A(void *p)
{
    while (1)
    {
        sem_wait(&sa);

        printf("A ");

        sem_post(&sb);
        sem_post(&sc);
        sem_post(&sd);
    }
}

void *B(void *p)
{
    while (1)
    {
        sem_wait(&sb);

        printf("B ");

        sem_post(&si);
    }
}

void *C(void *p)
{
    while (1)
    {
        sem_wait(&sc);

        printf("C ");

        sem_post(&se);
        sem_post(&sf);
    }
}

void *D(void *p)
{
    while (1)
    {
        sem_wait(&sd);

        printf("D ");

        sem_post(&sh);
    }
}

void *E(void *p)
{
    while (1)
    {
        sem_wait(&se);

        printf("E ");

        sem_post(&sg);
    }
}

void *F(void *p)
{
    while (1)
    {
        sem_wait(&sf);

        printf("F ");

        sem_post(&sg);
    }
}

void *G(void *p)
{
    while (1)
    {
        sem_wait(&sg);
        sem_wait(&sg);

        printf("G ");

        sem_post(&si);
    }
}

void *I(void *p)
{
    while (1)
    {
        sem_wait(&si);
        sem_wait(&si);
        sem_wait(&si);

        printf("I\n");

        printf("\nPress ENTER...");
        getchar();

        sem_post(&sa);
    }
}

void *H(void *p)
{
    while (1)
    {
        sem_wait(&sh);

        printf("H ");

        sem_post(&si);
    }
}

int main(void)
{
    pthread_t ta, tb, tc, td, te, tf, tg, th, ti;

    sem_init(&sa, 0, 1);
    sem_init(&sb, 0, 0);
    sem_init(&sc, 0, 0);
    sem_init(&sd, 0, 0);
    sem_init(&se, 0, 0);
    sem_init(&sf, 0, 0);
    sem_init(&sh, 0, 0);
    sem_init(&sg, 0, 0);
    sem_init(&si, 0, 0);

    pthread_create(&ta, NULL, A, NULL);
    pthread_create(&tb, NULL, B, NULL);
    pthread_create(&tc, NULL, C, NULL);
    pthread_create(&td, NULL, D, NULL);
    pthread_create(&te, NULL, E, NULL);
    pthread_create(&tf, NULL, F, NULL);
    pthread_create(&tg, NULL, G, NULL);
    pthread_create(&th, NULL, H, NULL);
    pthread_create(&ti, NULL, I, NULL);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    pthread_join(tc, NULL);
    pthread_join(td, NULL);
    pthread_join(te, NULL);
    pthread_join(tf, NULL);
    pthread_join(tg, NULL);
    pthread_join(th, NULL);
    pthread_join(ti, NULL);

    return 0;
}
