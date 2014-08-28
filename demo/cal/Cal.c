#include <stdio.h>
#include <string.h>
#include "mybase.h"
#include "mylunar.h"

#define MINLUNARYEAR 1900
#define MAXLUNARYEAR 8704

#define CLOSETYPE APP_PROMPT|APP_CHINESE

int ShowDiyCfgFile()
{
	printf("\n--------------------------以下为自定义节日文件DiyHoliday.cfg的模版内容--------------------------\n\n");
	printf("#\t公历、农历历自定义节日或纪念日配置文件\n");
	printf("#\tGregorian Diy Holiday和Lunar Diy Holiday两行是区别公历和农历的关键行，不要修改，更不能删\n");
	printf("#\t使用#字符可以注释掉一行\n");
	printf("#\t公历和农历的自定义节日个数均不能超过30个，超过30个的将无效\n");
	printf("#\t格式均为：MMDD--名称\n");
	printf("#\tMMDD表示四位的月日，名称是您想要在日历中显示的名称，名称不能超过8个汉字或16个字符\n");
	printf("#\t日期和名称中间的两个短线是必须要有的\n");
	printf("#\t不符合以上格式的自定义均视为无效\n");
	printf("\n\n\n");
	printf("#\tGregorian Diy Holiday begin --This line connot modify or delete.\n");
	printf("0808--奥运纪念日\n");
	printf("\n\n\n\n");
	printf("#\tLunar Diy Holiday begin --This line connot modify or delete.\n");
	printf("1219--我的生日\n\n");
	return 0;
}

