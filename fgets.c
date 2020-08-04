#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* ExternRead(char *FileDir,FILE *fp,char str[]);
int main()
{
//    FILE *fp;
//    char str[60];

//    /* 打开用于读取的文件 */
//    fp = fopen("file.txt" , "r");
//    if(fp == NULL) {
//       perror("打开文件时发生错误");
//       return(-1);
//    }
//    if( fgets (str, 60, fp)!=NULL ) {
//       /* 向标准输出 stdout 写入内容 */
//       //puts(str);
//       printf("%s",str);
//    }
//    if( fgets (str, 60, fp)!=NULL ) {
//       /* 向标准输出 stdout 写入内容 */
//       //puts(str);
//       printf("%s",str);
//    }
    FILE *fp;
    char str[60];
    /* 打开用于读取的文件 */
    char *FileDir="file.txt";
    fp = fopen(FileDir , "r");
    ExternRead(FileDir,fp,str);
    //if (0==strncmp(str,"extern",6))
    printf("%s",str);
    ExternRead(FileDir,fp,str);
    printf("%s,%d",str,strncmp(str,"extern",6));
    printf("%s",fgets(str, 60, fp));
    fclose(fp);
    return(0);
}

char* ExternRead(char *FileDir,FILE *fp,char str[])
{
    char *ex="extern";
    if(fp == NULL) {
        perror("打开文件时发生错误");
        return NULL;
   }
    if(fgets(str, 60, fp)!=NULL) {
    /* 向标准输出 stdout 写入内容 
    fgets函数从文件读取'\n'并存储，在'\n'后再增加一个'\0'构成字符串。
    */
        if (0==strncmp(str,ex,7)){
            printf("%d",strncmp(str,ex,7));
            return str;
        }
        //puts(str);
        //printf("%u",strlen(str));
    return NULL;
   }
   return NULL;
}