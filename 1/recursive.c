
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

/*describing the prototype*/
void searchFileDirRecursively(char *basePath, char *argname);

/*declaring flag to identify if the file or directory is present or not*/
int flag = 0;

int main(int argc, char *argv[]){

  if(argc != 2){
    fprintf(stderr, "Usage: %s <file-name>\n", argv[0]);
    exit(0);
  }

  searchFileDirRecursively(".", argv[1]);

  if(flag == 0){
    printf("%s is not present in the current directory hierarchy\n", argv[1]);
  }

  exit(0);
}

/*
  Recursive funcition called when directory is present. There is a possibility of same file
  being present in different directory
*/
void searchFileDirRecursively(char *basePath, char *argname){
  char path[1000];
  DIR *dp = opendir(basePath);
  struct dirent *dirp;

  if(!dp)
    return;

  while((dirp=readdir(dp)) != NULL){
    /* check if the file or directory is present in current or parent directory */
    if(strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0){
      /*check if the name matches any file or directory*/
      if(!strcmp(dirp->d_name, argname)){
        if(dirp->d_type == DT_DIR){
         printf("%s: this is a directory. Directory found at %s\n", dirp->d_name, basePath);
        }
        else{
          printf("%s: this is a file. File found at %s\n", dirp->d_name, basePath);
        }
        flag = 1;
      }
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dirp->d_name);
      searchFileDirRecursively(path, argname);
    }
  }
  closedir(dp);
}
