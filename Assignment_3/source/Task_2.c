#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>

#define TRUE 0
#define FALSE 1

typedef int BOOL;

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
        return TRUE;
    }
    else 
    {
        return FALSE;
    }

}

int main()
{
    char arr[50];
    char brr[50];
    BOOL bret = FALSE;
    
    DIR *dp = NULL;

    memset(arr,'\0',sizeof(arr));
    memset(brr,'\0',sizeof(brr));

    printf("Jay Ganesh....\n");

    printf("Enter Directory Name You Want To Search File In\n");
    scanf("%s",arr);

    printf("Enter File Name You Want To Check \n");
    scanf("%s",brr);
    
    dp = opendir(arr);

    if(dp == NULL)
    {
        perror("Error Occured While Opening Directory");
        return -1;
    }

    bret = checkFilePresence(dp,brr);

    if(bret == TRUE)
    {
        printf("%s File is Present in Directory %s\n",brr,arr);
    }    
    else 
    {
        printf("%s File is Not Present in Directory %s\n",brr,arr);
    }

    return 0;
}