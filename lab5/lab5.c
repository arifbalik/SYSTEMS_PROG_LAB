#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>
#include <pwd.h>


void  list_dir(char *base_path, const int root);

int main(int argc, char **argv)
{
 

    DIR *dp;
    struct dirent *dir;
    struct stat info;
    char pathname[BUFSIZ+1];
    struct passwd *ps;

    if(argc != 2){
        printf("Please give a path. \n Example: ./[name] [path]\n");
        exit(1);
    }

    if(stat(argv[1], &info) < 0) exit(1);
    
    if((info.st_mode & __S_IFMT) != __S_IFREG && (info.st_mode & __S_IFMT) != __S_IFDIR ){
        printf("%s is not a directory or file\n", argv[1]);
        exit(1);
    }

    switch((info.st_mode & __S_IFMT)){
        case __S_IFREG:
            ps = getpwuid(info.st_uid);
            printf("File name : %s, Size : %ld, Owner: %s\n", argv[1], info.st_size, ps->pw_name);
            exit(1);
        break;
        case __S_IFDIR:
             
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
    struct stat info;
    DIR *dir = opendir(base_path);
    char cur_path[BUFSIZ + 1];
    struct passwd *ps;

    if (!dir){
        return;
    }


    while ((dp = readdir(dir)) != NULL){
    
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            for (i=0; i<root; i++) {
                if (i % 2 == 0 || i == 0)
                    printf("|");
                else
                    printf(" ");

            }   
        sprintf(cur_path, "%s/%s",base_path, dp->d_name);
            if(stat(cur_path, &info) < 0) return;
        ps = getpwuid(info.st_uid);
            printf("|--%s, Size: %ld, Owner: %s\n", dp->d_name, info.st_size, ps->pw_name) ;

            strcpy(path, base_path);
            strcat(path, "/");
            strcat(path, dp->d_name);
            list_dir(path, root + 2);
        usleep(100000); // to make it look coooool!
        }
    }

    closedir(dir);
}