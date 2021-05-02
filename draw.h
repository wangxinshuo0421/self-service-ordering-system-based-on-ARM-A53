#ifndef __DRAW__
#define __DRAW__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "MyLib.h"

#define logInBmp "picture/logInPicture.bmp"


//x坐标起始点; y坐标起始点; 图片名称
int displayBmpPicture( unsigned int x, unsigned int y, const char pictureName[]){
    int bmpPoint, bmpReadRet, bmpBit;
    unsigned int  bmpReadLength, bmpReadWidth,bmpLine;
    int lcdFilePoint,i,j;   //lcd文件变量
    unsigned char bmpBuf[LCDSizeof] = {0}, ch = 0x00;
    int *mapPoint;      //内存映射指针

    lcdFilePoint = open( LCD, O_RDWR ); //读lcd
    bmpPoint = open(pictureName,O_RDONLY);  //读BMP文件
    if( lcdFilePoint == -1 || bmpPoint == -1 ){
        printf("open file failed; lcd:%d; bmp:%d; %s",lcdFilePoint,bmpPoint,pictureName);
        return -1;
    }

    bmpReadRet = read(bmpPoint,bmpBuf,LCDSizeof);
    if(bmpReadRet > LCDSizeof){
        perror("bmp oversize lcd screen");
        return -2;
    }else if(bmpReadRet == -1){
        perror("read bmp file failed");
        return -3;
    }
    bmpReadWidth = bmpBuf[22] | bmpBuf[23]<<8 | bmpBuf[24]<<16 | bmpBuf[25]<<24;
    bmpReadLength = bmpBuf[18] | bmpBuf[19]<<8 | bmpBuf[20]<<16 | bmpBuf[21]<<24;;
    printf("picture: %s len = %d;   width = %d\n",pictureName,bmpReadLength,bmpReadWidth);
    close(bmpPoint);

    //显存映射
    mapPoint = mmap( NULL, LCDSizeof, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFilePoint, 0 );
    if( mapPoint == NULL ){    //判断映射是否成功
        perror("mmap lcd failed");
        return -4;
    }
  
    bmpPoint = open( pictureName, O_RDONLY );  //读bmp
    bzero(bmpBuf,sizeof(bmpBuf));     //清空数组
    lseek(bmpPoint, 54, SEEK_SET);
    bmpReadRet = read(bmpPoint,bmpBuf,LCDSizeof);
    printf("bmpReadRet = %d\n",bmpReadRet);
    if(bmpReadRet == -1){
        perror("read file failed\n");
        return -3;
    }

    bmpLine = bmpReadWidth-1;
    for(i = y; i < y+bmpReadWidth; i++,bmpLine--){
        for(j = x; j < x+bmpReadLength; j++){
            if(i<LCDWidth && j<LCDLength){
                bmpBit = bmpBuf[((bmpLine*bmpReadLength+j-x)*3)]|bmpBuf[((bmpLine*bmpReadLength+j-x)*3)+1]<<8|bmpBuf[((bmpLine*bmpReadLength+j-x)*3)+2]<<16|ch<<24;
                memcpy( mapPoint + (i*LCDLength + j), &bmpBit, 4); //内存拷贝
            }
        }
    }

    close(lcdFilePoint);
    close(bmpPoint);
    munmap(mmap,LCDSizeof);

    return 1;   //运行成功
}
int displayColorBlock(unsigned int x, unsigned int y, unsigned int xLen, unsigned int yLen, unsigned int color){   //x,y为起点,xLen,yLen为终点的颜色块
    int lcdFilePoint,i,j;   //lcd文件变量
    unsigned char ch = 0x00;
    int *mapPoint;      //内存映射指针

    lcdFilePoint = open( LCD, O_RDWR ); //读lcd
    
    if( lcdFilePoint == -1 ){
        perror("open lcd file failed");
        return -1;
    }

   //显存映射
    mapPoint = mmap( NULL, LCDSizeof, PROT_READ | PROT_WRITE, MAP_SHARED, lcdFilePoint, 0 );
    if( mapPoint == NULL ){    //判断映射是否成功
        perror("mmap lcd failed");
        return -4;
    }

    for(i = y; i < yLen; i++){
        for(j = x; j < xLen; j++){
            if(i<LCDWidth && j<LCDLength){
                memcpy( mapPoint + (i*LCDLength + j), &color, 4); //内存拷贝
            }
        }
    }

    close(lcdFilePoint);
    munmap(mmap,LCDSizeof);

    return 1;   //运行成功
}
#endif