int Help()
{
	printf("农历日历【1901年--8704年】、农历公历转换、生辰八字查询\n\n");
	printf("CAL [-L] [-G] [-B[:L/G]] [-DIY] [年[月[日]]]\n\n");
	printf("\t-L\t将公历日期转换为对应的农历日期，输入八位公历日期如：YYYYMMDD.\n");
	printf("\t-G\t将农历日期转换为对应的公历日期，输入的农历日期格式：YYYYMMDD或YYYYRMMDD R表示闰月.\n");
	printf("\t-B\t查询生辰八字，默认公历出生日期，格式为YYYYMMDDHH或YYYYRMMDDHH  HH取00-23.\n");
	printf("\t\t:G  公历出生日期，格式必须是YYYYMMDDHH.\n");
	printf("\t\t:L  农历出生日期，使用R可以表示闰月.\n");
	printf("\t-DIY\t查看自定义节日、纪念日配置文件模版.\n\n");
	printf("不使用任何操作符时，将默认显示输入日期的详细信息.\n");
	printf("如:CAL 2012、CAL 201208、CAL 20120818 将分别显示2012整年、2012年8月、2012年8月18日的日历信息.\n");
	printf("如果需要自定义节日，可以在EXE目录下添加文件DiyHoliday.cfg文件，键入CAL -DIY可以查看该文件的格式.\n");
	printf("该日历理论上可以计算1901年--8704年的信息，但年份越大误差也会越大，2300年之前误差还是蛮小的.\n");
	
}
int PrfBirBZ(char *date)
{
	int i=0,len=0,hour=0;
	char ganzhi[40];
	char wuxing[40];
	char nayin[40];
	char zhuming[10];
	char que[15];
	
	memset(ganzhi,0x00,sizeof(ganzhi));
	memset(wuxing,0x00,sizeof(wuxing));
	memset(nayin,0x00,sizeof(nayin));
	memset(zhuming,0x00,sizeof(zhuming));
	memset(que,0x00,sizeof(que));
	
	len=strlen(date);
	hour=atoi(SubString(date,len-2,2));
	if((hour>23)||(hour<0))
	{
		printf("出生时辰不合法，只能在0-23之间！\n");
		printf("键入CAL -help 可查看帮助！\n");
		AppExit(CLOSETYPE);
	}
	strcpy(ganzhi,Get_ZB_BaZi(date));
	strcpy(wuxing,Get_ZB_WuXing(ganzhi));
	strcpy(nayin,Get_ZB_NaYin(ganzhi));
	strcpy(zhuming,SubString(wuxing,10,2));
	strcpy(que,"");
	if(strcon(wuxing,"金")!=0)
	{
		strcat(que,"金");
	}
	if(strcon(wuxing,"木")!=0)
	{
		strcat(que,"木");
	}
	if(strcon(wuxing,"水")!=0)
	{
		strcat(que,"水");
	}
	if(strcon(wuxing,"火")!=0)
	{
		strcat(que,"火");
	}
	if(strcon(wuxing,"土")!=0)
	{
		strcat(que,"土");
	}
	printf("西元日期：%s\n农历日期：%s\n",SubString(date,0,8),ConvertGL_Info(SubString(date,0,8),"-l"));
	strrep(ganzhi," ","   ");
	strrep(wuxing," ","   ");
	printf("八字：%s\n五行：%s\n纳音：%s\n",ganzhi,wuxing,nayin);
	printf("主命为%s命",zhuming);
	len=strlen(que);
	if(len==0)
	{
		printf("\n");
	}
	else if(len==2)
	{
		printf("，五行缺%s\n",que);
	}
	else if(len==4)
	{
		printf("，五行缺%s、%s\n",SubString(que,0,2),SubString(que,2,2));
	}
	else if(len==6)
	{
		printf("，五行缺%s、%s、%s\n",SubString(que,0,2),SubString(que,2,2),SubString(que,4,2));
	}
	else if(len==8)
	{
		printf("，五行缺%s、%s、%s、%s\n",SubString(que,0,2),SubString(que,2,2),SubString(que,4,2),SubString(que,6,2));
	}
	else if(len==10)
	{
		printf("，五行缺%s、%s、%s、%s、%s\n",SubString(que,0,2),SubString(que,2,2),SubString(que,4,2),SubString(que,6,2),SubString(que,8,2));
	}
	return 0;
}
int main(int argc,char *argv[])
{
	int year=0,len=0,month=0,i=0;
	char date[20];
	char oprs[20];
	char syear[5];
	char smonth[3];
	char tmpdate[15];
	char c;
	memset(date,0x00,sizeof(date));
	memset(syear,0x00,sizeof(syear));
	memset(smonth,0x00,sizeof(smonth));
	if(argc==1)
	{
		Help();
		AppExit(CLOSETYPE);
	}
	if(argc==2)
	{
		if((strcasecmp(argv[1],"-h")==0)||(strcasecmp(argv[1],"-help")==0)||(strcasecmp(argv[1],"-?")==0)||(strcasecmp(argv[1],"/?")==0)||(strcasecmp(argv[1],"/h")==0)||(strcasecmp(argv[1],"/help")==0)||(strcasecmp(argv[1],"?")==0))
		{
			Help();
			AppExit(CLOSETYPE);
		}
		if(strcasecmp(argv[1],"-DIY")==0)
		{
			ShowDiyCfgFile();
			AppExit(CLOSETYPE);
		}
		strcpy(date,argv[1]);
		len=strlen(date);
		/*日期的合法性检查*/
		if(isdigitstr(date)!=0)
		{
			printf("日期不能包含非数字字符！\n");
			printf("键入CAL -help 可查看帮助！\n");
			AppExit(CLOSETYPE);
		}
		
		if(len==8)
		{
			if(isdate(date)!=0)
			{
				printf("公历日期不合法！\n");
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("只能查看%d年到%d年的日历信息！\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			PrfOneDay(date,"-g");
		}
		else if(len==6)
		{
			strcpy(syear,SubString(date,0,4));
			strcpy(smonth,SubString(date,4,2));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("只能查看%d年到%d年的日历信息！\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			month=atoi(smonth);
			if((month>12)||(month<=0))
			{
				printf("月份必须在1-12之间！\n");
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			InitLunarCal(year);
			PrfCalendar(month);
			printf("\n如果显示格式不正常，请使用命令\"%s %s >cal.txt\" 将结果打印到cal.txt文件中查看，文件名可随意替换。\n",argv[0],argv[1]);
		}
		else if(len==4)
		{
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("只能查看%d年到%d年的日历信息！\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			InitLunarCal(year);
			PrfCalendar(year);
			printf("\n如果显示格式不正常，请使用命令\"%s %s >cal.txt\" 将结果打印到cal.txt文件中查看，文件名可随意替换。\n",argv[0],argv[1]);
		}
		else
		{
			printf("日期长度不正确！\n");
			printf("键入CAL -help 可查看帮助！\n");
			AppExit(CLOSETYPE);
		}
	}
	if(argc==3)
	{
		memset(oprs,0x00,sizeof(oprs));
		strcpy(oprs,argv[1]);
		if(strcasecmp(oprs,"-l")==0)
		{
			if(isdate(argv[2])!=0)
			{
				printf("公历日期不合法！\n");
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			memset(date,0x00,sizeof(date));
			strcpy(date,argv[2]);
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("只能查看%d年到%d年的日历信息！\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			PrfOneDay(date,"-g");
		}
		else if(strcasecmp(oprs,"-g")==0)
		{
			if(islunardate(argv[2])!=0)
			{
				printf("农历日期格式不合法，只能为YYYYMMDD或YYYYRMMDD！\n");
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			memset(date,0x00,sizeof(date));
			strcpy(date,argv[2]);
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("只能查看%d年到%d年的日历信息！\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
			PrfOneDay(date,"-l");
		}
		else if(strcasecon(oprs,"-B")==0)
		{
			if((strcasecmp(oprs,"-B")==0)||(strcasecmp(oprs,"-B:G")==0))
			{
				memset(date,0x00,sizeof(date));
				strcpy(date,argv[2]);
				len=strlen(date);
				if(len!=10)
				{
					printf("公历查询八字时，出生日期必须为10位--YYYYMMDDHH！\n");
					printf("键入CAL -help 可查看帮助！\n");
					AppExit(CLOSETYPE);
				}
				if(isdigitstr(date)!=0)
				{
					printf("公历查询八字时，出生日期不能含有非数字字符！\n");
					printf("键入CAL -help 可查看帮助！\n");
					AppExit(CLOSETYPE);
				}
				if(isdate(SubString(date,0,8))!=0)
				{
					printf("公历出生日期不合法！\n");
					printf("键入CAL -help 可查看帮助！\n");
					AppExit(CLOSETYPE);
				}
				PrfBirBZ(date);
			}
			else if(strcasecmp(oprs,"-B:L")==0)
			{
				memset(date,0x00,sizeof(date));
				strcpy(date,argv[2]);
				len=strlen(date);
				if((len!=10)&&(len!=11))
				{
					printf("农历查询八字时，出生日期只能是10位--YYYYMMDDHH 或11位--YYYYRMMDDHH！\n");
					printf("键入CAL -help 可查看帮助！\n");
					AppExit(CLOSETYPE);
				}
				if(len==10)
				{
					if(isdigitstr(date)!=0)
					{
						printf("不是闰月时，出生日期不能含有非数字字符！\n");
						printf("键入CAL -help 可查看帮助！\n");
						AppExit(CLOSETYPE);
					}
					if(islunardate(SubString(date,0,8))!=0)
					{
						printf("农历出生日期不合法！\n");
						printf("键入CAL -help 可查看帮助！\n");
						AppExit(CLOSETYPE);
					}
				}
				if(len==11)
				{
					if(islunardate(SubString(date,0,9))!=0)
					{
						printf("农历出生日期不合法！\n");
						printf("键入CAL -help 可查看帮助！\n");
						AppExit(CLOSETYPE);
					}
				}
				memset(tmpdate,0x00,sizeof(tmpdate));
				strcpy(tmpdate,ConvertGL(SubString(date,0,len-2),"-g"));
				strcat(tmpdate,SubString(date,len-2,2));
				PrfBirBZ(tmpdate);
			}
			else
			{
				printf("无此参数模式！\n");
				printf("键入CAL -help 可查看帮助！\n");
				AppExit(CLOSETYPE);
			}
		}
		else
		{
			printf("无此参数模式！\n");
			printf("键入CAL -help 可查看帮助！\n");
			AppExit(CLOSETYPE);
		}
	}
	AppExit(CLOSETYPE);
}
