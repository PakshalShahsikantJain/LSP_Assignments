///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 25/12/2025
//  Program: Move All Files (Dir → Dir)
//              •Accept source dir and destination dir.
//              •Move all regular les:
//                  ◦Use rename() if same filesystem
//                  ◦Else copy + delete
//              •Print count of moved les
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
//  Function Name: moveRegularFiles
//  Parameters: dp,destDir (DIR *,char[])
//  Purpose: To Move All Regular Files into another Directory
//  Return Value: Count of File Moved (int)
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
        return -1;   //if unable to move file
    }
    else 
    {
        return iCnt;   //Count of Files Move into another Directory
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name:openDirectory
//  Paramters: fileName (char[])
//  Purpose: User Defined Function To Open Directory
//  Return Value: Nothing
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

    //Taking Source Directory Name as input from user 
    printf("Enter Source Directory Name You Want to Move File From \n");
    scanf("%s",arr);

    //Taking Destination Directory Name as input from user
    printf("Enter Destination Directory Name You Want To Move File Into\n");
    scanf("%s",brr);

    openDirectory(arr,brr); //Call To User Defined function
 
    return 0;
}