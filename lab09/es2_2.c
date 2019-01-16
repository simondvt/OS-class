#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void semInit(int *S)
{
    if (pipe(S) == -1)
    {
        fprintf(stderr, "Error in pipe\n");
        exit(1);
    }
}

void semSignal(int *S)
{
    char c;

    if (write(S[1], &c, sizeof(c)) != 1)
    {
        fprintf(stderr, "error in write\n");
        exit(1);
    }
}

void semWait(int *S)
{
    char c;

    if (read(S[0], &c, sizeof(c)) != 1)
    {
        fprintf(stderr, "error in read\n");
        exit(1);
    }
}

int main(void)
{
    int S1[2], S2[2];

    semInit(S1);
    semInit(S2);

    while (1)
    {
        semSignal(S1);
        semSignal(S1);
        semSignal(S1);

        printf("Press ENTER...\n");
        getchar();

        printf("A\n");

        if (!fork())
        {
            if (!fork())
            {
                // D - H
                semWait(S1);

                printf("D\n");

                printf("H\n");

                semSignal(S2);
                exit(0);
            }
            else
            {
                // C - ...
                semWait(S1);
                
                int S3[2], S4[2];

                semInit(S3);
                semInit(S4);

                printf("C\n");

                semSignal(S3);
                semSignal(S3);

                if (!fork())
                {
                    semWait(S3);

                    printf("E\n");

                    semSignal(S4);

                    exit(0);
                }
                else
                {
                    semWait(S3);

                    printf("F\n");

                    semSignal(S4);
                }


                semWait(S4);
                semWait(S4);

                printf("G\n");

                semSignal(S2);
                exit(0);
            }
        }
        else
        {
            // B
            semWait(S1);

            printf("B\n");

            semSignal(S2);
        }


        semWait(S2);
        semWait(S2);
        semWait(S2);

        // I
        printf("I\n");

    }

    return 0;
}
