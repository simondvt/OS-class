#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int i;

	for (i=1; i<=2; i++) {
		if (!fork ())
			printf ("%d\n", i);
	}
	printf ("%d\n", i); 

    return 0;
}
