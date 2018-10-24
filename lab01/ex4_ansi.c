#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *in, *out;

    if (argc != 3)
    {
        printf("Usage: %s <src> <dest>\n", argv[0]);
        return 2;
    }

    if ((in = fopen(argv[1], "r")) == NULL)
    {
        printf("error: %s could not be opened\n", argv[1]);
        return 1;
    }

    if ((out = fopen(argv[2], "w")) == NULL)
    {
        printf("error: %s could not be written\n", argv[2]);
        return 1;
    }

    int ch;
    while ((ch = fgetc(in)) != EOF)
       fputc(ch, out); 

    fclose(in);
    fclose(out);

    printf("Copy done\n");
    return 0;
}
