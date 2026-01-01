/*
    Author : Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: Create dir_report.c that recursively calculates:
                •Total number of les
                •Total number of directories
                •Total size of regular les (in bytes)
                •Largest le name + size
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/*
    Function Name: directoryTraversal
    Parameters: dp (pointer to directory file address), dirPath (Name of Directory)
    Description: TO Travel Directory File
    Return Value: Nothing
*/
void directoryTraversal(DIR * dp,char dirPath[100])
{
    struct dirent * ptr = NULL;
    struct stat sobj;
    char * largestFileName = NULL;
    char fullPath[260];
    int iRet = 0;
    int iDirCnt = 0;
    int iFCnt = 0;
    int totalSize = 0;
    int iMax = 0;
    DIR * sdp = NULL;

    memset(fullPath,'\0',sizeof(fullPath)); //system call to set local buffer with '\0' upto size of file
    
    while((ptr = readdir(dp)) != NULL)   //readdir system call to read directory file
    {
        if((strcmp(ptr->d_name,".") != 0)&&(strcmp(ptr->d_name,"..") != 0))
        {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, ptr->d_name);  //library function to generate full path of directory

            iRet = lstat(fullPath,&sobj); //system call to get statistical information of file
            if(iRet == -1)
            {
                break;
            }
            

            if(S_ISDIR(sobj.st_mode))  //if file is directory file
            {
                sdp = opendir(fullPath); //system call to open directory file

                if(sdp != NULL)
                {
                    iDirCnt++;        //counting total directories present
                }
                else 
                {
                    perror("Error Occured While Opening Subdirectory: ");
                    return;
                }
            }
            else if(S_ISREG(sobj.st_mode))  //file is regularfile 
            {
                iFCnt++; // count total number of files
                totalSize = totalSize + sobj.st_size; //calucating total size of files present in directory

                //Finding largest file present in directory
                if(iMax < sobj.st_size)
                {
                    iMax = sobj.st_size;
                    largestFileName = ptr->d_name;
                }
            }
            else 
            {
                iFCnt++; //counting total number of files
            } 
        }
    }

    if(iRet == -1)
    {
        perror("Error Occured When Stat of file: ");  //system call to print system call errors
        return;
    }

    printf("Files: %d\n",iFCnt);
    printf("Dirs: %d\n",iDirCnt);
    printf("Total Size: %d bytes\n",totalSize);
    printf("Largest: %s (%d bytes)\n",largestFileName,iMax);
}

//Entry Point function
int main(int argc,char * argv[])
{
    DIR * dp = NULL;
    char * dirPath = NULL;

    printf("Jay Ganesh.....\n");

    if(argc < 2)
    {
        printf("Invalid Number of arguments entered,please enter valid number of arguments\n");
        return 1;
    }

    dirPath = argv[1];  //taking directory path from command line
    
    dp = opendir(dirPath); //system call to open directory file

    if(dp == NULL)
    {
        perror("Error Occured while open directory");

        return -1;
    }

    directoryTraversal(dp,dirPath); //call to user defined function


    return 0;
}