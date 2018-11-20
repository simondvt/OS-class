#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sys(FILE *fp)
{
    char str[1000];

    while (fgets(str, 1000, fp) != NULL)
    {
        system(str);

        printf("Press ENTER to execute next command...");
        getchar();
    }
}

char **parse_cmd(char *str)
{
    char **parsed;
    int count_words = 0;

    parsed = malloc(10 * sizeof(*parsed));
    for (int i = 0; i < 10; i++)
        parsed[i] = malloc(sizeof(*parsed[i]) * 20);

    int count_chars = 0;
    while (1)
    {
        if (*str == ' ')
        {
            parsed[count_words][count_chars] = '\0';
            count_words++;
            count_chars = 0;
        }
        else if (*str == '\0' || *str == '\n')
        {
            parsed[count_words][count_chars] = '\0';
            count_words++;
            break;
        }
        else
            parsed[count_words][count_chars++] = *str;

        str++;
    }

    parsed[count_words] = NULL;
    return parsed;
}

void my_system(char *path, char **parsed)
{
    if (!fork())
        execv(path, parsed);
}

void exec(FILE *fp)
{
    char str[1000];

    while (fgets(str, 1000, fp) != NULL)
    {
        char **parsed = parse_cmd(str);
        
        my_system(parsed[0], parsed);

        for (int i = 0; i < 10; i++)
            free(parsed[i]);
        free(parsed);

        printf("Press ENTER to execute next command...");
        getchar();
    }
}

    int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage %s 0/1 file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    if ((fp = fopen(argv[2], "r")) == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    if (atoi(argv[1]) == 0) // system
        sys(fp);
    else    // exec
        exec(fp);

    fclose(fp);
    return 0;
}
