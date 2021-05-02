#ifndef __TOUCHSCREEN__
#define __TOUCHSCREEN__
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "MyLib.h"



void *start_routine(void *arg)
{
	while(1){
        read(touchFilePoint,&touchEvent,sizeof(touchEvent));
	}
	
}

int startTouchScreen(void){

    pthread_t tid;   //定义线程号

    //打开屏幕触摸文件
    touchFilePoint = open(touchFile, O_RDONLY);
    if(touchFilePoint == -1){
        perror("open touchFile failed:");
        return -1;
    }
	
	pthread_create(&tid, NULL, start_routine, NULL);	//创建一个线程
	
	
	return 1;
}

#endif
