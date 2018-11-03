#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int i;
	for (i=0; i<2; i++) {
		if (fork ())
			fork ();
	}
	printf ("%d\n", i);

	return 0;
}
