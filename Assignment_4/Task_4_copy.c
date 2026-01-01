/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
            Reverse File Content
            Problem Statement:
                Display the contents of a file in reverse order.
            Input:
                File name.
            Output:
                File content printed in reverse.
      
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

/*
    Function Name: displayFileInRevOrder
    Date: 01/01/2026
    Description: To Print File Contents in reverese order
*/
int displayFileInRevOrder(int fd)
{
    char * fileData = NULL;
    int iRet = 0;
    struct stat sobj;
    int fileSize  = 0;
    int i = 0;

    iRet = fstat(fd,&sobj); //System call to get statistics of File 

    if(iRet == -1)
    {
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = read(fd,fileData,fileSize); //system call to read data from file 

    if(iRet == -1)
    {
        return -1;
    }

    //Logic To Print file in reverse order 
    for(i = fileSize;i > -1;i--)
    {
        printf("%c",fileData[i]);
    }
    printf("\n");

    return iRet;

}

//Entry Point function
int main(int argc,char * argv[])
{
    char * fileName = NULL;
    int fd = 0;
    int iRet = 0;

    printf("Jay Ganesh....\n");

    fileName = argv[1];

    if(argc < 2)
    {
        printf("Invalid Number of Arguments Passed\n");
        return -1;
    }
    fd = open(fileName,O_RDONLY); //system call to open file in read mode only 

    if(fd == -1)
    {
        perror("Error Occured While Opening file in read mode:"); //system call to print system call errors
        return -1;
    }

    iRet = displayFileInRevOrder(fd); //call to userdefinef function

    if(iRet == -1)
    {
        perror("Error Occured while printing file Data in Reverse Order:\n");  //system call to print file in reverse order
        return -1;
    }
    else 
    {
        printf("%d Bytes successfully readed and printed in Reverse Order:\n",iRet);
    }

    close(fd); //system call to close opened file 

    return 0;
}
/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
            File Merge Utility
                Problem Statement:
                    Merge multiple input fles into a single output file.
                Input:
                    output_file file1 file2 file3 ...
                Output:
                    Combined file content in order.
      
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: makeCopyOfFile
//  Parameters: fd1 (File Descriptor of Source File), fd2 (File Descriptor of Destination File) 
//  Description: Merges multiple input fles into a single output file.
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int makeCopyOfFile(int fd1,int fd2)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj); //system call to get files statistical information

    if(iRet != 0)
    {
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = read(fd1,fileData,fileSize); //system call to read data from file 

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);    
    }

    iRet = write(fd2,fileData,fileSize); //sytem call to write data into file

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        if(lseek(fd2,0,SEEK_END) != -1) // system call to change current file offset to specified position
        {
            write(fd2,"\n",1);  //system call to write data into file 
        }
        
        return iRet;
    }
}

//Entry Point Function
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int iRet = 0;
    int i = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 3)
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;
    }

    destFile = argv[1];
    
    //Loop To Iterated through command line arguments from specified index
    for(i = 2;i < argc;i++)
    {
        srcFile = argv[i];

        fd = open(srcFile,O_RDONLY); //system call to open file in read mode only

        if(fd == -1)
        {
            perror("Error Occured While Opening Source File in Read mode: ");
            return -1;
        }


        fd2 = open(destFile,O_WRONLY | O_APPEND); //system call to open file in write and append mode 

        if(fd2 == -1)
        {
            if(errno == ENOENT)
            {
                fd2 = creat(destFile,0777); //system call to creat file 

                if(fd2 == -1)
                {
                    perror("Error Occcured while creating file:\n");
                    return -1;
                }
                else 
                {
                    printf("Destination File %s Get Successfully Created with fd %d Making Copy of File\n",destFile,fd2);
                }
            }
            else if(errno == EACCES)
            {
                iRet = fchmod(fd,0777); //system call to change file permissions

                if(iRet == -1)
                {
                    perror("Error Occured While Changing Mode:\n");
                    return -1;
                }
            }
        }

        iRet = makeCopyOfFile(fd,fd2); //call to user defined function
        
        if(iRet == -1)
        {
            perror("Error Occured while Making Copy of File:\n"); //system call to print system call errors

            //system call to close opened files
            close(fd);
            close(fd2);
            return -1;
        }
        else 
        {
            printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
        }

        //system call to close opened files
        close(fd);
        close(fd2);
    }

    return 0;
}
/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
        File Copy Using pread & pwrite
            Problem Statement:
                Copy a file using pread() and pwrite() without changing the file offset.
            Input:
                Source and destination file names.
            Output:
                Copied file identical to source.
      
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: makeCopyOfFile
//  Parameters: fd1 (File Descriptor of Source File), fd2 (File Descriptor of Destination File)
//  Description: Copies a File witout changing its offset
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int makeCopyOfFile(int fd1,int fd2)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    off_t offset = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj);  //system call to get statistics of file 

    if(iRet != 0)
    {
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = pread(fd1,fileData,fileSize,offset); //system call to read data from file without changing files offset

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);
        offset = lseek(fd1,0,SEEK_CUR); //system call to check current file offset position
        printf("Current Offset is: %ld\n",offset);   //0  : offset halat nahi
    
    }

    iRet = pwrite(fd2,fileData,fileSize,offset); //system call to copy data into file without changing files offset 

    if(iRet == -1)
    {
        return -1;  //on error
    }
    else 
    {
        return iRet; //on success
    }
}


