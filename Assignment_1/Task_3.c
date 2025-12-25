///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 21/12/2025
//  Task: Check File Access Permission
//              •Accept Fille name and mode (read/write/execute).
//              •Use access() to check permission for current process.
//              •Print “Accessible / Not accessible” with reason.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define TRUE 0
#define FALSE 1

typedef int BOOL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: checkFileAccessPermissions
//  Parameters: fileName,mode (char,int)
//  Description: Checks File Access Permission if Accessible or not in give mode
//  Return Value : TRUE on Success else FALSE
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL checkFileAccessPermissions(char fileName[50],int mode)
{
    int iRet = 0;

    iRet = access(fileName,mode);   //system call to check file access permissions

    if(iRet == 0)
    {
        return TRUE;               // if accessible in given mode 
    }
    else 
    {
        return FALSE;              // if not accessible in given mode
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: strcmpx
//  Parameters: str1,str2 (char *,char *)
//  Description: Compares Two Strings if equal or not
//  Return Value : TRUE on Success else FALSE
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        return FALSE;            //if given strings are not equal
    }
    else 
    {
        return TRUE;            //ig given string are equal
    }
}

//Entry Point Function
int main()
{
    char arr[50];
    char brr[50];
    int mode = 0;
    BOOL bret = FALSE;

    printf("Jay Ganesh....\n");

    memset(arr,'\0',sizeof(arr));
    memset(brr,'\0',sizeof(brr));
    //Taking File Name as input from user
    printf("Enter File Name: \n");
    scanf("%s",arr);

    //Taking file mode as input from user
    printf("Enter Mode To Check if File is accessible or not in that mode: \n");
    scanf("%s",brr);

    if(strcmpx(brr,"read") == TRUE)
    {
        mode = R_OK;
    }
    else if(strcmpx(brr,"write") == TRUE)
    {
        mode = W_OK;
    }
    else if(strcmpx(brr,"execute") == TRUE)
    {
        mode = X_OK;
    }

    bret = checkFileAccessPermissions(arr,mode);  //call to user defined function

    if(bret == TRUE)
    {
        if(mode == R_OK)
        {
            printf("File is Accessible in read mode\n");
        }
        else if(mode == W_OK)
        {
            printf("File is Accessible in write mode\n");
        }
        else if(mode == X_OK)
        {
            printf("File is Accessible in execute mode\n");
        }
    }
    else 
    {
        perror("Error");
    }

    return 0;
}