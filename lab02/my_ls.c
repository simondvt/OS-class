#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>

char *next_name(char *p_name, char *c_name)
{
    char *name = malloc(strlen(p_name) + strlen(c_name) + 2); // 2 more chars for '/' and '\0'
    strcpy(name, p_name);
    strcat(name, "/");
    strcat(name, c_name);

    return name;
}

void view_dir(char *dir_name)
{
    DIR *d = opendir(dir_name); 
    if (d == NULL) return;

    struct dirent *de;
    while ((de = readdir(d)) != NULL)
    {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
        {
            if (de->d_type == DT_DIR)
            {
                char *nn = next_name(dir_name, de->d_name);

                view_dir(nn);
                printf("\n");

                free(nn);
            }
            else
                printf("In %s:\t%s\n", dir_name, de->d_name); 
        }
    }

    closedir(d);
}

int main(int argc, char **argv) 
{ 
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }

    view_dir(argv[1]);

    return 0; 
} 