//Entry Point Function
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int iRet = 0;
    off_t offset = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 3)
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;
    }

    srcFile = argv[1];
    destFile = argv[2];

    fd = open(srcFile,O_RDONLY); //system call to open file in read mode only

    if(fd == -1)
    {
        perror("Error Occured While Opening Source File in Read mode: ");
        return -1;
    }


    fd2 = open(destFile,O_WRONLY | O_APPEND); //system call to open file in write and append mode

    if(fd2 == -1)
    {
        if(errno == ENOENT) 
        {
            fd2 = creat(destFile,0777);  //system call to create file with specified permission

            if(fd2 == -1)
            {
                perror("Error Occcured while creating file:\n");
                return -1;
            }
            else 
            {
                printf("Destination File %s Get Successfully Created with fd %d Making Copy of File\n",destFile,fd2);
            }
        }
        else if(errno == EACCES)
        {
            iRet = fchmod(fd,0777); //system call to change file permission

            if(iRet == -1)
            {
                perror("Error Occured While Changing Mode:\n");
                return -1;
            }
        }
    }

    iRet = makeCopyOfFile(fd,fd2); //call to user defined function
    
    if(iRet == -1)
    {
        perror("Error Occured while Making Copy of File:\n");

        //system call to close files
        close(fd);
        close(fd2);
        return -1;
    }
    else 
    {
        printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
        offset = lseek(fd2,0,SEEK_CUR); //system call to check files's current offset position
        printf("Current Offset is: %ld\n",offset); 
    }

    //system call to close files
    close(fd);
    close(fd2);

    return 0;
}
/*
    Author: Pakshal Shashikant Jain
    Date: 01/01/2026
    Program: 
        File Copy with Offset
            Problem Statement:
                Copy a File starting from a given byte offset of the source le.
            Input:
                source_file destination_file offset
            Output:
                Partial file copied starting from offset.
      
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: makeCopyOfFile
//  Parameters: fd1 (File Descriptor of Source File), fd2 (File Descriptor of Destination File), offset 
//  Description: Copy a File starting from a given byte offset of the source file.
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int makeCopyOfFile(int fd1,int fd2,off_t offset)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj);  //system call to fetch statistics of file 

    if(iRet != 0)
    {
        perror("Error Occured While Getting Status of File:");
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));

    iRet = lseek(fd1,offset,SEEK_CUR);  //system call to change offset of a file to specified offset

    if(offset > fileSize)
    {
        fileSize = fileSize + offset;
    }
    
    fileSize = fileSize - offset;

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("Current Offset Location is: %d\n",iRet);
    }

    iRet = read(fd1,fileData,fileSize);   //system call to read data from file from changed offset

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);
    }

    iRet = write(fd2,fileData,fileSize);  //system call to write copied data into destination file

    if(iRet == -1)
    {
        return -1;
    }
    else 
    {
        return iRet;
    }
}

//Entry Point Function
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int offset = 0;
    int iRet = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 4)
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;
    }

    srcFile = argv[1];
    destFile = argv[2];
    offset = atoi(argv[3]);

    fd = open(srcFile,O_RDONLY); //system call to open file in read only mode

    if(fd == -1)
    {
        perror("Error Occured While Opening Source File in Read mode: ");
        return -1;
    }


    fd2 = open(destFile,O_WRONLY | O_APPEND);  //system call to open file in write and append mode 

    if(fd2 == -1)
    {
        if(errno == ENOENT)
        {
            fd2 = creat(destFile,0777);   //system call to creat file with all permissions

            if(fd2 == -1)
            {
                perror("Error Occcured while creating file:\n");
                return -1;
            }
            else 
            {
                printf("Destination File %s Get Successfully Created with fd %d Making Copy of File\n",destFile,fd2);
            }
        }
        else if(errno == EACCES)
        {
            iRet = fchmod(fd,0777);  // system call to change permissions of file

            if(iRet == -1)
            {
                perror("Error Occured While Changing Mode:\n"); //system call to print error if occured
                return -1;
            }
        }
    }

    iRet = makeCopyOfFile(fd,fd2,offset); //call to user defined function
    
    if(iRet == -1)
    {
        perror("Error Occured while Making Copy of File:\n");

        //system call to close opened files
        close(fd);
        close(fd2);
        return -1;
    }
    else 
    {
        printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
    }

    //System call to cloed opened files
    close(fd);
    close(fd2);

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author: Pakshal Shashikant Jain
//  Date: 01/01/2026
//  Program: File Copy Utility
//           Problem Statement:
//              Write a program that copies the contents of one le into another.
//              Input:
//                  Source le name and destination le name as command-line arguments.
//              Output:
//                  Destination File containing an exact copy of source le.
//                  •Handle File-not-found and permission errors.
//                  •Destination File should be created if not present.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name: makeCopyOfFile
//  Parameters: fd1 (File Descriptor of Source File), fd2 (File Descriptor of Destination File)
//  Description: Makes Exact Copy of Source File into Destination File
//  Return Value: Numbe of Bytes copied
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int makeCopyOfFile(int fd1,int fd2)
{
    char * fileData = NULL;
    struct stat sobj;
    off_t fileSize = 0;
    int iRet = 0;

    iRet = fstat(fd1,&sobj);   // system call to fetch Files Statistics

    if(iRet != 0)
    {
        perror("Error Occured While Getting Status of File:");
        return -1;
    }

    fileSize = sobj.st_size;

    fileData = (char *)malloc(fileSize * (sizeof(char)));  

    iRet = read(fd1,fileData,fileSize);   //system call to read Data From File

    if(iRet == -1)
    {
        perror("Error while reading File:\n");
        return -1;
    }
    else 
    {
        printf("%d Bytes Successfully readed from File\n",iRet);
    }

    iRet = write(fd2,fileData,fileSize);  //system call to write Data into File

    if(iRet == -1)
    {
        return -1;    //on Error Occured
    }
    else 
    {
        return iRet;  //on Success
    }
}

//Entry Point Function with Command Line Arguments
int main(int argc,char * argv[])
{
    int fd = 0;
    int fd2 = 0;
    int iRet = 0;

    char * srcFile = NULL;
    char * destFile = NULL;

    printf("Jay Ganesh....\n");

    if(argc < 3)   
    {
        printf("Invalid Number of arguments entered.Please Enter Source File And Destination File Names\n");
        return -1;  //if command line arguments entered are less than expected number
    }

    srcFile = argv[1];
    destFile = argv[2];

    fd = open(srcFile,O_RDONLY);  //system call to open file in read mode 

    if(fd == -1)
    {
        perror("Error Occured While Opening Source File in Read mode: ");
        return -1;
    }


    fd2 = open(destFile,O_WRONLY | O_APPEND); //system call to open file in Write and Appedn Mode

    if(fd2 == -1)
    {
        if(errno == ENOENT)  //If File Not Found
        {
            fd2 = creat(destFile,0777); //system call to creat file

            if(fd2 == -1)
            {
                perror("Error Occcured while creating file:\n");
                return -1;
            }
            else 
            {
                printf("Destination File %s Get Successfully Created with fd %d Making Copy of File\n",destFile,fd2);
            }
        }
        else if(errno == EACCES)  //if file does not have necessary permissions to perform I/O Operations
        {
            iRet = fchmod(fd,0777);  //system call to change files permissions

            if(iRet == -1)
            {
                perror("Error Occured While Changing Mode:\n");
                return -1;
            }
        }
    }

    iRet = makeCopyOfFile(fd,fd2); // call to user definef function
    
    if(iRet == -1)
    {
        perror("Error Occured while Making Copy of File:\n");
        close(fd);  //system call to close the file
        close(fd2); //system call to cloee the file
        return -1;  //on error occured while making copy of file
    }
    else 
    {
        printf("%d Bytes successfully copied into destination file %s\n",iRet,destFile);
    }

    //system calls to close the file
    close(fd);   
    close(fd2);

    return 0;
}
