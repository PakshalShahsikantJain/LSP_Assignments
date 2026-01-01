/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
        File Copy Using pread & pwrite
            Problem Statement:
                Copy a file using pread() and pwrite() without changing the file offset.
            Input:
                Source and destination file names.
            Output:
                Copied file identical to source.
      
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: makeCopyOfFile
//  Parameters: fd1 (File Descriptor of Source File), fd2 (File Descriptor of Destination File)
//  Description: Copies a File witout changing its offset
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int makeCopyOfFile(int fd1,int fd2)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    off_t offset = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj);  //system call to get statistics of file 

    if(iRet != 0)
    {
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = pread(fd1,fileData,fileSize,offset); //system call to read data from file without changing files offset

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);
        offset = lseek(fd1,0,SEEK_CUR); //system call to check current file offset position
        printf("Current Offset is: %ld\n",offset);   //0  : offset halat nahi
    
    }

    iRet = pwrite(fd2,fileData,fileSize,offset); //system call to copy data into file without changing files offset 

    if(iRet == -1)
    {
        return -1;  //on error
    }
    else 
    {
        return iRet; //on success
    }
}


//Entry Point Function
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int iRet = 0;
    off_t offset = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 3)
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;
    }

    srcFile = argv[1];
    destFile = argv[2];

    fd = open(srcFile,O_RDONLY); //system call to open file in read mode only

    if(fd == -1)
    {
        perror("Error Occured While Opening Source File in Read mode: ");
        return -1;
    }


    fd2 = open(destFile,O_WRONLY | O_APPEND); //system call to open file in write and append mode

    if(fd2 == -1)
    {
        if(errno == ENOENT) 
        {
            fd2 = creat(destFile,0777);  //system call to create file with specified permission

            if(fd2 == -1)
            {
                perror("Error Occcured while creating file:\n");
                return -1;
            }
            else 
            {
                printf("Destination File %s Get Successfully Created with fd %d Making Copy of File\n",destFile,fd2);
            }
        }
        else if(errno == EACCES)
        {
            iRet = fchmod(fd,0777); //system call to change file permission

            if(iRet == -1)
            {
                perror("Error Occured While Changing Mode:\n");
                return -1;
            }
        }
    }

    iRet = makeCopyOfFile(fd,fd2); //call to user defined function
    
    if(iRet == -1)
    {
        perror("Error Occured while Making Copy of File:\n");

        //system call to close files
        close(fd);
        close(fd2);
        return -1;
    }
    else 
    {
        printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
        offset = lseek(fd2,0,SEEK_CUR); //system call to check files's current offset position
        printf("Current Offset is: %ld\n",offset); 
    }

    //system call to close files
    close(fd);
    close(fd2);

    return 0;
}