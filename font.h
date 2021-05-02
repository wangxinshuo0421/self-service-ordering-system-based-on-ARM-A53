#ifndef __FONT__
#define __FONT__


int   Init_Font(void);  //显示字体库前先调用本函数进行初始化
void  UnInit_Font(void); //程序退出前，调用本函数
int   Clean_Area(int X,  //x坐标起始点
                 int Y,  //y坐标起始点
				 int width, //绘制的宽度
				 int height,//绘制的高度
				 unsigned long color); //往屏幕指定区域填充颜色
				 
int   Display_characterX(unsigned int x,          //x坐标起始点
                         unsigned int y,          //y坐标起始点
						 unsigned char *string,   //GB2312 中文字符串
						 unsigned int color ,     //字体颜色值
						 int size);               //字体放大倍数 1~8


#endif