///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 23/12/2025
//  Program: List All Files From Directory
//              •Accept directory name.
//              •Use opendir() / readdir() to print only names (skip . and ..).
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: readDirectoryFile
//  Parameters: dp (DIR *)
//  Purpose: To List All Files From Directory
//  Return Value: void 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readDirectoryFile(DIR *dp) 
{
    struct dirent *ptr = NULL;

    while(ptr = readdir(dp))    //system Call to List Data From File   
    {   
        if((strcmp(ptr->d_name,".") != 0)&&(strcmp(ptr->d_name,"..") != 0))
        {
            printf("File Name: %s\n",ptr->d_name);
        }
    }

    closedir(dp);   //system call to close file
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

    dp = opendir(fileName);      //system call to open given directory

    if(dp != NULL)
    {   
        readDirectoryFile(dp);   //call to user define function
    }
    else 
    {
        perror("Error Occured While Opening Diretory");  //system call to print error 
        return;
    }
}

//Entry Point Function
int main()
{
    char arr[50];

    memset(arr,'\0',sizeof(arr));    //system call to set local buffer with const value '\0'

    printf("Jay Ganesh....\n");

    printf("Enter Director Name You want To Open: \n");
    scanf("%s",arr);

    openDirectory(arr);  //Call to userdefined function

    return 0;
}