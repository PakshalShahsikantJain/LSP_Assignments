///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 21/12/2025
//  Program: Read N Bytes From File
//              •Accept File name and number of bytes N.
//              •Read exactly N bytes using read() and print on console.
//              •If File contains less than N, print only available bytes
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

//////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: readDataFromFile
//  Paramters: fileName,no (char[],int)
//  Description: User Defined FunctionTo Read exactly N bytes using read() system call and print Data on console.
//  Return Value: void
//
///////////////////////////////////////////////////////////////////////////////////
void readDataFromFile(char fileName[50],int no)
{
    int fd = 0;
    int iRet = 0;
    char *arr = NULL;

    arr = (char *)malloc(no * sizeof(char));

    fd = open(fileName,O_RDONLY);   //system call to open file in Read Mode Only.

    if(fd > -1)          // if file gets successfully
    {
        iRet = read(fd,arr,no);     //System call to read data from file upto specified number of bytes

        if(iRet != -1)   // if read() successfully reads data from file
        {
            printf("Data From file is: %s\n",arr);       //Displaying Data On Console
            printf("Number of Bytes readed from file is: %d\n",iRet);   
        }
        else            // if error occurs during reading data from file
        {
            perror("Error Occured while reading Data From File");    //system call to display excat error
        }

    }
    else               // if error occurs dunring opening file
    {
        perror("Error");    //system call to display excat error 
    }
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Entry point function
int main()
{
    char arr[50];
    int iNo = 0;

    memset(arr,'\0',sizeof(arr));

    printf("Jay Ganesh....\n");

    //Taking File Name as input from user
    printf("Enter File Name: \n");
    scanf("%s",arr);

    //Taking number of bytes to read from file from user
    printf("Enter Number of Bytes You want to read from file: \n");
    scanf("%d",&iNo);

    readDataFromFile(arr,iNo);   // call to userdefined function

    return 0;
}