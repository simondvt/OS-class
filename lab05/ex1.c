#include <stdio.h>

int main(void)
{
    int n;

    while(scanf("%d", &n))
    {
        if (n == 0)
            return 0;

        if (n % 2)
            fprintf(stderr, "%d ", n);
        else
            printf("%d ", n);
    }

    return 0;
}
