///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 25/12/2025
//  Program: Check File Present in Directory
//              •Accept directory name and le name.
//              •Check whether that le exists in that directory.
//              •Print absolute matched path if found.
//              
//        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include <limits.h>
#include <stdlib.h>

#define TRUE 0
#define FALSE 1

typedef int BOOL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: strcmpx
//  Parameters: str1,str2(char*,char *)
//  Purpose: To Compare Two Strings
//  Return Value: TRUE if Both String are Same else FALSE
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL strcmpx(char *str1,char *str2)
{   
    while((*str1 != '\0')&&(*str2 != '\0'))
    {
        if(*str1 != *str2)
        {
            break;
        }

        str1++;
        str2++;
    }

    if(*str1 != *str2)
    {
        return FALSE;
    }
    else 
    {
        return TRUE;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: checkFilePresence
//  Parameters: dp,fileName (DIR *,fileName)
//  Purpose: To Check if File is Present or not in the directory
//  Return Value: TRUE ON Success, FALSE ON Failure
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL checkFilePresence(DIR *dp,char fileName[50])
{
    struct dirent *ptr = NULL;

    while((ptr = readdir(dp)) != NULL)
    {
        if(strcmpx(ptr->d_name,fileName) == TRUE)
        {
            break;
        }
    }    

    if((ptr != NULL)&&(strcmpx(ptr->d_name,fileName) == TRUE))
    {
        return TRUE;   //On Success
    }
    else 
    {
        return FALSE;  //On Failure
    }

}

//Entry Point Function
int main()
{
    char arr[50];
    char brr[50];
    char absolutePath[200];

    BOOL bret = FALSE;
    
    DIR *dp = NULL;

    memset(arr,'\0',sizeof(arr));
    memset(brr,'\0',sizeof(brr));

    printf("Jay Ganesh....\n");

    //Taking Directoru Name AS Input from user
    printf("Enter Directory Name You Want To Search File In\n");
    scanf("%s",arr);

    //Taking File Name as input from user 
    printf("Enter File Name You Want To Check \n");
    scanf("%s",brr);
    
    dp = opendir(arr);  //System Call to open directory

    if(dp == NULL)
    {
        perror("Error Occured While Opening Directory");
        return -1;
    }

    bret = checkFilePresence(dp,brr);  //Call to userdefine function to check file presence

    if(bret == TRUE)
    {   
        if(realpath(brr,absolutePath) != NULL)
        {
            printf("%s File is Present in Directory %s\n",brr,absolutePath);
        }
        else 
        {
            perror("Erro Occured while getting absolute path: ");
            return -1;
        }
    }    
    else 
    {
        printf("%s File is Not Present in Directory %s\n",brr,arr);
    }

    return 0;
}