#ifndef __LISTFRESH__
#define __LISTFRESH__

#include "font.h"
#include <stdio.h>
#include <string.h>

//listPosition = -1 ���Ʊ��

void FreshList(int foodId,int foodNum,int color,int listPosition,int money){
	char buf[30];
	switch (foodId){
		case 10:
			sprintf(buf,"���������     %2d  %d",foodNum,money);
			break;
		case 11:
			sprintf(buf,"Ѫ�Ⱥ��ܲ�֭   %2d  %d",foodNum,money);
			break;
		case 12:
			sprintf(buf,"���ǰ�������   %2d  %d",foodNum,money);
			break;
		case 13:
			sprintf(buf,"����ţ�̶�     %2d  %d",foodNum,money);
			break;
		case 14:
			sprintf(buf,"ľ������       %2d  %d",foodNum,money);
			break;
		case 15:
			sprintf(buf,"����ѩ���     %2d  %d",foodNum,money);
			break;
		case 16:
			sprintf(buf,"������Ƭ       %2d  %d",foodNum,money);
			break;
		case 17:
			sprintf(buf,"��ʽ��������� %2d  %d",foodNum,money);
			break;
		case 18:
			sprintf(buf,"���˴���       %2d  %d",foodNum,money);
			break;
		case 19:
			sprintf(buf,"���ʲ���       %2d  %d",foodNum,money);
			break;
		case 20:
			sprintf(buf,"������ͷ��     %2d  %d",foodNum,money);
			break;
		case 21:
			sprintf(buf,"�����Ź�       %2d  %d",foodNum,money);
			break;
		case 22:
			sprintf(buf,"��ݮţ�̲���   %2d  %d",foodNum,money);
			break;
		case 23:
			sprintf(buf,"��Ȼ�Ź�       %2d  %d",foodNum,money);
			break;
		case 24:
			sprintf(buf,"�������       %2d  %d",foodNum,money);
			break;			
		default:
			break;
	}
	if(listPosition == -1){//���Ʊ��
		Display_characterX(0,60,"��Ʒ          ���� ����",black,1);
		sprintf(buf,"�ܼ�:           %3dԪ",money);
	    Display_characterX(0,395,buf,black,1);
	}else{
		Display_characterX(0,listPosition*30+80,buf,black,1);
	}

}

#endif
