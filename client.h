#ifndef __CLIENT__
#define __CLIENT__

#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "MyLib.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "user.h"
#include "food.h"

int sock;

void *startSendDitect(void *arg)
{
	while(1){
        if(submitFlag){

            char msg[60];
            userLink = userHead;
            while (userLink->next != NULL){
                userLink = userLink->next;
                if(userLink->isSelected){
                    userLink->isSelected = 0;   //清除用户选择
                    sprintf(msg,"===================================\n");
                    write(sock,msg,strlen(msg));
                    sprintf(msg,"===================================\n");
                    write(sock,msg,strlen(msg));
                    sprintf(msg,"用户 -- %d --已下单\n\n",userLink->userName);
                    write(sock,msg,strlen(msg));
                }
            }    
            foodLink = head;
            int sumMoney = 0;
            while (foodLink->next != NULL){
                foodLink = foodLink->next;
                if(foodLink->orderNum>0){
                    int foodNum = foodLink->orderNum;
                    int money = foodLink->money;
                    sumMoney = sumMoney + money * foodNum;
                    switch (foodLink->foodIdentify){
                        case 10:
                            sprintf(msg,"西红柿天鹅     %2d  %d\n",foodNum,money);
                            break;
                        case 11:
                            sprintf(msg,"血橙胡萝卜汁   %2d  %d\n",foodNum,money);
                            break;
                        case 12:
                            sprintf(msg,"冰糖阿胶燕窝   %2d  %d\n",foodNum,money);
                            break;
                        case 13:
                            sprintf(msg,"花胶牛奶冻     %2d  %d\n",foodNum,money);
                            break;
                        case 14:
                            sprintf(msg,"木瓜炖奶       %2d  %d\n",foodNum,money);
                            break;
                        case 15:
                            sprintf(msg,"银耳雪蛤羹     %2d  %d\n",foodNum,money);
                            break;
                        case 16:
                            sprintf(msg,"糟溜鱼片       %2d  %d\n",foodNum,money);
                            break;
                        case 17:
                            sprintf(msg,"日式香煎三文鱼 %2d  %d\n",foodNum,money);
                            break;
                        case 18:
                            sprintf(msg,"红焖带鱼       %2d  %d\n",foodNum,money);
                            break;
                        case 19:
                            sprintf(msg,"果仁菠菜       %2d  %d\n",foodNum,money);
                            break;
                        case 20:
                            sprintf(msg,"腐竹鱼头煲     %2d  %d\n",foodNum,money);
                            break;
                        case 21:
                            sprintf(msg,"红烧排骨       %2d  %d\n",foodNum,money);
                            break;
                        case 22:
                            sprintf(msg,"草莓牛奶布丁   %2d  %d\n",foodNum,money);
                            break;
                        case 23:
                            sprintf(msg,"孜然排骨       %2d  %d\n",foodNum,money);
                            break;
                        case 24:
                            sprintf(msg,"麻辣香锅       %2d  %d\n",foodNum,money);
                            break;			
                        default:
                            break;
                    }
                    write(sock,msg,strlen(msg));
                    foodLink->orderNum = 0;
                }
            }
            sprintf(msg,"\n总价格 --------------- %d 元\n",sumMoney);
            write(sock,msg,strlen(msg));
            sendFlag = 1;
            submitFlag = 0;
        }
    }
	
}

int startClient(void){

    pthread_t tid;   //定义线程号
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1){
        perror("socket");
    }
    struct sockaddr_in sockAddr;
    bzero(&sockAddr,sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;  //IPV4
    sockAddr.sin_port = htons(50000);   //PORT
    inet_pton(AF_INET,"192.168.1.1",&sockAddr.sin_addr);

    //connect server
    if(connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr))){
        perror("connect success");
    }else{
        perror("connect failed");
    }
    printf("connect success\n");

	pthread_create(&tid, NULL, startSendDitect, NULL);	//创建一个线程
	
	return 1;
}

#endif

