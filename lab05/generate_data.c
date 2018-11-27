#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDWR);

    int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        int i = rand() % 10;
        int j = rand() % 10;

        int temp = num[i];
        num[i] = num[j];
        num[j] = temp;
    }

    for (int i = 0; i < 10; i++)
        write(fd, &num[i], sizeof(int));

    close(fd);
    return 0;
}
