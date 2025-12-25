///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 23/12/2025
//  Program: Write String to File
//              •Accept file name and a string from user.
//              •Write string using write() (append mode by default).
//              •Print number of bytes written.
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: openFile
//  Parameter: filename (char[])
//  Purpose: User Defined Function To Open File in Write Mode (Append By Default)
//  Return value: fd (file Descriptor) of opened file
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int openFile(char fileName[50])
{
    int fd = 0;
    
    fd = open(fileName,O_WRONLY | O_APPEND | O_CREAT,0777);     //System call to open file in write mode(Appen Mode By Default)

    if(fd < 0)
    {
        return -1;           // If Error Occurs while opening file
    }
    else
    {
        return fd;          // If File Open Successfully
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: writeDataIntoFile
//  Paramters: data,fd,size (char[],int,int)
//  Purpose: User Defined function to write data into file 
//  Return Value: Number of bytes written into file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int writeDataIntoFile(char data[50],int fd,int size)
{
    int iRet = 0;
    
    iRet = write(fd,data,size);         //System call to write data into file 

    if(iRet < 0)
    {
        return -1;               // If Failed to write Data into file
    }
    else 
    {
        return iRet;             // Number of bytes written into file
    }
}

//Entry Point Function
int main()
{
    char arr[50];
    char brr[50];

    int iRet = 0;
    int fd = 0;
    
    memset(arr,'\0',sizeof(arr));
    memset(brr,'\0',sizeof(brr));

    printf("Jay Ganesh.....\n");
    
    //Taking File Name as Input from user 
    printf("Enter File Name You want to write string into: \n");
    scanf("%s",arr);

    //Taking Data which need to be written into file from user
    printf("Enter String You Want to Write:\n");
    scanf(" %[^'\n']s",brr);

    fd = openFile(arr);  //Call to user defined function to open file

    if(fd < 0)
    {
        perror("Error Occured while Opening File: ");
        return -1;
    }

    iRet = writeDataIntoFile(brr,fd,strlen(brr));  // call to user defined function to write data into file

    if(iRet < 0)
    {
        perror("Error Occured While Writing Data into File");
        return -1;
    }
    else 
    {
        printf("%d Bytes Gets Successfully Written into File\n",iRet);
    }

    close(iRet);

    return 0;
}