///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 23/12/2025
//  Program: List Files with Type
//              •Accept directory name.
//              •Print each entry with its type: Regular / Directory / Link / FIFO / Socket / Char / Block
//              •Use lstat() for accurate type.
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>
#include<sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: readDirectoryFile
//  Parameters: dp (DIR *)
//  Purpose: To List All Files From Directory with File Type
//  Return Value: void 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readDirectoryFile(DIR *dp) 
{
    struct dirent *ptr = NULL;
    struct stat sobj;

    while(ptr = readdir(dp))    //system call list out files present in directory
    {   
        printf("File Name: %s\n",ptr->d_name);
        lstat(ptr->d_name,&sobj);     //system call to fetch status of file
        

        if(S_ISBLK(sobj.st_mode))     //Macro to check if file is Type is Block Device or not  
        {
            printf("File Type: Block Device\n");
        }
        else if(S_ISCHR(sobj.st_mode))    //Macro to check if file is Type is Character Device or not 
        {
            printf("File Type: Character Device\n");
        }
        else if(S_ISDIR(sobj.st_mode))  //Macro to check if file is Type is Directory File or not 
        {
            printf("File Type: Directory File\n");
        }
        else if(S_ISREG(sobj.st_mode))  //Macro to check if file is Type is Regular File or not 
        {
            printf("File Type: Regular FIle\n");
        }
        else if(S_ISSOCK(sobj.st_mode))      //Macro to check if file is Type is Socket File or not 
        {
            printf("File Type: Socket File\n");
        }
        else if(S_ISFIFO(sobj.st_mode))    //Macro to check if file is Type is FIFO or Pipe FIle or not 
        {
            printf("File Type: Pipe File\n");
        }
        else if(S_ISLNK(sobj.st_mode))   //Macro to check if file is Type is Symbolic Link or not 
        {
            printf("File Type: Symbolic Link\n");
        }

        printf("-----------------------------------------------------------\n");
    }

    closedir(dp);               // system call to close opened directory
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name:openDirectory
//  Paramters: fileName (char[])
//  Purpose: User Defined Function To Open Directory
//  Return Value: openDirectory
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void openDirectory(char fileName[50])
{
    DIR *dp = NULL;

    dp = opendir(fileName);       // system call to open existing directory

    if(dp != NULL)
    {   
        readDirectoryFile(dp);    //call to user defined function
    }
    else 
    {
        perror("Error Occured While Opening Diretory");   //system cal to print error 
        return;
    }
}

//Entry Point Function
int main()
{
    char arr[50];

    memset(arr,'\0',sizeof(arr));

    printf("Jay Ganesh....\n");

    //Taking Directory Name as input from user
    printf("Enter Directory Name You want To Open: \n");
    scanf("%s",arr);

    openDirectory(arr);   //call to user defined function

    return 0;
}