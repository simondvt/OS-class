#include <stdio.h> 
#include <dirent.h>      // for opendir
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>   // for open, mkdir
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>      // for read, write
#include <errno.h>


void createDir(const char *path)
{
    if(mkdir(path, S_IRWXU))
    {
        fprintf(stderr,"Error: on creatDir(%s)\n", path);
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    printf("Created %s...\n", path);
}

void copy(const char *src, const char *dest)
{
    int s, d;

    if ((s = open(src, O_RDONLY)) == -1)
    {
        fprintf(stderr, "Error: %s can't be opened.\n", src);
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }

    if ((d = open(dest, O_WRONLY | O_CREAT, 0664)) == -1)
    {
        fprintf(stderr, "Error: %s can't be created.\n", dest);
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }

    char buf[512];
    int len;

    while ((len = read(s, buf, 512)) > 0)
    {
        if (write(d, buf, len) == -1)
        {
            fprintf(stderr, "Error: on write.\n");
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        }
    }

    close(s);
    close(d);

    printf("Copied %s to %s\n", src, dest);
}

char *next_name(char *p_name, char *c_name)
{
    char *name = malloc(strlen(p_name) + strlen(c_name) + 2); // 2 more chars for '/' and '\0'
    strcpy(name, p_name);
    strcat(name, "/");
    strcat(name, c_name);

    return name;
}

void view_dir(char *src_dir, char *dest_dir)
{
    DIR *d = opendir(src_dir); 
    if (d == NULL) return;


    printf("Entering %s:\n", src_dir);
    createDir(dest_dir);

    struct dirent *de;
    while ((de = readdir(d)) != NULL)
    {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
        {
            if (de->d_type == DT_DIR)
            {
                char *nn = next_name(src_dir, de->d_name);
                char *nd = next_name(dest_dir, de->d_name);

                printf("Recurring on %s:\n", de->d_name);
                view_dir(nn, nd);
                printf("\n");

                free(nn);
                free(nd);
            }
            else
            {
                char *nd = next_name(dest_dir, de->d_name);
                char *nn = next_name(src_dir, de->d_name);
                
                copy(nn, nd);
                
                free(nn);
                free(nd);
            }
        }
    }

    closedir(d);
}

int main(int argc, char **argv) 
{ 
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]);
        return 1;
    }

    view_dir(argv[1], argv[2]);

    printf("Copy done!\n");
    return 0; 
} 
