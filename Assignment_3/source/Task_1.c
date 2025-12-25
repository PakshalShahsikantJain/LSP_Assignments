#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void copyFileContentsFromSrcToDest(int fd,int fd2) 
{
    char * srcData = NULL;
    size_t srcFileSize = 0;
    mode_t mode = 0;
    int iRet = 0;
    struct stat sobj;

    iRet = fstat(fd,&sobj);

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

    iRet = read(fd,srcData,srcFileSize);
    
    if(iRet != -1)
    {
        printf("%d Bytes Succesfully readed from file\n",iRet);
    }
    else 
    {
        perror("Error Occured While Reading Data From File");
        return;
    }

    close(fd);

    iRet = fchmod(fd2,mode);

    if(iRet != -1)
    {
        printf("chmod of Destination File Done Successfully\n");
    }
    else 
    {
        perror("Error Occured while changing mode of destination File");
    }
    
    iRet = write(fd2,srcData,srcFileSize);

    if(iRet != -1)
    {
        printf("%d Bytes Successfully Written into file\n",iRet);
    }
    else 
    {
        perror("Error Occured While Writing Data into File");
        return;
    }

    close(fd2);
}

int openFileInWriteMode(char fileName[50]) 
{
    int fd = open(fileName,O_WRONLY | O_APPEND | O_CREAT,0777);

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

int openFileInReadMode(char fileName[50])
{
    int fd = open(fileName,O_RDONLY);

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

int main()
{
    char src[50];
    char dest[50];
    int fd = 0;
    int fd2 = 0;

    memset(src,'\0',sizeof(src));
    memset(dest,'\0',sizeof(dest));

    printf("Jay Ganesh....\n");

    printf("Enter Source File Name You Want to read data From: \n");
    scanf("%s",src);

    printf("Enter Destination File Name You Want to write data in \n");
    scanf("%s",dest);

    fd = openFileInReadMode(src);

    if(fd == -1)
    {
        return -1;
    }

    fd2 = openFileInWriteMode(dest);

    if(fd2 == -1)
    {
        return -1;
    }

    copyFileContentsFromSrcToDest(fd,fd2);
    
    return 0;
}