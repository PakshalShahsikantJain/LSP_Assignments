/*
    Author : Pakshal Shashikant Jain
    Date: 01/01/2026
    Program:Write tree_clone.c which prints a directory as a tree, like: 
                root/
                    a.txt
                    src/
                        Ganesh.c
            •Indentation based on recursion depth
            •Print type markers:
                ◦[D] directory
                ◦[F] regular le
                ◦[L] symbolic link
            •Use lstat() to detect symbolic links.
            •Do not follow symlink directories (avoid loops).
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
    char fullPath[260];
    int iRet = 0;
    static int depth = 0;
    DIR * sdp = NULL;
    int i = 0;

    memset(fullPath,'\0',sizeof(fullPath)); //system call to set local buffer with '\0' upto size of file

    if(depth < 1)
    {
        printf("%s/\n",dirPath);
    }
    
    while((ptr = readdir(dp)) != NULL)   //readdir system call to read directory file
    {
        if((strcmp(ptr->d_name,".") != 0)&&(strcmp(ptr->d_name,"..") != 0))
        {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, ptr->d_name);    //library function to generate full path of directory
 
            iRet = lstat(fullPath,&sobj);  //system call to get statistical information of file
            if(iRet == -1)
            {
                break;
            }
            
            //Logic to Print Directory as a tree
            for(i = 0;i <= depth;i++)
            {
                printf("\t");
            }

            if(ptr->d_type == DT_DIR)   //if file is directory file
            {
                printf("[D] %s/\n",ptr->d_name);
                sdp = opendir(fullPath);  //system call to open directory file

                if(sdp != NULL)
                {
                    depth++;
                    directoryTraversal(sdp,fullPath);   //recrusive call to directoryTraversal() 
                    depth--;
                }
                else 
                {
                    perror("Error Occured While Opening Subdirectory: ");   //system call to print system call errors
                    return;
                }
            }
            else if(ptr->d_type == DT_LNK)  //file is symbolic link
            {
                printf("[L] %s\n",ptr->d_name);
            }
            else if(ptr->d_type == DT_REG)  //file is regularfile 
            {
                printf("[F] %s\n",ptr->d_name);
            }
        }

    }

    if(iRet == -1)
    {
        perror("Error Occured When Stat of file: "); //system call print system call error
        return;
    }
}


//Entry Point Function
int main(int argc,char * argv[])
{
    DIR * dp = NULL;
    char * dirPath = NULL;

    printf("Jay Ganesh.....\n");

    if(argc < 2) 
    {
        printf("Invalid Number of arguments entered,please enter valid number of arguments\n");
        return -1;    //on error 
    }

    dirPath = argv[1];
    
    dp = opendir(dirPath);   //system call to open directory file

    if(dp == NULL)
    {
        perror("Error Occured while open directory");

        return -1;    //on error 
    }

    //Call to user defined function
    directoryTraversal(dp,dirPath);

    
    return 0;
}