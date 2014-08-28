#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define CURU 72
#define CURD 80
#define CURL 75
#define CURR 77
#define ESC 27

void printWNL(int, int); //简单格式打印万年历
void printWNL2(int, int); //打印带表格的万年历
int Week(int,int,int); //求星期几
int getDays(int, int); //计算某个月的天数
int isRunNian(int); //判断是否闰年

/*
*主函数,应用程序入口
*/
void main()
{
 int year,month;
 struct tm t;
 char ch;

    time_t timer;
    struct tm *tblock;
    timer = time(NULL);
    tblock = localtime(&timer);

 t = *tblock; //标准函数, 获得系统当前时间
 year = t.tm_year + 1900; //得到当前年份
 month = t.tm_mon + 1; //得到当前月份
 do
 {
  system("cls"); //调用DOS清屏命令
  printWNL(year,month); //自定义函数, 打印万年历
  ch = getchar(); //获得无回显控制台输入字符

  if(ch == ESC) //ESC键，退出循环，结束程序
     break;
  else if(ch == 0) //若值为零，则用户敲了功能键，继续获取后续代码。
   ch = getchar(); 

  switch(ch)
  {
  case CURL: year--; break; //左键减年
  case CURR: year++; break; //右键加年
  case CURU:                //上键减月
   month--; 
   if(month == 0)
   {
    month = 12;
    year--;
   }
   break;
  case CURD:                //下键加月
   month++;
   if(month == 13)
   {
    month = 1;
    year++;
   }
   break;
  default:;
  }
 }while(1);

 printf("\n\n\t谢谢使用，欢迎常来！再见。\n");
}

/*
*简单格式打印万年历
*参数:   y 整型,接收年份值; m 整型,接收月份值;
*返回值: 无
*/
void printWNL(int y, int m)
{
 int i,j;
 int day = 1 - Week(y,m,1); //天数初始值，定位1号的位置
 int days = getDays(y,m);

 printf("\n\t╔═══════════════════════════╗");
 printf("\n\t╔══万年历查询═════════════刘大刚制作══╗\n");
 printf("\t║                      %4d 年 %2d 月                   ║\n",y,m);
 printf("\t╟------┬------┬------┬------┬------┬------┬------╢\n");
 printf("\t║  日  │  一  │  二  │  三  │  四  │  五  │  六  ║\n");

 for(i = 1; i <= 6; i++)
 {
 printf("\t╟------┼------┼------┼------┼------┼------┼------╢\n");
 printf("\t║");
  for(j = 1; j <= 7; j++)
  {
   if(day <= 0 || day > days)
    printf("      ");
   else
    printf("  %2d  ",day);
   j < 7 ? printf("│") : i < 6 ? printf("║") : printf("║");
   day++;
  }
  printf("\n");
 }
 printf("\t╚═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n");
 printf(" 提示：【←】减年  【→】加年  【↑】减月  【↓】加月  【ESC】退出\n");
}

/*
*求星期几
*参数:   y 整型,接收年份值; m 整型,接收月份值; d 整型,接收天的号数
*返回值: 整型, 是0,1-6七个数之间的一个数,0代表星期日,1-6代表星期一至星期六
*/
int Week(int y,int m,int d)
{
 int days = 0; //总天数
 int i;
 for(i = 1; i < y; i++) //累计1到y-1年的天数
  days += isRunNian(i) ? 366 : 365;
 for(i = 1; i < m; i++) //累计y年第1月到第m-1月的天数
  days += getDays(y,i);
 days += d; //累计当月的天数。

 return days % 7; //返回星期值
}

/*
*判断是否闰年
*参数:   y 整型, 接收年份值
*返回值: 整型, 只为0或1, 0代表假, 1代表真
*/
int isRunNian(int y)
{
 return (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) ? 1 : 0;
}

/*
*计算某个月的天数
*参数:   y 整型,接收年份值; m 整型,接收月份值;
*返回值: 整型, 是0, 28, 29, 30, 31之间的一个数
*注意:   返回值为0,表示你调用该函数时传递了不正确的年份值或月份值.
*/
int getDays(int y, int m)
{
 int days = 0;
 switch(m)
 {
 case 1:
 case 3:
 case 5:
 case 7:
 case 8:
 case 10:
 case 12:
  days = 31; break;
 case 4:
 case 6:
 case 9:
 case 11:
  days = 30; break;
 case 2:
  days = isRunNian(y) ? 29 : 28; break;
 default:;
 }
 return days;
}

