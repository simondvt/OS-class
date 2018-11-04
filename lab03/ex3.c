#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

void P2457()
{
    printf("P2\n");
    pid_t child;

    if ((child = fork()))
    {
        printf("P4\n");
        waitpid(child, NULL, 0);
    }
    else
    {    
        printf("P5\n");
        exit(0);
    }

    printf("P7\n");
}

void P368()
{
    printf("P3\n");
    pid_t child;

    if (!(child = fork()))
    {
        printf("P6\n");
        exit(0);
    }
    else
        waitpid(child, NULL, 0);

    printf("P8\n");
}

int main(void)
{
    printf("P1\n");
    pid_t child;

    if ((child = fork()))
    {
        P2457();
        waitpid(child, NULL, 0);
    }
    else
    {
        P368();
        exit(0);
    }

    printf("P9\n");
    return 0;
}
