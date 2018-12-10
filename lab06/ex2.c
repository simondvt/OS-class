#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) == -1)
    {
        fprintf(stderr, "Error on pipe1: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2) == -1)
    {
        fprintf(stderr, "Error on pipe2: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int par_read = pipe1[0];
    int par_write = pipe2[1];
    int cld_read = pipe2[0];
    int cld_write = pipe1[1];

    char w;

    setbuf(stdout, NULL);

    if (fork()) // par
    {
        close(cld_read);
        close(cld_write);

        while(1)
        {
            printf("I'm the father\n");

            if (write(par_write, &w, 1) == -1)
            {
                fprintf(stderr, "Error on par_write: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            if (read(par_read, &w, 1) == -1)
            {
                fprintf(stderr, "Error on par_read: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }

    }
    else    // cld
    {
        close(par_read);
        close(par_write);

        while(1)
        {
            if (read(cld_read, &w, 1) == -1)
            {
                fprintf(stderr, "Error on cld_read: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            printf("I'm the child\n");

            if (write(cld_write, &w, 1) == -1)
            {
                fprintf(stderr, "Error on cld_write: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
