/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
            File Merge Utility
                Problem Statement:
                    Merge multiple input fles into a single output file.
                Input:
                    output_file file1 file2 file3 ...
                Output:
                    Combined file content in order.
      
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
//  Description: Merges multiple input fles into a single output file.
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int makeCopyOfFile(int fd1,int fd2)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj); //system call to get files statistical information

    if(iRet != 0)
    {
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = read(fd1,fileData,fileSize); //system call to read data from file 

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);    
    }

    iRet = write(fd2,fileData,fileSize); //sytem call to write data into file

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        if(lseek(fd2,0,SEEK_END) != -1) // system call to change current file offset to specified position
        {
            write(fd2,"\n",1);  //system call to write data into file 
        }
        
        return iRet;
    }
}

//Entry Point Function
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int iRet = 0;
    int i = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 3)
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;
    }

    destFile = argv[1];
    
    //Loop To Iterated through command line arguments from specified index
    for(i = 2;i < argc;i++)
    {
        srcFile = argv[i];

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
            else if(errno == EACCES)
            {
                iRet = fchmod(fd,0777); //system call to change file permissions

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
            perror("Error Occured while Making Copy of File:\n"); //system call to print system call errors

            //system call to close opened files
            close(fd);
            close(fd2);
            return -1;
        }
        else 
        {
            printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
        }

        //system call to close opened files
        close(fd);
        close(fd2);
    }

    return 0;
}