#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>


void handler(int sig)
{
}

void str_to_upper(char *str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

void bro1(pid_t bro2_p, int fd)
{
    while(1)
    {
        printf("[BRO1: reading...] ");
        char str[100];
        fgets(str, 100, stdin);

        lseek(fd, 0, SEEK_SET);
        if (write(fd, str, 100) == -1)
        {
            fprintf(stderr, "Error on write: %s\n", strerror(errno));
            exit(0);
        }

        kill(bro2_p, SIGUSR2);
        
        if (strcmp(str, "end\n") == 0)
            exit(0);
        
        pause();
    }
}

void bro2(pid_t bro1_p, int fd)
{
    while(1)
    {
        printf("[BRO2: paused]\n");
        pause();
        printf("[BRO2: awaked]\n");

        char str[100];

        lseek(fd, 0, SEEK_SET);
        if (read(fd, str, 100) == -1)
        {
            fprintf(stderr, "Error on read: %s\n", strerror(errno));
        }
        
        if (strcmp(str, "end\n") == 0)
            exit(0);

        str_to_upper(str);
        printf("%s", str);

        kill(bro1_p, SIGUSR1);
    }
}

int main(void)
{
    pid_t bro1_p, bro2_p;
    int fd;

    if ((fd = open(".tmp", O_CREAT | O_RDWR, S_IRWXU)) == -1)
    {
        fprintf(stderr, "Error on open: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    if ((bro1_p = fork()))
    {
        printf("[FATHER: born bro1]\n");

        if ((bro2_p = fork()))
        {
            printf("[FATHER: born bro2]\n\n");
            
            // wait childs
            while(wait(NULL) > 0);

            close(fd);
            if (remove(".tmp") == -1)
                fprintf(stderr, "Error on remove: %s\n", strerror(errno));

            printf("\n[FATHER: exiting now...]\n");
        }
        else
        {
            bro1(bro2_p, fd);
        }
    }
    else
    {
        bro2(bro1_p, fd);
    }

    return 0;
}
