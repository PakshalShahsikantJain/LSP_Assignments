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
int moveRegularFiles(DIR *dp,char destDir[50]) 
{
    struct dirent *ptr = NULL;

    struct stat sobj;
    int iRet = 0;
    int iCnt = 0; 
    char fullDestPath[260];

    while(ptr = readdir(dp))             //system call to list out all files present in directory
    {   
        lstat(ptr->d_name,&sobj);        //System call to get status of file 
        
        if(S_ISREG(sobj.st_mode))
        {         
            snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", destDir, ptr->d_name);

            iRet = rename(ptr->d_name,fullDestPath);

            if(iRet != 0)
            {
                perror("Error");
                break;
            }
            else 
            {
                iCnt++;
            }
        }
    }
    
    closedir(dp);   //system call to close opened file

    if(iRet != 0)
    {
        return -1;
    }
    else 
    {
        return iCnt;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name:openDirectory
//  Paramters: fileName (char[])
//  Purpose: User Defined Function To Open Directory
//  Return Value: openDirectory
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void openDirectory(char srcDir[50],char destDir[50])
{
    DIR *dp = NULL;
    int iRet = 0;
    dp = opendir(srcDir);    //system call to open given directory

    if(dp != NULL)
    {   
        iRet = moveRegularFiles(dp,destDir);

        if(iRet == -1)
        {
            return;
        }
        else 
        {
            printf("Total Number of files Moved are: %d\n",iRet);
        }
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
    char brr[50];

    memset(arr,'\0',sizeof(arr));    // system call to set localbuffer with '\0
    memset(brr,'\0',sizeof(brr));

    printf("Jay Ganesh....\n");

    //Taking Directory Name as input from user 
    printf("Enter Source Directory Name You Want to Move File From \n");
    scanf("%s",arr);

    printf("Enter Destination Directory Name You Want To Move File Into\n");
    scanf("%s",brr);

    openDirectory(arr,brr); //Call To User Defined function
 
    return 0;
}