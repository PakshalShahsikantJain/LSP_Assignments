///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 25/12/2025
//  Program: Copy File Contents (source → destination)
//                  •Accept source_file and dest_file.
//                  •Create destination if not exists (O_CREAT | O_TRUNC).
//                  •Copy using buffered read()/write() loop.
//                  •Preserve permissions (optional bonus using stat() + chmod()).
//              
//        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: copyFileContentsFromSrcToDest
//  Paramters: fd,fd2 (int,int)
//  Purpose: To Copy File Contents from one file into another
//  Return Value: nothing   
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void copyFileContentsFromSrcToDest(int fd,int fd2) 
{
    char * srcData = NULL;
    size_t srcFileSize = 0;
    mode_t mode = 0;
    int iRet = 0;
    struct stat sobj;

    iRet = fstat(fd,&sobj);   //System call to get statistics of file 

    if(iRet != -1)
    {
        srcFileSize = sobj.st_size;
        mode = sobj.st_mode;
    }
    else
    {
        perror("Error Occured While getting File Status");
        return;
    }

    srcData = (char *)malloc(srcFileSize * sizeof(char));

    iRet = read(fd,srcData,srcFileSize);  //system call to read data from file
    
    if(iRet != -1)
    {
        printf("%d Bytes Succesfully readed from file\n",iRet);
    }
    else 
    {
        perror("Error Occured While Reading Data From File");
        return;
    }
 
    close(fd);                          //System call to close the opened file after reading is completed

    iRet = fchmod(fd2,mode);           //System call to change file permissions

    if(iRet != -1)
    {
        printf("chmod of Destination File Done Successfully\n");
    }
    else 
    {
        perror("Error Occured while changing mode of destination File");
    }
    
    iRet = write(fd2,srcData,srcFileSize);    //system call to write copied data into another file

    if(iRet != -1)
    {
        printf("%d Bytes Successfully Written into file\n",iRet);
    }
    else 
    {
        perror("Error Occured While Writing Data into File");
        return;
    }

    close(fd2);                            //system call to close the opened file after writing
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: openFileInWriteMode
//  Paramters: fileName (char [])
//  Purpose: To Open file in write Mode
//  Return Value: fd (file Descriptor) of Opened File 
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int openFileInWriteMode(char fileName[50]) 
{
    int fd = open(fileName,O_WRONLY | O_APPEND | O_CREAT,0777);   //system call to open file in write mode

    if(fd < 0)
    {
        perror("Error Occured While Opening File in Write Mode");
        return -1;
    }
    else 
    {
        return fd;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: openFileInReadMode
//  Paramters: fileName (char [])
//  Purpose: To Open file in read Mode
//  Return Value: fd (file Descriptor) of Opened File 
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int openFileInReadMode(char fileName[50])
{
    int fd = open(fileName,O_RDONLY);   //system call to open file in read mode

    if(fd < 0)
    {
        perror("Error Occured While Opening File in Read Mode");
        return -1;
    }
    else 
    {
        return fd;
    }
}

//Entry Point Function
int main()
{
    char src[50];
    char dest[50];
    int fd = 0;
    int fd2 = 0;

    memset(src,'\0',sizeof(src));
    memset(dest,'\0',sizeof(dest));

    printf("Jay Ganesh....\n");

    //Taking Source File Name as input from user
    printf("Enter Source File Name You Want to read data From: \n");
    scanf("%s",src);

    //Taking Destination File Name as input from user
    printf("Enter Destination File Name You Want to write data in \n");
    scanf("%s",dest);

    fd = openFileInReadMode(src);   //call to user define function to open file in read mode

    if(fd == -1)
    {
        return -1;
    }

    fd2 = openFileInWriteMode(dest);  //call to user defined function to open file in write mode

    if(fd2 == -1)
    {
        return -1;
    }

    copyFileContentsFromSrcToDest(fd,fd2);
    
    return 0;
}