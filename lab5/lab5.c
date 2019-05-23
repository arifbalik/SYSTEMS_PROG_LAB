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

    
    

    /*//###########################___PART1___#############################//
    if(argc != 2)
    {
        perror("Arguments number is not valid.."); 
        exit(1);
    }
    //#########################___END_OF_THE_PART1___####################//

    //###########################___PART2___#############################//
    if(stat(*++argv, &info) < 0)exit(1);
    //#########################___END_OF_THE_PART2___####################//
    
    //###########################___PART3___#############################//
    if((typeOfFile(info.st_mode) != 'd') && (typeOfFile(info.st_mode) != '-'))
    {
        perror("Neither a file nor a directory..\n");
        exit(1);
    }
    //#########################___END_OF_THE_PART4___####################//
    
    //###########################___PART4___#############################//
    if(typeOfFile(info.st_mode) == '-')
    {
        printf("File name : %s, Size : %ld\n", *argv, info.st_size);
        exit(1);
    }    
    //#########################___END_OF_THE_PART4___####################//
    
    //###########################___PART5___#############################//
    if(typeOfFile(info.st_mode) == 'd')
    {
        printf("Directory name : %s, Size : %ld\n", *argv, info.st_size);
        if((dp = opendir(*argv)) == NULL)
        {
            perror("The directory cannot be opened..");
            exit(1);
        }
        
        while((dir = readdir(dp)) != NULL){
            if(dir->d_ino == 0)continue;
            sprintf(pathname, "%s/%s", *argv, dir->d_name);      
            if(stat(pathname, &info) != -1)
            {
                if(typeOfFile(info.st_mode) == '-')
                    printf("File name : %s, Size : %ld\n", dir->d_name, info.st_size);
            }else
            {
                perror("Regular file name cannot read..\n");
            }   
        }
    }*/

    //closedir(dp);
    //#########################___END_OF_THE_PART5___####################//

    //createRecDir(*++argv);
    printf("File Size / User Id / Grup Id / ST_Mode /  File Name\n");
    printf("----------------------------------------------------------------------------\n");
    listRecv(*++argv);
    printf("----------------------------------------------------------------------------\n");

    return 0;
}

void outputStatInfo(char *pathname, char *filename, struct stat *st)
    {
        int n;
        char slink[BUFSIZ+1];

        printf("%5ld %c", st->st_blocks, typeOfFile(st->st_mode));
        printf("%3ld ", st->st_nlink);
        printf("%5d/%-5d ", st->st_uid, st->st_gid);
    }

char typeOfFile(mode_t mode)
{
    switch (mode & __S_IFMT)
    {
        case __S_IFREG:
            return '-';
            break;
        case __S_IFDIR:
            return 'd';
        default:
            return '?';
            break;
    }
}

void listRecv(char *basePath)
{
    char path[BUFSIZ+1];
    struct dirent *dp;
    struct stat info;
    DIR *dir;

    if ((dir = opendir(basePath)) == NULL){
        return;
    }
    
    while ((dp = readdir(dir)) != NULL)
    {
        
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            sprintf(path, "%s/%s", basePath, dp->d_name);
            if (stat(path, &info) < 0)exit(1);
            
            printf("   %ld\t  |  %d   |  %d   |    %c    |  %s/%s\n", info.st_size, 
                                                               info.st_uid, 
                                                               info.st_gid, 
                                                               typeOfFile(info.st_mode), 
                                                               basePath, dp->d_name);
            listRecv(path);
        }
    }
    closedir(dir);
}




