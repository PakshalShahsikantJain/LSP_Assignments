///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 23/12/2025
//  Program: Find Largest File in Directory
//              •Accept directory name.
//              •Find and print:
//                  ◦largest le name
//                  ◦its size in bytes
//           Consider only regular les (ignore directories).
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include<string.h>
#include<sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: readDirectoryFile
//  Parameters: dp (DIR *)
//  Purpose: To List All Files From Directory
//  Return Value: void 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readDirectoryFile(DIR *dp) 
{
    struct dirent *ptr = NULL;

    struct stat sobj;
    char * fileName = NULL;

    long int iMax = 0; 

    while(ptr = readdir(dp))             //system call to list out all files present in directory
    {   
        lstat(ptr->d_name,&sobj);        //System call to get status of file 

        printf("File Name: %s\n",ptr->d_name);
        printf("File Size: %ld\n",sobj.st_size);

        if(S_ISREG(sobj.st_mode))       //system call to get status of file
        {
            if(iMax < sobj.st_size)    
            {
                iMax = sobj.st_size;
                fileName = ptr->d_name;
            }
        }
        
        printf("------------------------------------------------------\n");
    }
    

    printf("Largest File in Directory is: \n");
    printf("File Name: %s\n",fileName);
    printf("File Size is: %ld\n",iMax);

    closedir(dp);   //system call to close opened file
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name:openDirectory
//  Paramters: fileName (char[])
//  Purpose: User Defined Function To Open Directory
//  Return Value: openDirectory
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void openDirectory(char fileName[50])
{
    DIR *dp = NULL;

    dp = opendir(fileName);    //system call to open given directory

    if(dp != NULL)
    {   
        readDirectoryFile(dp);   //call to user defined function
    }
    else 
    {
        perror("Error Occured While Opening Diretory");   //system call to print error
        return;
    }
}

//Entry Point Function
int main()
{
    char arr[50];

    memset(arr,'\0',sizeof(arr));    // system call to set localbuffer with '\0

    printf("Jay Ganesh....\n");

    //Taking Directory Name as input from user 
    printf("Enter Director Name You want To Open: \n");
    scanf("%s",arr);

    openDirectory(arr); //Call To User Defined function
 
    return 0;
}