///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 23/12/2025
//  Program: Delete All Empty Regular Files
//              •Accept directory name.
//              •Delete les with size = 0 bytes (regular les only).
//              •Print names deleted + total deleted count.
//              
//        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: deleteEmptyFile
//  Parameters: dp (DIR *)
//  Purpose: To Delete All Empty Files Present in Directory
//  Return Value: int 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int deleteEmptyFile(DIR *dp) 
{
    struct dirent *ptr = NULL;

    struct stat sobj;
    int iCnt = 0; 

    while(ptr = readdir(dp))             //system call to list out all files present in directory
    {   
        stat(ptr->d_name,&sobj);        //System call to get status of file 

        if(S_ISREG(sobj.st_mode))
        {
            if(sobj.st_size == 0)
            {
                unlink(ptr->d_name);
                printf("File Deleted is: %s",ptr->d_name);
                iCnt++;
            }
        }
    }
    
    closedir(dp);   //system call to close opened file

    return iCnt;
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

    dp = opendir(fileName);    //system call to open given directory

    if(dp != NULL)
    {   
        int iRet = deleteEmptyFile(dp);   //call to user defined function
        printf("Total Number of files deleted are: %d\n",iRet);
    }
    else 
    {
        perror("Error Occured While Opening Diretory");   //system call to print error
        return;
    }
}

//Entry Point Function
int main()
{
    char arr[50];
    
    memset(arr,'\0',sizeof(arr));    // system call to set localbuffer with '\0

    printf("Jay Ganesh....\n");

    //Taking Directory Name as input from user 
    printf("Enter Director Name You want To Open: \n");
    scanf("%s",arr);

    openDirectory(arr); //Call To User Defined function
 
    return 0;
}