/*
    Author : Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: Create a program ls_clone.c that takes one directory path and prints:
                •Entry name
                •Type ( le/dir/link/other)
                •Size (bytes)
                •Permissions in rwxr-xr-x format
                •Last modied time
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/*
    Function Name: convertPermission
    Paramters: mode 
    Description: Converts Permission mode into character based on mode and permission
    return value: void
*/
void convertPermission(mode_t mode) 
{
    // Print file type
    if (S_ISDIR(mode)) 
    {
        printf("d");
    }
    else if(S_ISLNK(mode))
    {
        printf("l");
    } 
    else 
    {
        printf("-");
    }
        
    
    // Print user permissions (rwx)
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    
    // Print group permissions (rwx)
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    
    // Print other permissions (rwx)
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

/*
    Function Name: ls
    Parameters: pointer pointing to directory file address(dp), directory Name 
    Description: Lists out All The Directory FIle entries with perrmissions and other meta-data
    Return value: Void (Nothing)
*/
void ls(DIR * dp,char dir[50])
{
    struct dirent * ptr = NULL;
    int iRet = 0;
    off_t fileSize = 0;
    struct stat sobj;
    char fullPath[260];

    memset(fullPath,'\0',sizeof(fullPath)); //system call to '\0' upto size of local buffer 

    while((ptr = readdir(dp)) != NULL)  // readdir() system call to read directory file 
    {
        if((strcmp(ptr->d_name,".") != 0)&&(strcmp(ptr->d_name,"..") != 0))
        {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, ptr->d_name); //library to build full path of files 

            iRet = lstat(fullPath,&sobj);  //system call to get statistical information of file
            if(iRet == -1)
            {
                break;
            }

            //Logic to display all meta-data of files
            printf("Entry Name: %s\n",ptr->d_name);
            printf("File Type: ");
            if(ptr->d_type == DT_DIR)
            {
                printf("directory\n");
            }
            else if(ptr->d_type == DT_LNK)
            {
                printf("link\n");
            }
            else if(ptr->d_type == DT_REG)
            {
                printf("regular file\n");
            }
            printf("Size: %ld\n",sobj.st_size);
            printf("Permissions: ");
            convertPermission(sobj.st_mode);
            printf("\n");
            printf("Last file modification:   %s", ctime(&sobj.st_mtime));

            

            printf("Full Path: %s\n",fullPath);

        }

        printf("------------------------------------------\n");
    }

    if(iRet == -1)
    {
        perror("Error Occured When Stat of file: ");   //system call to print system call errors
        return;
    }
}

//Entry Point Function
int main(int argc,char * argv[])
{
    DIR * dp = NULL;
    char * dirPath = NULL;

    printf("Jay Ganesh....\n");

    dirPath = argv[1];

    dp = opendir(dirPath);   //system call to open directory 

    if(dp == NULL)
    {
        perror("Error Occured While Opening Directory:");  //system call to print system call errors
        return -1;
    }

    ls(dp,dirPath);  //call to user defined function ls

    return 0;
}