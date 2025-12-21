///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 20/12/2025
//  Task: Open File in Given Mode
//          •Accept File name and mode (R, W, RW, A) from user.
//          •Convert mode to ags (O_RDONLY, O_WRONLY, O_RDWR, O_APPEND | O_CREAT).
//          •Open le accordingly and display fd.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Rquired Header Files
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

/////////////////////////////////////////
//
//  Function Name: openGivenFile
//  Parameter1: Name of File Which need to open
//  Parameter2: Mode In Which File Needs to Open
//  Data Type of Parameters: char, int 
//  Return Value Data Type: int
//
/////////////////////////////////////////
int openGivenFileInGivenMode(char fileName[50],int mode) 
{
    int fd = 0;

    fd = open(fileName,mode | O_CREAT);   //open() system call to open the file in given mode

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
    char brr[20];   
    int mode = 0;
    int iOption = 0;
    int iRet = 0;

    printf("Jay Ganesh...\n");
    
    //clean the Array and set with const value '\0' upto the size of array
    memset(arr,'\0',sizeof(arr));

    //Take File Name as input from user
    printf("Enter File Name You Want To Open: \n");
    scanf("%s",arr);

    //Take Read Mode From User    
    printf("Select Mode In Which You Want To Open File: \n");
    printf("1. R (Read Mode Only)\n");
    printf("2. W (Write Mode Only)\n");
    printf("3: RW (Read Write Mode)\n");
    printf("4: A (Append Mode)\n");

    printf("Enter Option Number: ");
    scanf("%d",&iOption);

    switch(iOption) 
    {
        case 1:
        {
            printf("Mode Selected Read Only\n");
            mode = O_RDONLY;
            break;           
        }
        case 2:
        {
            printf("Mode Selected Write Only\n");
            mode = O_WRONLY;
            break;
        }
        case 3:
        {
            printf("Mode Selected Read Write\n");
            mode = O_RDWR;
            break;
        }
        case 4:
        {
            printf("Mode Selected Append\n");
            mode = O_APPEND;
            break;
        }
        default:
        {
            printf("Invalid Mode Entered Please Enter Valid Mode");
            return 1;
        }
    };
    
    iRet = openGivenFileInGivenMode(arr,mode); //Call to user-defined function  

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