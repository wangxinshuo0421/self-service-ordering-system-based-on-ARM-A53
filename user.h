#ifndef __USER__
#define __USER__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UserFile "user.txt"

int NameInputFlag = 0;
int PasswordInputFlag = 0;
int userNameInput = 0;
int userPasswordInput = 0;
int loginPageFreshFlag = 1;


struct User{
    int userName;
    int userPassword;
    int isSelected;
    struct User* next;
};


struct User* initUserFile(){
    struct User* head = (struct User*)malloc(sizeof(struct User));   //创建头结点
    struct User* node = NULL,* end = head;
    FILE* filePoint;
    filePoint = fopen(UserFile,"r");
    int user,password;

    /*打开文件操作*/
    if(filePoint == NULL){
        printf("fail to open the User file\n");
        return NULL;
    }else{
        printf("open the User file\n");
    }
    while( fscanf(filePoint,"%d %d",&user,&password) != EOF ) {     //按行读取用户文件
        //printf("read user name = %d;password = %d\n",user,password);
        node = (struct User*)malloc(sizeof(struct User));
        node->userName = user;
        node->userPassword = password;
        node->isSelected = 0;
        end->next = node;
        end = node;
    }
    end->next = NULL;   //结束创建
    fclose(filePoint);  //关闭文件
    return head;
}

int writeUserInFile(int userName,int password){
    char buf[30];
    FILE* filePoint;
    filePoint = fopen(UserFile,"a");    //追加文本
    sprintf(buf,"%4d\n%4d\n",userName,password);
    fputs(buf,filePoint);
    fclose(filePoint);
    return 1;
}

#endif