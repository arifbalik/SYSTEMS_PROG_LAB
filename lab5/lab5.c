#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>


void    listRecv(char *basePath);
char    typeOfFile(mode_t);
void    outputStatInfo(char *, char *, struct stat *);

//DIR     *dp_glob;
//struct  dirent *dir_glob;
//char    pathname_glob[BUFSIZ+1];
//struct  stat info_glob;
//char    *argvv;
//int     argcc;

int main(argc, argv)
int argc;
char **argv;
{
    //argvv = *++argv;
    //argcc = argc;

    
    //printf("name: %s, number of arg: %d", argvv, argcc);


    DIR *dp;
    struct dirent *dir;
    struct stat info;
    char pathname[BUFSIZ+1];

    
    

    if(argc != 2)
    {
        perror("Arguments number is not valid.."); 
        exit(1);
    }

    if(stat(argv[1], &info) < 0)exit(1);

    if((typeOfFile(info.st_mode) != 'd') && (typeOfFile(info.st_mode) != '-'))
    {
        perror("Neither a file nor a directory..\n");
        exit(1);
    }

    switch(typeOfFile(info.st_mode)){
        case '-':
            printf("File name : %s, Size : %ld\n", argv[1], info.st_size);
            exit(1);
        break;
        case 'd':
             
             list_dir(argv[1], 0);
        break;
    }

    closedir(dp);

    return 0;
}

void list_dir(char *base_path, const int root)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(base_path);

    if (!dir){
        printf("Someting went wrong when reading %s\n", base_path );
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++) 
            {
                if (i % 2 == 0 || i == 0)
                    printf("|");
                else
                    printf(" ");

            }
            printf("%c-%s size: %d", 195, dp->d_name, info.st_size);

            strcpy(path, base_path);
            strcat(path, "/");
            strcat(path, dp->d_name);
            list_dir(path, root + 2);
        }
    }

    closedir(dir);
}