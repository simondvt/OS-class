#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

void str_to_upper(char *str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}


void bro1(int write_here)
{
    char str[100];

    while (1)
    {
        printf("[BRO1]: reading... ");

        fgets(str, 100, stdin);

        int n = strlen(str);
        str[n - 1] = '\0';
        n--;

        if (write(write_here, &n, sizeof(int)) == -1)
        {
            fprintf(stderr, "[BRO1]: Error on write 1: %s\n", strerror(errno));
            exit(1);
        }

        if (write(write_here, str, n) == -1)
        {
            fprintf(stderr, "[BRO1]: Error on write 2: %s\n", strerror(errno));
            exit(1);
        }

        if (strcmp(str, "end") == 0)
        {
            printf("[BRO1: exiting...]\n");
            break;
        }
    }
}

void bro2(int read_here)
{
    char str[100];

    while (1)
    {
        int n;

        if (read(read_here, &n, sizeof(int)) == -1)
        {
            fprintf(stderr, "[BRO2]: Error on read 1: %s\n", strerror(errno));
            exit(1);
        }

        if (read(read_here, str, n) == -1)
        {
            fprintf(stderr, "[BRO2]: Error on read 2: %s\n", strerror(errno));
            exit(1);
        }

        str[n] = '\0';

        if (strcmp(str, "end") == 0)
        {
            printf("[BRO2]: exiting...\n");
            break;
        }

        str_to_upper(str);

        printf("[BRO2]: writing... ");
        printf("%s\n", str);
    }
}


int main(void)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "[FATHER]: error on pipe: %s\n", strerror(errno));
        exit(1);
    }

    if (fork())
    {
        printf("[FATHER: born bro1]\n");

        if (fork())
        {
            printf("[FATHER: born bro2]\n");

            while(wait(NULL) > 0);

            if (close(fd[0]) == -1)
            {
                fprintf(stderr, "[FATHER]: error on close 0: %s\n", strerror(errno));
                exit(1);
            }

            if (close(fd[1]) == -1)
            {
                fprintf(stderr, "[FATHER]: error on close 1: %s\n", strerror(errno));
                exit(1);
            }

            printf("[FATHER]: exiting...\n");
        }
        else
            bro2(fd[0]);
    }
    else
        bro1(fd[1]);

    return 0;
}
