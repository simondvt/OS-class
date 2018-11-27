#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void child_wakeup(int sig)
{
    printf("Child Woke-up\n");
}

void father_wakeup(int sig)
{
    printf("Father Woke-up\n");
}

int main(void)
{
    signal(SIGUSR1, child_wakeup);
    signal(SIGUSR2, father_wakeup);

    pid_t pid;

    if ((pid = fork()) == 0) // child
    {
        while(1) 
        {
            kill(getppid(), SIGUSR2);
            sleep(1);
        }
    }
    else // father
    {
        while(1)
        {
            kill(pid, SIGUSR1);
            sleep(1);
        }
    }

    return 0;
}
