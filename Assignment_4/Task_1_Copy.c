///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 01/01/2026
//  Program: File Copy Utility
//           Problem Statement:
//              Write a program that copies the contents of one le into another.
//              Input:
//                  Source le name and destination le name as command-line arguments.
//              Output:
//                  Destination File containing an exact copy of source le.
//                  •Handle File-not-found and permission errors.
//                  •Destination File should be created if not present.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
//  Description: Makes Exact Copy of Source File into Destination File
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int makeCopyOfFile(int fd1,int fd2)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj);   // system call to fetch Files Statistics

    if(iRet != 0)
    {
        perror("Error Occured While Getting Status of File:");
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));  

    iRet = read(fd1,fileData,fileSize);   //system call to read Data From File

    if(iRet == -1)
    {
        perror("Error while reading File:\n");
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);
    }

    iRet = write(fd2,fileData,fileSize);  //system call to write Data into File

    if(iRet == -1)
    {
        return -1;    //on Error Occured
    }
    else 
    {
        return iRet;  //on Success
    }
}

//Entry Point Function with Command Line Arguments
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int iRet = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 3)   
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;  //if command line arguments entered are less than expected number
    }

    srcFile = argv[1];
    destFile = argv[2];

    fd = open(srcFile,O_RDONLY);  //system call to open file in read mode 

    if(fd == -1)
    {
        perror("Error Occured While Opening Source File in Read mode: ");
        return -1;
    }


    fd2 = open(destFile,O_WRONLY | O_APPEND); //system call to open file in Write and Appedn Mode

    if(fd2 == -1)
    {
        if(errno == ENOENT)  //If File Not Found
        {
            fd2 = creat(destFile,0777); //system call to creat file

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
        else if(errno == EACCES)  //if file does not have necessary permissions to perform I/O Operations
        {
            iRet = fchmod(fd,0777);  //system call to change files permissions

            if(iRet == -1)
            {
                perror("Error Occured While Changing Mode:\n");
                return -1;
            }
        }
    }

    iRet = makeCopyOfFile(fd,fd2); // call to user definef function
    
    if(iRet == -1)
    {
        perror("Error Occured while Making Copy of File:\n");
        close(fd);  //system call to close the file
        close(fd2); //system call to cloee the file
        return -1;  //on error occured while making copy of file
    }
    else 
    {
        printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
    }

    //system calls to close the file
    close(fd);   
    close(fd2);

    return 0;
}