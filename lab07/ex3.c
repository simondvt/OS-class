#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define N 5 // num of elements in each file

static int int_cmp(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

void *sort_file(void *arg)
{
    FILE *in; 
    int *vet;
    char *name = (char *) arg;

    if ((in = fopen(name, "r")) == NULL)
    {
        perror("Couldn't open file");
        exit(1);
    }

    vet = malloc(N * sizeof(int));
    
    for (int i = 0; i < N; i++)
        fscanf(in, "%d", vet + i);
    fclose(in);

    // qsort_r for thread safety (?)
    qsort(vet, N, sizeof(int), int_cmp);

    //free(vet);
    pthread_exit((void *) vet);
}

int *merge(int *vet, int *cur, int n)
{
    n *= N;
    int *res = malloc(sizeof(int) * (n + N));


    int i = 0, j = 0, k = 0;

    while (i < n && j < N)
    {
        if (vet[i] < cur[j])
            res[k++] = vet[i++];
        else
            res[k++] = cur[j++];
    }

    while (i < n)
        res[k++] = vet[i++];

    while (j < N)
        res[k++] = cur[j++];

    if (vet) 
    {
        free(vet);
    }
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage %s <n> <strA> <strB>\n", argv[0]);
        exit(2);
    }

    setbuf(stdout, NULL);

    int n = atoi(argv[1]);
    pthread_t *threads = malloc(n * sizeof(pthread_t));
    char **file_names = malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++)
    {
        file_names[i] = malloc(20 * sizeof(char));
        sprintf(file_names[i], "%s%d.txt", argv[2], i);

        pthread_create(&threads[i], NULL, sort_file, file_names[i]);
    }

    int *res = NULL;
    int *cur = NULL;

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], (void **) &cur);
        free(file_names[i]);
        res = merge(res, cur, i);
        free(cur);
    }

    FILE *out = fopen(argv[3], "w");
    for (int i = 0; i < n * N; i++)
        fprintf(out, "%d\n", res[i]);
    fclose(out);

    free(res);
    free(threads);
    free(file_names);
    
    return 0;
}
