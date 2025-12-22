///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 21/12/2025
//  Task: Display Complete File Information
//          • Accept File name and display le metadata using stat():
//              • Size, inode, permissions, hard links, owner uid/gid, le type, last access/modify time
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<time.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: DisplayFileStatistics
//  Parameters: fileName (char[])
//  Description: User Define function To Display Complete File Information
//  Return Value: Void
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DisplayFileStatistics(char fileName[50])
{
    int iRet = 0;
    struct stat sobj;

    iRet = stat(fileName,&sobj);      //system call to fetch complete file operation

    if(iRet == 0)
    {
        printf("File Size is: %ld\n",sobj.st_size);
        printf("inode number of File is: %ld\n",sobj.st_ino);
        
        if(S_ISBLK(sobj.st_mode))
        {
            printf("File Type / Mode: Block Device\n");
        }
        else if(S_ISCHR(sobj.st_mode))
        {
            printf("File Type / Mode: Character Device\n");
        }
        else if(S_ISDIR(sobj.st_mode))
        {
            printf("File Type / Mode: Directory File\n");
        }
        else if(S_ISREG(sobj.st_mode))
        {
            printf("File Type / Mode: Regular FIle\n");
        }
        else if(S_ISSOCK(sobj.st_mode))
        {
            printf("File Type / Mode: Socket File\n");
        }
        else if(S_ISFIFO(sobj.st_mode))
        {
            printf("File Type / Mode: Pipe File\n");
        }
        else if(S_ISLNK(sobj.st_mode))
        {
            printf("File Type / Mode: Symbolic Link\n");
        }
        
        printf("Number of Hard Links: %ld\n",sobj.st_nlink);
        printf("User ID of Owner: %d\n",sobj.st_uid);
        printf("Group ID of Owner: %d\n",sobj.st_gid);
        printf("Last status change: %s\n", ctime(&sobj.st_ctime));
        printf("Last file access: %s\n", ctime(&sobj.st_atime));

    }
    else 
    {
        perror("Error");              // system call to display error occured during execution of system call
    }

    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Entry Point Function
int main()
{
    char arr[50];

    memset(arr,'\0',sizeof(arr));

    printf("Jay Ganesh....\n");

    //Take File Name as input from user
    printf("Enter File Name You Want To Display Statistics of: \n");
    scanf("%s",arr);

    DisplayFileStatistics(arr);      //Call to user define function

    return 0;
}