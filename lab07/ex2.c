#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct
{
    char in[32], out[32];
} targ_t;

static int int_cmp(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

void *sort_file(void *arg)
{
    FILE *in, *out;
    int n;
    int *vet;
    targ_t *targ = (targ_t *) arg;

    if ((in = fopen(targ->in, "r")) == NULL)
    {
        perror("Couldn't open file'");
        exit(1);
    }

    if ((out = fopen(targ->out, "w")) == NULL)
    {
        perror("Couldn't open file'");
        exit(1);
    }

    fscanf(in, "%d", &n);
    vet = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++)
        fscanf(in, "%d", vet + i);
    fclose(in);

    // qsort_r for thread safety (?)
    qsort(vet, n, sizeof(int), int_cmp);

    for (int i = 0; i < n; i++)
        fprintf(out, "%d\n", vet[i]);
    fclose(out);

    free(vet);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage %s <n> <strA> <strB>\n", argv[0]);
        exit(2);
    }

    int n = atoi(argv[1]);
    pthread_t *threads = malloc(n * sizeof(pthread_t));
    targ_t *threads_data = malloc(n * sizeof(targ_t));

    char tmp[10];
    for (int i = 0; i < n; i++)
    {
        sprintf(tmp, "%d.txt", i);

        strcpy(threads_data[i].in, argv[2]);
        strcat(threads_data[i].in, tmp);
        strcpy(threads_data[i].out, argv[3]);
        strcat(threads_data[i].out, tmp);

        pthread_create(&threads[i], NULL, sort_file, &threads_data[i]);
    }

    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

    free(threads);
    free(threads_data);
    return 0;
}
