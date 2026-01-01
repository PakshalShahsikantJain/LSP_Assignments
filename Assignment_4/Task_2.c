/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
        File Copy with Offset
            Problem Statement:
                Copy a File starting from a given byte offset of the source le.
            Input:
                source_file destination_file offset
            Output:
                Partial file copied starting from offset.
      
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
//  Parameters: fd1 (File Descriptor of Source File), fd2 (File Descriptor of Destination File), offset 
//  Description: Copy a File starting from a given byte offset of the source file.
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int makeCopyOfFile(int fd1,int fd2,off_t offset)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj);  //system call to fetch statistics of file 

    if(iRet != 0)
    {
        perror("Error Occured While Getting Status of File:");
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = lseek(fd1,offset,SEEK_CUR);  //system call to change offset of a file to specified offset

    if(offset > fileSize)
    {
        fileSize = fileSize + offset;
    }
    
    fileSize = fileSize - offset;

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("Current Offset Location is: %d\n",iRet);
    }

    iRet = read(fd1,fileData,fileSize);   //system call to read data from file from changed offset

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);
    }

    iRet = write(fd2,fileData,fileSize);  //system call to write copied data into destination file

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        return iRet;
    }
}

//Entry Point Function
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int offset = 0;
    int iRet = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 4)
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;
    }

    srcFile = argv[1];
    destFile = argv[2];
    offset = atoi(argv[3]);

    fd = open(srcFile,O_RDONLY); //system call to open file in read only mode

    if(fd == -1)
    {
        perror("Error Occured While Opening Source File in Read mode: ");
        return -1;
    }


    fd2 = open(destFile,O_WRONLY | O_APPEND);  //system call to open file in write and append mode 

    if(fd2 == -1)
    {
        if(errno == ENOENT)
        {
            fd2 = creat(destFile,0777);   //system call to creat file with all permissions

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
            iRet = fchmod(fd,0777);  // system call to change permissions of file

            if(iRet == -1)
            {
                perror("Error Occured While Changing Mode:\n"); //system call to print error if occured
                return -1;
            }
        }
    }

    iRet = makeCopyOfFile(fd,fd2,offset); //call to user defined function
    
    if(iRet == -1)
    {
        perror("Error Occured while Making Copy of File:\n");

        //system call to close opened files
        close(fd);
        close(fd2);
        return -1;
    }
    else 
    {
        printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
    }

    //System call to cloed opened files
    close(fd);
    close(fd2);

    return 0;
}