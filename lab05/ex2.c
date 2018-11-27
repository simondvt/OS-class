#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define N 10 

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    if ((fd = open(argv[1], O_RDWR)) < 0)
    {
        fprintf(stderr, "Error opening %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    
    // shitty bubble with useless overhead
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (!fork())
            {
                int read_res;

                int vj, vj1;
                lseek(fd, j * sizeof(int), SEEK_SET);
                if ((read_res = read(fd, &vj, sizeof(int))) <= 0)
                {
                    fprintf(stderr, "Error on 1 read got %d: %s\n", read_res, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                
                lseek(fd, (j + 1) * sizeof(int), SEEK_SET);
                if ((read_res = read(fd, &vj1, sizeof(int))) <= 0)
                {
                    fprintf(stderr, "Error on 2 read got %d: %s\n", read_res, strerror(errno));
                    exit(EXIT_FAILURE);
                }

                if (vj > vj1)
                {
                    lseek(fd, j * sizeof(int), SEEK_SET);
                    write(fd, &vj1, sizeof(int));
                    lseek(fd, (j + 1) * sizeof(int), SEEK_SET);
                    write(fd, &vj, sizeof(int));
                }

                exit(0);
            }
            else
                wait(NULL);
        }
    }


    close(fd);    
}
