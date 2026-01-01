/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
            Reverse File Content
            Problem Statement:
                Display the contents of a file in reverse order.
            Input:
                File name.
            Output:
                File content printed in reverse.
      
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

/*
    Function Name: displayFileInRevOrder
    Date: 01/01/2026
    Description: To Print File Contents in reverese order
*/
int displayFileInRevOrder(int fd)
{
    char * fileData = NULL;
    int iRet = 0;
    struct stat sobj;
    int fileSize  = 0;
    int i = 0;

    iRet = fstat(fd,&sobj); //System call to get statistics of File 

    if(iRet == -1)
    {
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = read(fd,fileData,fileSize); //system call to read data from file 

    if(iRet == -1)
    {
        return -1;
    }

    //Logic To Print file in reverse order 
    for(i = fileSize;i > -1;i--)
    {
        printf("%c",fileData[i]);
    }
    printf("\n");

    return iRet;

}

//Entry Point function
int main(int argc,char * argv[])
{
    char * fileName = NULL;
    int fd = 0;
    int iRet = 0;

    printf("Jay Ganesh....\n");

    fileName = argv[1];

    if(argc < 2)
    {
        printf("Invalid Number of Arguments Passed\n");
        return -1;
    }
    fd = open(fileName,O_RDONLY); //system call to open file in read mode only 

    if(fd == -1)
    {
        perror("Error Occured While Opening file in read mode:"); //system call to print system call errors
        return -1;
    }

    iRet = displayFileInRevOrder(fd); //call to userdefinef function

    if(iRet == -1)
    {
        perror("Error Occured while printing file Data in Reverse Order:\n");  //system call to print file in reverse order
        return -1;
    }
    else 
    {
        printf("%d Bytes successfully readed and printed in Reverse Order:\n",iRet);
    }

    close(fd); //system call to close opened file 

    return 0;
}