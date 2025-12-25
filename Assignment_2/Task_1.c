///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 22/12/2025
//  Program: Read Whole File
//              •Accept le name and print full content on console.
//              •Use a buffer loop (read() until 0).
//              •Show total bytes read.
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: readDataFromFile
//  Parameters: fd,filesize (int,int)
//  Description: User Defined Function To Read Whole File and Display full content on console
//  Return Value: void
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void readDataFromFile(int fd,int fileSize)
{
    char *arr = NULL;
    int iRet = 0;

    arr = (char *)malloc(fileSize * sizeof(char));
    
    iRet = read(fd,arr,fileSize);   //System call to read Data From File 

    if(iRet != -1)
    {
        printf("Data From File is:\n");
        while(*arr != '\0')
        {
            printf("%c",*arr);
            arr++;
        }

        printf("\nTotal Bytes Readed From File is: %d\n",iRet);
    }
    else 
    {
        perror("read() Error");
    }

    close(fd);
    arr = NULL;
    free(arr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: openFileInReadMode
//  Parameters: fileName
//  Description: User Defined Function To Open File in Read Mode
//  Return Value: void
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void openFileInReadMode(char * fileName)
{
    int fd = 0;
    struct stat sobj;
    int iRet = 0;
    int fileSize = 0;

    fd = open(fileName,O_RDONLY);    //System call to open given file in given mode 

    if(fd != -1)
    {
        iRet = stat(fileName,&sobj);    //System call to get file staus 
        
        if(iRet == 0)
        {
            fileSize = sobj.st_size;

            readDataFromFile(fd,fileSize);   //call to user define function
        }
        else
        {
            perror("stat() Error");
            return;
        }
    }
    else 
    {
        perror("open() Error");
        return;
    }

}

//Entry Point Function
int main()
{
    char arr[50];

    memset(arr,'\0',sizeof(arr));

    printf("Jay Ganesh....\n");

    //Taking Filename as input from user
    printf("Enter File Name: \n");
    scanf("%s",arr);

    openFileInReadMode(arr);    //call to user defined function

    return 0;
}