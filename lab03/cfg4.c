#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int i;
	for (i=2; i>=1; i--) {
		if (!fork ())
			printf ("%d\n", -i);
		else
			printf ("%d\n", i);
	}

	return 0;
}
