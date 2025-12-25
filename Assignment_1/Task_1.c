///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 20/12/2025
//  Task: Open File
//          •Accept File name from user and open it using open().
//          •Print: success message + returned le descriptor.
//          •Handle errors using perror()
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Rquired Header Files
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

/////////////////////////////////////////
//
//  Function Name: openGivenFile
//  Parameter: Name of File Which need to open
//  Data Type of Parameter: char 
//  Return Value : File Descriptor (fd) of opened file 
//
/////////////////////////////////////////
int openGivenFile(char fileName[50]) 
{
    int fd = 0;

    fd = open(fileName,O_RDONLY);   //open() system call to open the file in read mode only

    if(fd < 0)
    {
        return -1;            // If Open System call return negative number if failure / error occurs
    }
    else 
    {
        return fd;            // If open system call returns non-negative number on success
    }
}

//Entry Point Function
int main()
{
    char arr[50];
    int iRet = 0;

    printf("Jay Ganesh...\n");
    
    //clean the Array and set with const value '\0' upto the size of array
    memset(arr,'\0',sizeof(arr));

    //Take File Name as input from user
    printf("Enter File Name You Want To Open: \n");
    scanf("%s",arr);

    iRet = openGivenFile(arr); //Call to user-defined function  

    //Ouput of Program
    if(iRet < 0) 
    {
        perror("Error Occured While Opening File");
        return -1;
    }
    else 
    {
        printf("File Gets Successfully opened with File Descriptor: %d\n",iRet);
        
        close(iRet);     //Close the file after all operations
    }
    
    return 0;   //return success to OS
}