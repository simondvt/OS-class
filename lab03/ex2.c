#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage %s <n> <t>\n", argv[0]);
        exit(1);
    }


    for (int i = 0; i < atoi(argv[1]); i++)
    {
        if (fork() != 0) // 1st child
        {
            if (fork() != 0) // 2nd child
            {
                exit(0); // father dies
            }
        }
    }

    sleep(atoi(argv[2]));
    printf("%d returned from %d\n", getpid(), getppid());
    exit(0);
}
