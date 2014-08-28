/*
 *    ProgramName      : Base.c
 *
 *    Version          : 2.0
 *
 *    OS & Environment : Windows NT, ANSI C, MinGW Compiler
 *
 *    Description      : Base Function Libaray
 *
 *    History          : Create in 201110 with some Date or CharStr And WriteLog Function Begin
 *
 *	Date		Position			Author		Description		Address
 * -----------------------------------------------------------------------------------------------------
 *	2011.11.24	Date/Writelog			Chen Yunlong	Creation		BeiJing
 *	2012.03		Str Function Like SubString	Chen Yunlong	Add			BeiJing
 *	2012.04		Str Function			Chen Yunlong	Modify			BeiJing
 *	2012.04		GetEnv				Chen Yunlong	Add			BeiJing
 *	2012.07.07	Lunar Functions			Chen Yunlong	Add			SuZhou
 *	2012.07.07	GetAnyWeek			Chen Yunlong	Modify			SuZhou
 *	2012.07.07	GetDayChaFromBase		Chen Yunlong	Modify			SuZhou
 *	2012.07.09	GetRandStr			Chen Yunlong	Add			SuZhou
 *	2012.07.14	AddReg				Chen Yunlong	Add			SuZhou
 *	2012.07.15	RemoveDir			Chen Yunlong	Add			SuZhou
 *	2012.08.01	str(case)con			Chen Yunlong	Add			SuZhou
 *	2012.08.01	str(case)rep			Chen Yunlong	Modify			SuZhou
 *	2012.08.01	CopyDir				Chen Yunlong	Add			SuZhou
 *	2012.08.05	CopyDirList			Chen Yunlong	Modify			SuZhou
 *	2012.08.06	AppExit				Chen Yunlong	Add			SuZhou
 *	2012.08.06	DelAppSelf			Chen Yunlong	Add			SuZhou
 *	2012.08.07	CopyFile(Dir)			Chen Yunlong	Modify			SuZhou
 *	2012.08.07	DelFile(Dir)			Chen Yunlong	Modify			SuZhou
 *	2012.08.13	mtrim				Chen Yunlong	Modify			SuZhou
 *	2012.08.18	gdb(GDB)			Chen Yunlong	Add			SuZhou
 *
*/







#include <stdio.h>
#include <wTypes.h>
#include <Winsock2.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <windows.h>
#include <io.h>
#include <ctype.h>
#include <Math.h>
#include <time.h>
#include <dirent.h>
#include <process.h>
#include <winbase.h>
#include <wincon.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <shlobj.h>





/*宏定义部分--BEGIN*/


/*最大调试数量*/
#define MAXGDBCOUNT 200

/*调试函数用到的通用参数*/
#define GDB __FILE__,__FUNCTION__,__LINE__

/* 当前EXE文件的绝对路径（包含文件名） */
#define __EXE__ _pgmptr

/* Get Html Return Bufsize*/
#define MYBUFSIZ 1024

/*WriteLog Source File And Line NUM*/
#define LOGLVL __FILE__,__LINE__

/*缓冲池最大个数*/
#define LOG_MAXBUFFNUM 200

/*单个缓冲池长度*/
#define LOG_MANBUFFLEN 30960

/* 程序退出模式定义 */
#define APP_PROMPT 0x01
#define APP_WINDOWS 0x02
#define APP_CHINESE 0x04

/* 创建文件夹时，路径的最大深度 */
#define MAX_DIRDEEP 100

/*宏定义部分--END*/





/*全局变量部分--BEGIN*/


/* 是否强制处理*/
/* 复制文件时：是否重写，0-提示 1-直接覆盖*/
/* 删除文件时：是否提示，0-提示 1-直接删除*/
int FORCEDEAL=0;

/* 复制/删除文件时，是否显示详细信息 */
/* 0-不显示，1-printf控制台显示 2-Writelog写入文件 3-两者都处理*/
int SHOWDEALINFO=0;

/*ETC File*/
char CONFIG_NAME[MAX_PATH]="\%MOONHOME\%\\Etc\\MoonTalk.cfg";

/*日志文件名*/
char LOG_FILE[MAX_PATH]="";

/*日志数据缓冲池*/
char LOG_BUFF[LOG_MAXBUFFNUM][LOG_MANBUFFLEN];

/*当前缓冲池个数*/
int LOG_BUFFNOWNUM=0;

/*日志开关 0-关 其他-开 默认开*/
int LOG_BUTTON=1;

/* WeekDay中英文标志 chinese or english */
char WEEK_LANG_TYPE[10]="chinese";

/* 程序开始时间 是根据CpyLogFile函数记录的 */
DWORD APPTIMESTART=0;

/*存储调试信息的结构体*/
struct TEST_GDB
{
	char func[50];
	int linenum;
	int count;
} test_gdb[MAXGDBCOUNT];

/*当前调试的COUNT*/
int NOWGDBCOUNT=0;

/*全局变量部分--END*/



/* 函数预定义部分--BEGIN */
int WriteLog(char *zhufile,int lnum,char *fmt,...);
int LogFlush();
/* 函数预定义部分--END */






/*程序通用部分--BEGIN*/



/*Add in 20120818*/
/*程序调试函数，只需要传入宏定义参数GDB即可*/
int gdb(const char *codefile,const char *func,int linenum)
{
	int i=0,findflag=0;
	if(NOWGDBCOUNT==0)
	{
		memset(&test_gdb,0x00,sizeof(struct TEST_GDB)*MAXGDBCOUNT);
		printf("I'm here!--> [%-50s][%-25s][%05d][%09d]\n",codefile,func,linenum,1);
		WriteLog(LOGLVL,"I'm here!--> [%-50s][%-25s][%05d][%09d]",codefile,func,linenum,1);
		strcpy(test_gdb[NOWGDBCOUNT].func,func);
		test_gdb[NOWGDBCOUNT].linenum=linenum;
		test_gdb[NOWGDBCOUNT].count=1;
		NOWGDBCOUNT++;
	}
	else
	{
		findflag=0;
		for(i=0;i<NOWGDBCOUNT;i++)
		{
			if((strcmp(test_gdb[i].func,func)==0)&&(test_gdb[i].linenum==linenum))
			{
				findflag=1;
				test_gdb[i].count++;
				printf("I'm here!--> [%-50s][%-25s][%05d][%09d]\n",codefile,func,linenum,test_gdb[i].count);
				WriteLog(LOGLVL,"I'm here!--> [%-50s][%-25s][%05d][%09d]",codefile,func,linenum,test_gdb[i].count);
				break;
			}
		}
		if(findflag==0)
		{
			printf("I'm here!--> [%-50s][%-25s][%05d][%09d]\n",codefile,func,linenum,1);
			WriteLog(LOGLVL,"I'm here!--> [%-50s][%-25s][%05d][%09d]",codefile,func,linenum,1);
			strcpy(test_gdb[NOWGDBCOUNT].func,func);
			test_gdb[NOWGDBCOUNT].linenum=linenum;
			test_gdb[NOWGDBCOUNT].count=1;
			NOWGDBCOUNT++;
		}
	}
	LogFlush();
	return 0;
}


/* Application Exit */
/* 参数为退出模式 APP_PROMPT|APP_WINDOWS|APP_CHINESE */
/* APP_PROMPT 退出前提示 */
/* APP_WINDOWS MESSAGEBOX方式提示，默认为控制台提示 */
/* APP_CHINESE 中文提示，默认为英文 */
/* 0-直接退出 1-默认控制台英文提示 */
/* 3-窗体英文提示 5-控制台中文提示 7-窗体中文提示 */
int AppExit(DWORD dwType)
{
	int i=0,len=0,tmpx=0,exittpye=0,langdis=0;
	char sxtype[20];
	char stype[30];
	char tmptype[5];
	DWORD dwConsum=0,dwEnd=0;
	memset(sxtype,0x00,sizeof(sxtype));
	memset(stype,0x00,sizeof(stype));
	if(APPTIMESTART!=0)
	{
		dwEnd=GetTickCount();
		dwConsum=dwEnd-APPTIMESTART;
		WriteLog(LOGLVL,"Time Consuming [%d] milliseconds.",dwConsum);
	}
	LogFlush();
	sprintf(sxtype,"%x",dwType);
	len=strlen(sxtype);
	strcpy(stype,"0000");
	for(i=0;i<len;i++)
	{
		if(sxtype[i]=='0')
		{
			strcat(stype,"0000");
		}
		else if(sxtype[i]=='1')
		{
			strcat(stype,"0001");
		}
		else if(sxtype[i]=='2')
		{
			strcat(stype,"0010");
		}
		else if(sxtype[i]=='3')
		{
			strcat(stype,"0011");
		}
		else if(sxtype[i]=='4')
		{
			strcat(stype,"0100");
		}
		else if(sxtype[i]=='5')
		{
			strcat(stype,"0101");
		}
		else if(sxtype[i]=='6')
		{
			strcat(stype,"0110");
		}
		else if(sxtype[i]=='7')
		{
			strcat(stype,"0111");
		}
		else if(sxtype[i]=='8')
		{
			strcat(stype,"1000");
		}
		else if(sxtype[i]=='9')
		{
			strcat(stype,"1001");
		}
		else if((sxtype[i]=='A')||(sxtype[i]=='a'))
		{
			strcat(stype,"1010");
		}
		else if((sxtype[i]=='B'||(sxtype[i]=='b')))
		{
			strcat(stype,"1011");
		}
		else if((sxtype[i]=='C')||(sxtype[i]=='c'))
		{
			strcat(stype,"1100");
		}
		else if((sxtype[i]=='D')||(sxtype[i]=='d'))
		{
			strcat(stype,"1101");
		}
		else if((sxtype[i]=='E')||(sxtype[i]=='e'))
		{
			strcat(stype,"1110");
		}
		else if((sxtype[i]=='F')||(sxtype[i]=='f'))
		{
			strcat(stype,"1111");
		}
	}
	len=strlen(stype);
	if(stype[len-1]=='1')
	{
		if(stype[len-3]=='0')
		{
			langdis=0;
		}
		else if(stype[len-3]=='1')
		{
			langdis=1;
		}
		if(stype[len-2]=='0')
		{
			if(langdis==0)
			{
				printf("\nPress any key to exit...");
				getch();
			}
			else if(langdis==1)
			{
				printf("\n按任意键将退出程序...");
				getch();
			}
		}
		else if(stype[len-2]=='1')
		{
			if(langdis==0)
			{
				MessageBox(NULL,"Application will exit","Exit",MB_OK|MB_ICONINFORMATION);
			}
			else if(langdis==1)
			{
				MessageBox(NULL,"点击OK按钮退出应用程序","退出",MB_OK|MB_ICONINFORMATION);
			}
		}
	}
	exit(0);
}


/*程序通用部分--END*/







/*第一部分--BEGIN*/
/*字符串处理函数相关*/




/*判断字符是不是属于汉字*/
/*0--汉字 非零--不是汉字*/
int IsChinese(char c)
{
	if(~(c >> 8) == 0)
	{
		return 0;
	}
	return -1;
}

/*将数字0-9转换为汉字零-九*/
/*Add in 20120705 从农历库中拉过来的*/
char *GetHanZi(int n)
{
	static char result[3];
	memset(result,0x00,sizeof(result));
	switch (n)
	{
		case 0:strcpy(result,"零");break;
		case 1:strcpy(result,"一");break;
		case 2:strcpy(result,"二");break;
		case 3:strcpy(result,"三");break;
		case 4:strcpy(result,"四");break;
		case 5:strcpy(result,"五");break;
		case 6:strcpy(result,"六");break;
		case 7:strcpy(result,"七");break;
		case 8:strcpy(result,"八");break;
		case 9:strcpy(result,"九");break;
		default:strcpy(result,"");break;
	};
	return result;
}

/*判断一个字符串是不是数字串*/
/*0--是数字串  其他--不是数字串*/
int isdigitstr(char *str)
{
	int i=0,len=0,flag=0;
	len=strlen(str);
	if(len<=0)
		return -1;
	for(i=0;i<len;i++)
	{
		if(isdigit(str[i])==0)
			flag=1;
	}
	if(flag!=0)
		return -1;
	return 0;
}

/*去掉字符串右边的空格*/
char *rtrim(char* str)
{
	char *s=str;
	while(*s)
		++s;
	--s;
	while(s>=str)
		if(*s==0x20)
			--s;
		else
			break;
	*(s+1)=0;
	return (str);
}

/*去掉字符串左边的空格*/
char * ltrim(char* str)
{
	char *s=str;
	while(*s)
		if(isspace(*s))
			++s;
		else
			break;
	if (s>str)
		strcpy(str,s);
	return (str);
}

/*去掉字符串两端的空格*/
char *  trim(char *str)
{
	ltrim(str);
	rtrim(str);
	return(str);
}

/*Add in 201204*/
/*检索字符串str中第一个出现char c的位置，返回数组下标，没有返回-1 */
int Indexof(char *str,char c)
{
	int result=-1,len=0,i=0;
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]==c)
		{
			result=i;
			break;
		}
	}
	return result;
}

/*Add in 20120801*/
/*检索字符串str中最后一个个出现char c的位置，返回数组下标，没有返回-1 */
int LastIndexof(char *str,char c)
{
	int result=-1,len=0,i=0;
	len=strlen(str);
	for(i=len-1;i>=0;i--)
	{
		if(str[i]==c)
		{
			result=i;
			break;
		}
	}
	return result;
}

/* Modify in 20120801 return \0 if null */
/* 此函数没有任何问题 */
/* 效仿C# SubString 这个东西百试不爽 */
/* 字符串截取，返回值为截取的部分，str不变，i为开始位置下标，n为截取长度 */
char *SubString(char *str,int i,int n)
{
	int len=0,k=0,g=0;
	char *p;
	len=strlen(str);
	p=(char *)malloc(sizeof(char)*(n+1));
	if ((i<0)||(n<=0)||(len==0)||(i>=len))
	{
		strcpy(p,"\0");
		return p;
	}
	for(k=i;((k<len)&&(g<n));k++)
	{
		p[g++]=str[k];
	}
	p[g]='\0';
	return p;
}

/* add in 20120801 由原来的StrContain改，相当于StrContain(str1,str2,"matchcase") */
/* 区分大小写*/
/* 确认str1是否包含str2。返回为-1说明不存在，返回0为存在  */
int strcon(char *str1,char *str2)
{
	char *p;
	p=NULL;
	p=strstr(str1,str2);
	if(p!=NULL)
		return 0;
	return -1;
}

/* add in 20120801 由原来的StrContain改，相当于StrContain(str1,str2,"-i") */
/* 不区分大小写*/
/* 确认str1是否包含str2。返回为-1说明不存在，返回0为存在  */
int strcasecon(char *str1,char *str2)
{
	int i=0,len1=0,len2=0;
	char *source,*seach,*s1,*s2,*p;
	
	len1=strlen(str1);
	len2=strlen(str2);
	if((len1<=0)||(len2<=0)||(len2>len1))
		return -1;
	
	source=(char *)malloc(sizeof(char)*(len1+1));
	seach=(char *)malloc(sizeof(char)*(len2+1));
	s1=source;
	s2=seach;
	for(i=0;i<len1;i++)
	{
		*source=str1[i];
		*source++;
	}
	*source='\0';
	for(i=0;i<len2;i++)
	{
		*seach=str2[i];
		*seach++;
	}
	*seach='\0';
	strlwr(s1);
	strlwr(s2);
	p=NULL;
	p=strstr(s1,s2);
	if(p!=NULL)
		return 0;
	return -1;
}

/* Add in 20120801 */
/* 区分大小写*/
/* 替换字符串source中str1为str2，全部替换*/
/* 不能循环替换，比如is--this 替换为this 之后的is不再替换*/
/* 当str2为空时，即去掉str1*/
char *strrep(char *source,char *str1,char *str2)
{
	int len=0,len1=0,len2=0,k=0,i=0,j=0,g=0,flag=0;
	len=strlen(source);
	len1=strlen(str1);
	len2=strlen(str2);
	if((len<=0)||(len1<=0)||(len1>len))
		return source;
	
	while(1)
	{
		len=strlen(source);
		if(i==len)
			break;
		if((i+len1)>len)
			break;
		if(source[i]==str1[0])
		{
			flag=0;
			k=0;
			for(j=i;((j<len)&&(k<len1));j++)
			{
				if(source[j]!=str1[k++])
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				k=i;
				g=k+len1;
				sprintf(source,"%s%s%s",SubString(source,0,k),str2,SubString(source,g,len-g));
				i=i+len2;
				continue;
			}
		}
		i++;
	}	
	return source;
}

/* Add in 20120801 */
/* 不区分大小写*/
/* 替换字符串source中str1为str2，全部替换*/
/* 不能循环替换，比如is--this 替换为this 之后的is不再替换*/
/* 当str2为空时，即去掉str1*/
char *strcaserep(char *source,char *str1,char *str2)
{
	int len=0,len1=0,len2=0,k=0,i=0,j=0,g=0,cn=0,flag=0;
	len=strlen(source);
	len1=strlen(str1);
	len2=strlen(str2);
	if((len<=0)||(len1<=0)||(len1>len))
		return source;
	
	while(1)
	{
		len=strlen(source);
		if(i==len)
			break;
		if((i+len1)>len)
			break;
		cn=(int)source[i]-(int)str1[0];
		if((cn==0)||(((cn==-32)&&(isalpha(source[i])!=0)&&(isalpha(str1[0])!=0)))||(((cn==32)&&(isalpha(source[i])!=0)&&(isalpha(str1[0])!=0))))
		{
			flag=0;
			k=0;
			for(j=i;((j<len)&&(k<len1));j++)
			{
				cn=(int)source[j]-(int)str1[k++];
				if(!((cn==0)||(((cn==-32)&&(isalpha(source[j])!=0)&&(isalpha(str1[k-1])!=0)))||(((cn==32)&&(isalpha(source[j])!=0)&&(isalpha(str1[k-1])!=0)))))
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				k=i;
				g=k+len1;
				sprintf(source,"%s%s%s",SubString(source,0,k),str2,SubString(source,g,len-g));
				i=i+len2;
				continue;
			}
		}
		i++;
	}	
	return source;
}

/* 分割字符串 */
/* 参数一：源字符串 */
/* 参数二：前面的部分 */
/* 参数三：后面的部分 */
/* 参数四：分割符 char类型 */
/* 参数五：第几个分隔符 负数表示从后开始 */
int strdiv(char *source,char *res1,char *res2,char c,int num)
{

	int len=0,inde=-1,i=0,j=0;
	memset(res1,0x00,sizeof(res1));
	memset(res2,0x00,sizeof(res2));
	len=strlen(source);
	if((len==0)||(num==0))
	{
		strcpy(res1,"");
		strcpy(res2,"");
		return -1;
	}
	if(num>0)
	{
		for(i=0;i<len;i++)
		{
			if(source[i]==c)
			{
				j++;
				if(j==num)
				{
					inde=i;
					break;
				}
			}
		}
	}
	else
	{
		num=-num;
		for(i=len-1;i>=0;i--)
		{
			if(source[i]==c)
			{
				j++;
				if(j==num)
				{
					inde=i;
					break;
				}
			}
		}
	}
	if(inde!=(-1))
	{
		strcpy(res1,SubString(source,0,inde));
		strcpy(res2,SubString(source,inde+1,len-inde-1));
	}
	else
	{
		strcpy(res1,"");
		strcpy(res2,"");
		return -1;
	}
	return 0;
}

/*Modify in 20120813 */
/*去掉字符串中间的空格--对两边的不处理*/
char *mtrim(char *str)
{
	int i=0,k=0,len=0,beg=-1,end=-1;
	char *s;
	len=strlen(str);
	if(len==0)
		return "";
	for(i=0;i<len;i++)
	{
		if(str[i]!=' ')
		{
			beg=i;
			break;
		}
	}
	if(beg==(-1))
	{
		trim(str);
		return str;
	}
	for(i=len-1;i>=0;i--)
	{
		if(str[i]!=' ')
		{
			end=len-i-1;
			break;
		}
	}
	trim(str);
	strrep(str," ","");
	s=(char *)malloc(len+1);
	if(beg>0)
	{
		for(i=0;i<beg;i++)
		{
			s[k++]=' ';
		}
	}
	len=strlen(str);
	if(len>0)
	{
		for(i=0;i<len;i++)
		{
			s[k++]=str[i];
		}
	}
	if(end>0)
	{
		for(i=0;i<end;i++)
		{
			s[k++]=' ';
		}
	}
	s[k]='\0';
	strcpy(str,s);
	return str;
}

/*Add in 20120812 */
/*将小于99999的数字转换成汉字形式*/
char *GetChineseSZ(int ncount)
{
	int i=0,len=0,k=0;
	int tmpnum[6];
	char tmpstr[6];
	static char result[100];
	
	memset(result,0x00,sizeof(result));
	memset(tmpstr,0x00,sizeof(tmpstr));
	if((ncount>99999)||(ncount<(-99999)))
	{
		return "";
	}
	if(ncount==0)
	{
		return "零";
	}
	if(ncount<0)
	{
		strcpy(result,"负");
		ncount=-ncount;
	}
	else
	{
		strcpy(result,"");
	}
	sprintf(tmpstr,"%d",ncount);
	for(i=0;i<6;i++)
	{
		tmpnum[i]=-1;
	}
	len=strlen(tmpstr);
	if(len==0)
		return "";
	for(i=len-1;i>=0;i--)
	{
		tmpnum[k++]=atoi(SubString(tmpstr,i,1));
	}
	for(i=k-1;i>=0;i--)
	{
		if(tmpnum[i]!=(-1))
		{
			switch (i)
			{
				case 0:if(tmpnum[i]!=0){strcat(result,GetHanZi(tmpnum[i]));}break;
				case 1:if(tmpnum[i]==0){strcat(result,"零");}else{if((tmpnum[i]==1)&&(i==(k-1))){strcat(result,"十");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"十");}}break;
				case 2:if(tmpnum[i]==0){strcat(result,"零");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"百");}break;
				case 3:if(tmpnum[i]==0){strcat(result,"零");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"千");}break;
				case 4:if(tmpnum[i]==0){strcat(result,"万");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"万");}break;
			};
		}
	}
	while(strcon(result,"零零")==0)
	{
		strrep(result,"零零","零");
	}
	len=strlen(result);
	if(len>=4)
	{
		if(strcmp(SubString(result,len-2,2),"零")==0)
		{
			strcpy(result,SubString(result,0,len-2));
		}
	}
	return result;
}

/*第一部分--END*/






/*第二部分--BEGIN*/
/*时间、日期处理函数*/


/*得到当前系统时间--小时 格式为HH*/
char *GetSysHours()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%02d",tp->tm_hour);
	return(str);
}

/*得到当前系统时间--分钟 格式为MM*/
char *GetSysMinute()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%02d",tp->tm_min);
	return(str);
}

/*得到当前系统时间--秒 格式为SS*/
char *GetSysSecond()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%02d",tp->tm_sec);
	return(str);
}

/*得到当前系统时间毫秒 格式为int MIS*/
int GetSysMilli()
{
	int miltime=0;
	static char str[20];
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	miltime=sysTime.wMilliseconds;
	return miltime;
}

/*得到当前系统日期年份 格式为YYYY*/
char *GetSysYear()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%04d",tp->tm_year+1900);
	return(str);
}

/*得到当前系统日期月份 格式为MM*/
char *GetSysMonth()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%02d",tp->tm_mon+1);
	return(str);
}

/*得到当前系统日期日 格式为DD*/
char *GetSysDay()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%02d",tp->tm_mday);
	return(str);
}

/*得到当前系统时间 格式为HHMMSS*/
char *GetSysTime()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%02d%02d%02d",tp->tm_hour,tp->tm_min,tp->tm_sec);
	return(str);
}

/*得到当前系统时间 精确到毫秒级 格式为HHMMSS.MIS*/
char *GetSysMilTime()
{
	static char str[20];
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	sprintf(str,"%02d%02d%02d.%03d",sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	return(str);
}

/*得到当前系统日期 格式为YYYYMMDD*/
char *GetSysDate()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%04d%02d%02d",
	tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);
	return(str);
}

/*得到当前系统日期 格式为YYYY.MM.DD*/
char *GetSysDateDot()
{
	struct tm *tp=NULL;
	time_t t;
	static char str[16];
	time(&t);
	tp = (struct tm *)localtime(&t);
	sprintf(str,"%04d.%02d.%02d",
	tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);
	return(str);
}

/*得到当前系统日期时间 格式为YYYYMMDDHHMMSS*/
char *GetSysDateTime()
{
	static char str[20];
	struct tm *tp=NULL;
	time_t t;
	time(&t);
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	tp = (struct tm *)localtime(&t);
	memset(str,0x00,sizeof(str));
	sprintf(str,"%04d%02d%02d%02d%02d%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
	return(str);
}

/*得到当前系统日期时间 格式为YYYYMMDDHHMMSS.MIL*/
char *GetSysDTM()
{
	static char str[20];
	struct tm *tp=NULL;
	time_t t;
	time(&t);
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	tp = (struct tm *)localtime(&t);
	memset(str,0x00,sizeof(str));
	sprintf(str,"%04d%02d%02d%02d%02d%02d.%03d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	return(str);
}

/*得到当前系统日期时间 格式为YYYYMMDDHHMMSS.minutes*/
char *GetSysDTMinutes()
{
	static char str[20];
	struct tm *tp=NULL;
	time_t t;
	time(&t);
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	tp = (struct tm *)localtime(&t);
	memset(str,0x00,sizeof(str));
	sprintf(str,"%04d%02d%02d%02d%02d%02d.%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wSecond);
	return(str);
}

/* 得到系统时间，格式为YYYY.MM.DD HH:MM:SS */
char *GetSysCloseDT()
{
	static char str[20];
	struct tm *tp=NULL;
	time_t t;
	time(&t);
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	tp = (struct tm *)localtime(&t);
	memset(str,0x00,sizeof(str));
	sprintf(str,"%04d.%02d.%02d %02d:%02d:%02d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
	return(str);
}

/*得到当前系统日期时间 格式为YYYY.MM.DD HH:MM:SS.MIL*/
char *GetSysDTMili()
{
	static char str[30];
	struct tm *tp=NULL;
	time_t t;
	time(&t);
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	tp = (struct tm *)localtime(&t);
	memset(str,0x00,sizeof(str));
	sprintf(str,"%04d.%02d.%02d %02d:%02d:%02d.%03d",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday,sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	return(str);
}

/* 判断是不是闰年 -1 平年  0 闰年 */
int RunNian(int year)
{
	/* return -1 平年  0 闰年*/
	if(((year%4==0)&&(year%100!=0))||(year%400==0))
		return 0;
	else return -1;
}

/*判断公历日期是否正确 并符合常理*/
/*参数：八位公历日期 YYYYMMDD*/
/*返回：0--正确  -1--不正确*/
int isdate(char *date)
{
	int y=0,m=0,d=0;
	if((strlen(date)!=8)||(isdigitstr(date)!=0))
		return -1;
	
	y=atoi(SubString(date,0,4));
	m=atoi(SubString(date,4,2));
	d=atoi(SubString(date,6,2));
	if((m>12)||(m<1))
		return -1;
	if(RunNian(y)==0)
	{
		if(m==2)
		{
			if((d>29)||(d<1))
				return -1;
		}
	}
	else
	{
		if(m==2)
		{
			if((d>28)||(d<1))
				return -1;
		}
	}
	if((m==1)||(m==3)||(m==5)||(m==7)||(m==8)||(m==10)||(m==12))
	{
		if((d>31)||(d<1))
			return -1;
	}
	if((m==4)||(m==6)||(m==9)||(m==11))
	{
		if((d>30)||(d<1))
			return -1;
	}
	return 0;
}


/*判断农历日期是否正确 并符合常理*/
/*参数：八位农历日期 YYYYMMDD 或 YYYYRMMDD*/
/*返回：0--正确  -1--不正确*/
int islunardate(char *date)
{
	int i=0,len=0,month=0,day=0;
	char c;
	len=strlen(date);
	if((len!=8)&&(len!=9))
		return -1;
	if(len==9)
	{
		if((date[4]!='R')&&(date[4]!='r'))
			return -1;
	}
	for(i=0;i<len;i++)
	{
		c=date[i];
		if(isdigit(c)==0)
		{
			if(i!=4)
			{
				return -1;
			}
		}
	}
	month=atoi(SubString(date,len-4,2));
	day=atoi(SubString(date,len-2,2));
	if((month>12)||(month<1))
		return -1;
	if((day<1)||(day>30))
		return -1;
	return 0;
}


/*判断时间是否正确 并符合常理*/
/*参数：六位时间 HHMMSS*/
/*返回：0--正确  -1--不正确*/
int istime(char *time)
{
	int h=0,m=0,s=0;
	if((strlen(time)!=6)||(isdigitstr(time)!=0))
		return -1;
	
	h=atoi(SubString(time,0,2));
	m=atoi(SubString(time,2,2));
	s=atoi(SubString(time,4,2));
	if((h>23)||(h<0))
		return -1;
	if((m>59)||(m<0))
		return -1;
	if((s>59)||(s<0))
		return -1;
	return 0;
}

/* 返回一个时间到00:00:00的秒数，输入格式为HHMMSS */
int GetMiaoChaFromBase(char *time)
{
	int h=0,m=0,s=0,shicha=0,fencha=0,miaocha=0,summiao=0;	
	h=atoi(SubString(time,0,2));
	m=atoi(SubString(time,2,2));
	s=atoi(SubString(time,4,2));
	shicha=h*60*60;
	fencha=m*60;
	miaocha=s;
	summiao=shicha+fencha+miaocha;
	return summiao;
}

/* 返回距离 1900.1.1 的天数(可以为负数) 参数格式为:YYYYMMDD */
int GetDayChaFromBase(char *date)
{
	int y=0,m=0,d=0,niancha=0,yuecha=0,richa=0,i=0,sumday=0;
	
	y=atoi(SubString(date,0,4));
	m=atoi(SubString(date,4,2));
	d=atoi(SubString(date,6,2));
	if(y>=1900)
	{
		for(i=1900;i<y;i++)
		{
			if(RunNian(i)==0)
			{
				niancha=niancha+366;
			}
			else niancha=niancha+365;
		}
		for(i=1;i<m;i++)
		{
			switch (i)
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:yuecha=yuecha+31;break;
				case 4:
				case 6:
				case 9:
				case 11:yuecha=yuecha+30;break;
				case 2:{
						if (RunNian(y)==0)
							{
								yuecha=yuecha+29;
							}
							else
							{
								yuecha=yuecha+28;
							}
							break;
						}
			}
		}
		richa=d-1;
		sumday=niancha+yuecha+richa;
	}
	else
	{
		for(i=y;i<1900;i++)
		{
			if(RunNian(i)==0)
			{
				niancha=niancha+366;
			}
			else niancha=niancha+365;
	
		}
		for(i=1;i<m;i++)
		{
			switch (i)
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:yuecha=yuecha+31;break;
				case 4:
				case 6:
				case 9:
				case 11:yuecha=yuecha+30;break;
				case 2:{
						if (RunNian(y)==0)
							{
								yuecha=yuecha+29;
							}
							else
							{
								yuecha=yuecha+28;
							}
							break;
						}
			}
		}
		richa=d-1;
		sumday=niancha-yuecha-richa;
		sumday=-sumday;
	}
	return sumday;
}

/* 得到两个时间点的秒数之差 参数格式均为:HHMMSS  */
int GetTimeMiaoCha(char *time1,char *time2)
{
	int summiao=0;
	summiao=GetMiaoChaFromBase(time1)-GetMiaoChaFromBase(time2);
	return summiao;
}

/* 此函数较为常用，返回结果可以为负数 */
/* 得到两个日期之间的天数差 参数格式为YYYYMMDD */
int GetDayCha(char *date1,char *date2)
{
	int sumday=0;
	sumday=GetDayChaFromBase(date1)-GetDayChaFromBase(date2);
	return sumday;
}

/* 得到某个时间点到当前系统的秒数差，可以返回负数 参数格式为:YYYYMMDD,HHMMSS */
/*此函数有问题，当两个日期相差太远时，计算机不足以保存完整并且正确的整数*/
/*目前只有在S.c 和R.c中使用这个函数，并且可以确保不会出问题*/
int GetMiaoChaFromSys(char *date,char *time)
{
	int summiao=0;
	summiao=GetDayCha(date,GetSysDate())*24*60*60+GetTimeMiaoCha(time,GetSysTime());
	return summiao;
}

/* 得到两个时间点之间的秒数差 输入格式为:YYYYMMDD,HHMMSS */
/*这个函数和上个函数问题一样，但是没有使用该函数的文件*/
/*现在把这个函数更改为返回天数差，自然，是返回double类型的*/
/* Modify in 20120706 */
double GetTianCha(char *date1,char *date2,char *time1,char *time2)
{
	double a=0,summiao=0;
	a=GetTimeMiaoCha(time1,time2);
	a=a/86400;
	summiao=GetDayCha(date1,date2)+a;
	return summiao;
}

/* Add in 20120705 */
/*判断一个日期dt2是否在两个日期dt1(小)和dt3(大)之间,格式均为标准8位*/
/*返回结果为0说明在，返回-1说明不在，情况包含两个端点*/
int CheckDate(char *dt1,char *dt2,char *dt3)
{
	int n1=0,n2=0,result=0;
	n1=GetDayCha(dt1,dt2);
	n2=GetDayCha(dt2,dt3);
	if(n1>0)
	{
		result=-1;
	}
	else if(n1==0)
	{
		result=0;
	}
	else if(n1<0)
	{
		if(n2>0)
		{
			result=-1;
		}
		else if(n2==0)
		{
			result=0;
		}
		else if(n2<0)
		{
			result=0;
		}
	}
	return result;
}

/* 得到系统开机时间，格式为YYYY.MM.DD HH:MM:SS */
char *GetSysBootTime()
{
	int TickC=0,y=0,mont=0,d=0,h=0,minu=0,s=0,i=0;
	char dtime[20];
	static char result[20];
	memset(dtime,0x00,sizeof(dtime));
	strcpy(dtime,GetSysDTM());
	TickC=GetTickCount()/1000;
	y=atoi(SubString(dtime,0,4));
	mont=atoi(SubString(dtime,4,2));
	d=atoi(SubString(dtime,6,2));
	h=atoi(SubString(dtime,8,2));
	minu=atoi(SubString(dtime,10,2));
	s=atoi(SubString(dtime,10,2));
	for(i=0;i<TickC;i++)
	{
		s--;
		if(s<0)
		{
			s=59;
			minu--;
			if(minu<0)
			{
				minu=59;
				h--;
				if(h<0)
				{
					h=23;
					d--;
					if(d<1)
					{
						mont--;
						if(mont<1)
						{
							mont=12;
							d=31;
							y--;
						}
						else
						{
							switch (mont)
							{
								case 1:
								case 3:
								case 5:
								case 7:
								case 8:
								case 10:
								case 12:d=31;break;
								case 4:
								case 6:
								case 9:
								case 11:d=30;break;
								case 2:{
											if (RunNian(y)==0)
											{
												d=29;
											}
											else
											{
												d=28;
											}
											break;
										}
							}
						}
					}
				}
			}
		}
	}

	sprintf(result,"%04d.%02d.%02d %02d:%02d:%02d",y,mont,d,h,minu,s);
	return(result);
}

/* 得到日期 */
/* 参数一：基准日期 YYYYMMDD */
/* 参数二：增加或者减少的天数，负数为减少 */
/* 返回结果：日期 YYYYMMDD */
char *GetDate(char *date,int num)
{
	int year=0,month=0,day=0,i=0,n=0;
	char c;
	static char result[20];
	char today[20];
	memset(result,0x00,sizeof(result));
	memset(today,0x00,sizeof(today));
	strcpy(today,date);
	year=atoi(SubString(today,0,4));
	month=atoi(SubString(today,4,2));
	day=atoi(SubString(today,6,2));
	if(num==0)
	{
		strcpy(result,today);
		return result;
	}
	if(num<0)
	{
		c='-';
		n=-num;
	}
	else
	{
		c='+';
		n=num;
	}
	for(i=0;i<n;i++)
	{
		if(c=='-')
		{
			day--;
			if(day==0)
			{
				month--;
				if(month==0)
				{
					month=12;
					year--;
				}
				switch (month)
				{
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12:{day=31;break;}
					case 4:
					case 6:
					case 9:
					case 11:{day=30;break;}
					case 2:{
							if(RunNian(year)==0)
							{
								day=29;
							}
							else
							{
								day=28;
							}
							break;
						}
				};
			}
		}
		else
		{
			day++;
			switch (month)
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:{
							if(day==32)
							{
								day=1;
								month++;
							}
							break;
						}
				case 4:
				case 6:
				case 9:
				case 11:{
							if(day==31)
							{
								day=1;
								month++;
							}
							break;
						}
				case 2:{
							if(RunNian(year)==0)
							{
								if(day==30)
								{
									day=1;
									month++;
								}
							}
							else
							{
								if(day==29)
								{
									day=1;
									month++;
								}
							}
							break;
					}
			};
			if(month==13)
			{
				month=1;
				year++;
			}
		}
	}
	sprintf(result,"%04d%02d%02d",year,month,day);
	return result;
}

/*Add in 201207 for Lunar Calendar */
/*以一个基准日期为基础，加上一定的秒数，得到一个日期*/
/*循环次数，为连续相加，只返回最后结果*/
/*参数source为基准日期，addsecond为要加的秒数，num为循环次数，可以等于零，num为负数时表示相减*/
/*返回结果为相加之后的日期，source与result的格式均为YYYYMMDDHHMMSSMIL*/
char *CalcSecond(char *source,double addsecond,int num)
{
	char based[20];
	char olddate[20];
	char newdate[20];
	char thour[3];
	char tminute[3];
	char tsecond[3];
	char tmilsec[4];
	static char result[20];
	int i=0,lday=0,lhour=0,lminute=0,lsecond=0,lmils=0,nhour=0,nminute=0,nsecond=0,nmilsec=0;
	
	
	/*得到一个相加秒数的具体天、时、分、秒、毫秒*/
	i=addsecond;
	lday=addsecond/86400;
	lhour=(addsecond-86400*lday)/3600;
	lminute=(addsecond-86400*lday-3600*lhour)/60;
	lsecond=addsecond-86400*lday-3600*lhour-60*lminute;
	lmils=(addsecond-i)*1000;
	
	
	/*初始化based为基准日期*/
	memset(based,0x00,sizeof(based));
	memset(result,0x00,sizeof(result));
	strncpy(based,source,sizeof(based));
	
	if(num<0)
	{
		num=-num;
		for(i=0;i<num;i++)
		{
			/*先让based减去一个秒数拥有的的整天数*/
			memset(olddate,0x00,sizeof(olddate));
			memset(newdate,0x00,sizeof(newdate));
			strncpy(olddate,SubString(based,0,8),sizeof(olddate));
			strncpy(newdate,GetDate(olddate,-lday),sizeof(newdate));
			memset(olddate,0x00,sizeof(olddate));
			strncpy(olddate,SubString(based,8,9),sizeof(olddate));
			memset(based,0x00,sizeof(based));
			sprintf(based,"%s%s",newdate,olddate);
			
			
			/*时分秒毫秒按顺序想减*/
			memset(olddate,0x00,sizeof(olddate));
			memset(thour,0x00,sizeof(thour));
			memset(tminute,0x00,sizeof(tminute));
			memset(tsecond,0x00,sizeof(tsecond));
			memset(tmilsec,0x00,sizeof(tmilsec));
			strncpy(olddate,SubString(based,0,8),sizeof(olddate));
			strncpy(thour,SubString(based,8,2),sizeof(thour));
			strncpy(tminute,SubString(based,10,2),sizeof(tminute));
			strncpy(tsecond,SubString(based,12,2),sizeof(tsecond));
			strncpy(tmilsec,SubString(based,14,3),sizeof(tmilsec));
			nhour=0;
			nminute=0;
			nsecond=0;
			nmilsec=0;
			nhour=atoi(thour);
			nminute=atoi(tminute);
			nsecond=atoi(tsecond);
			nmilsec=atoi(tmilsec);
			nhour-=lhour;
			nminute-=lminute;
			nsecond-=lsecond;
			nmilsec-=lmils;
			if(nmilsec<0)
			{
				nmilsec=nmilsec+1000;
				nsecond--;
			}
			if(nsecond<0)
			{
				nsecond=nsecond+60;
				nminute--;
			}
			if(nminute<0)
			{
				nminute=nminute+60;
				nhour--;
			}
			if(nhour<0)
			{
				nhour=nhour+24;
				memset(newdate,0x00,sizeof(newdate));
				strncpy(newdate,GetDate(olddate,-1),sizeof(newdate));
			}
			/*最后得到一个加一个秒数后的based*/
			memset(based,0x00,sizeof(based));
			sprintf(based,"%08s%02d%02d%02d%03d",newdate,nhour,nminute,nsecond,nmilsec);
			
			/*循环结尾，每循环一次加一个秒数*/
		}
	}
	else
	{
		for(i=0;i<num;i++)
		{
			/*先让based加上一个秒数拥有的的整天数*/
			memset(olddate,0x00,sizeof(olddate));
			memset(newdate,0x00,sizeof(newdate));
			strncpy(olddate,SubString(based,0,8),sizeof(olddate));
			strncpy(newdate,GetDate(olddate,lday),sizeof(newdate));
			memset(olddate,0x00,sizeof(olddate));
			strncpy(olddate,SubString(based,8,9),sizeof(olddate));
			memset(based,0x00,sizeof(based));
			sprintf(based,"%s%s",newdate,olddate);
			
			
			/*时分秒毫秒按顺序加*/
			memset(olddate,0x00,sizeof(olddate));
			memset(thour,0x00,sizeof(thour));
			memset(tminute,0x00,sizeof(tminute));
			memset(tsecond,0x00,sizeof(tsecond));
			memset(tmilsec,0x00,sizeof(tmilsec));
			strncpy(olddate,SubString(based,0,8),sizeof(olddate));
			strncpy(thour,SubString(based,8,2),sizeof(thour));
			strncpy(tminute,SubString(based,10,2),sizeof(tminute));
			strncpy(tsecond,SubString(based,12,2),sizeof(tsecond));
			strncpy(tmilsec,SubString(based,14,3),sizeof(tmilsec));
			nhour=atoi(thour);
			nminute=atoi(tminute);
			nsecond=atoi(tsecond);
			nmilsec=atoi(tmilsec);
			
			nhour+=lhour;
			nminute+=lminute;
			nsecond+=lsecond;
			nmilsec+=lmils;
			
			if(nmilsec>=1000)
			{
				nmilsec=nmilsec-1000;
				nsecond++;
			}
			if(nsecond>=60)
			{
				nsecond=nsecond-60;
				nminute++;
			}
			if(nminute>=60)
			{
				nminute=nminute-60;
				nhour++;
			}
			if(nhour>=24)
			{
				nhour=nhour-24;
				memset(newdate,0x00,sizeof(newdate));
				strncpy(newdate,GetDate(olddate,1),sizeof(newdate));
			}
			/*最后得到一个加一个秒数后的based*/
			memset(based,0x00,sizeof(based));
			
			sprintf(based,"%08s%02d%02d%02d%03d",newdate,nhour,nminute,nsecond,nmilsec);
			/*循环结尾，每循环一次加一个秒数*/
		}
	}
	strncpy(result,based,sizeof(result));
	return result;
}

/* 得到任意日期的星期，返回从星期一到星期日的汉字 */
/* type为chinese时得到中文返回，占6个字节,其他返回英文,均占5个字节 */
/* 20120705 增加另外一种算法，因为使用普通算法当时间小于1980年则算不出来 */
char *GetWeek(char *date,char *wtype)
{
	int iyear=0,imonth=0,iday=0,weeknum=0,daycha=0,wkcha=0,flag=0;
	static char str[10];
	struct tm newtime;

	iyear=atoi(SubString(date,0,4));
	imonth=atoi(SubString(date,4,2));
	iday=atoi(SubString(date,6,2));

	iyear=iyear-1900;
	imonth=imonth-1;


	newtime.tm_sec=0;
	newtime.tm_min=0;
	newtime.tm_hour=0;
	newtime.tm_mday=iday;
	newtime.tm_mon=imonth;
	newtime.tm_year=iyear;
	mktime(&newtime);

	weeknum=newtime.tm_wday;
   	memset(str,0x00,sizeof(str));
	if(strcasecmp(wtype,"chinese")==0)
	{
		switch (weeknum)
		{
			case 0:sprintf(str,"星期日");break;
			case 1:sprintf(str,"星期一");break;
			case 2:sprintf(str,"星期二");break;
			case 3:sprintf(str,"星期三");break;
			case 4:sprintf(str,"星期四");break;
			case 5:sprintf(str,"星期五");break;
			case 6:sprintf(str,"星期六");break;
		};
	}
	else
	{
		switch (weeknum)
		{
			case 0:sprintf(str,"Sun. ");break;
			case 1:sprintf(str,"Mon. ");break;
			case 2:sprintf(str,"Tues.");break;
			case 3:sprintf(str,"Wed. ");break;
			case 4:sprintf(str,"Thur.");break;
			case 5:sprintf(str,"Fri. ");break;
			case 6:sprintf(str,"Say. ");break;
		};
	}
	if(strlen(str)==0)
	{
		/*20120707 add */
		/*返回某一天的星期*/
		/*当利用平常天数求不出星期来的话，那么利用此办法*/
		/*以两千零零年一月一日是星期六为基础*/
		/*利用基数办法求星期*/
		memset(str,0x00,sizeof(str));
		daycha=GetDayCha(date,"20000101");
		flag=0;
		if(daycha<0)
		{
			flag=1;
			daycha=-daycha;
		}
		wkcha=daycha%7;
		if(flag==0)
		{
			if(strcasecmp(wtype,"chinese")==0)
			{
				switch (wkcha)
				{
					case 0:strcpy(str,"星期六");break;
					case 1:strcpy(str,"星期日");break;
					case 2:strcpy(str,"星期一");break;
					case 3:strcpy(str,"星期二");break;
					case 4:strcpy(str,"星期三");break;
					case 5:strcpy(str,"星期四");break;
					case 6:strcpy(str,"星期五");break;
				};
			}
			else
			{
				switch (wkcha)
				{
					case 0:strcpy(str,"Say.");break;
					case 1:strcpy(str,"Sun.");break;
					case 2:strcpy(str,"Mon.");break;
					case 3:strcpy(str,"Tues.");break;
					case 4:strcpy(str,"Wed.");break;
					case 5:strcpy(str,"Thur.");break;
					case 6:strcpy(str,"Fri.");break;
				};
			}
		}
		else
		{
			if(strcasecmp(wtype,"chinese")==0)
			{
				switch (wkcha)
				{
					case 0:strcpy(str,"星期六");break;
					case 1:strcpy(str,"星期五");break;
					case 2:strcpy(str,"星期四");break;
					case 3:strcpy(str,"星期三");break;
					case 4:strcpy(str,"星期二");break;
					case 5:strcpy(str,"星期一");break;
					case 6:strcpy(str,"星期日");break;
				};
			}
			else
			{
				switch (wkcha)
				{
					case 0:strcpy(str,"Say.");break;
					case 1:strcpy(str,"Fri.");break;
					case 2:strcpy(str,"Thur.");break;
					case 3:strcpy(str,"Wed.");break;
					case 4:strcpy(str,"Tues.");break;
					case 5:strcpy(str,"Mon.");break;
					case 6:strcpy(str,"Sun.");break;
				};
			}
		}
	}
	return(str);
}

/*第二部分--END*/






/*第三部分--BEGIN*/
/*随机函数*/


/*20120709 add*/
/*得到格式为HHMMSSMIL九位的随机数种子*/
int GetRandTime()
{
	int result=0;
	char str[20];
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	memset(str,0x00,sizeof(str));
	sprintf(str,"%02d%02d%02d%03d",sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	result=atoi(str);
	return result;
}

/*20120709 add*/
/*返回一个num位长度的随机数，以字符串的形式返回*/
/*此函数调用以毫秒为单位，所以，请不要再一毫秒内调用两次及以上*/
char *GetRandStr(int num)
{
	int i=0,k=0;
	char tmpstr[2];
	char *result;
	result=(char *)malloc(num+1);
	srand(GetRandTime());
	for(i=0;i<num;i++)
	{
		memset(tmpstr,0x00,sizeof(tmpstr));
		sprintf(tmpstr,"%d",rand()%10);
		result[k++]=tmpstr[0];
	}
	result[k]='\0';
	return result;
}

/*第三部分--END*/





/*第四部分--BEGIN*/
/*文件名及路径处理*/


/* 换掉路径中所有的环境变量 */
char *ConvertEnv(char *source)
{
	int i=0,j=0,k=0,len=0,beg=0,end=0;
	char envstr[30+1];
	char repstr[32+1];
	char tmpstr[100];
	while(1)
	{
		len=strlen(source);
		i=0;
		beg=-1;
		end=-1;
		for(i=0;i<len;i++)
		{
			if(source[i]=='%')
			{
				beg=i;
				break;
			}
		}
		if(beg==-1)
			break;
		if((i+1)==len)
			break;
		for(j=i+1;j++;j<len)
		{
			if(source[j]=='%')
			{
				end=j;
				break;
			}
		}
		if(end==-1)
			break;
		k=0;
		memset(envstr,0x00,sizeof(envstr));
		i=beg+1;
		for(i=beg+1;i<end;i++)
		{
			envstr[k++]=source[i];
		}
		envstr[k]='\0';
		memset(repstr,0x00,sizeof(repstr));
		strcpy(repstr,"\%");
		strcat(repstr,envstr);
		strcat(repstr,"\%");
		if(getenv(envstr)==NULL)
		{
			sprintf(tmpstr,"找不到环境变量！--%s",envstr);
			MessageBox(NULL,tmpstr,"错误",MB_OK|MB_ICONERROR);
			AppExit(0);
		}
		strcaserep(source,repstr,getenv(envstr));
	}
	return source;
}

/*标准化文件名称，如果带路径则变为不带路径*/
char *StdFile(char *filename)
{
	static char result[MAX_PATH];
	memset(result,0x00,sizeof(result));
	int i=0;
	i=LastIndexof(filename,'\\');
	if (i==(-1))
	{
		strcpy(result,filename);
	}
	else
	{
		strcpy(result,SubString(filename,i+1,strlen(filename)-i-1));
	}
	return result;
}

/* 得到标准文件名 */
/* 参数格式：全路径的文件名、非全路径的文件名、文件名带dot，文件名不带dot */
/* 返回结果：不带后缀的文件名 */
char *GetFileName(char *str)
{
	char tmpstr[MAX_PATH];
	static char result[MAX_PATH];
	memset(tmpstr,0x00,sizeof(tmpstr));
	memset(result,0x00,sizeof(result));
	if(strcon(str,"\\")==0)
	{
		strcpy(tmpstr,SubString(str,LastIndexof(str,'\\')+1,strlen(str)-LastIndexof(str,'\\')-1));
	}
	else
	{
		strcpy(tmpstr,str);
	}
	if(strcon(tmpstr,".")==0)
	{
		strcpy(result,SubString(tmpstr,0,LastIndexof(tmpstr,'.')));
	}
	else
	{
		strcpy(result,tmpstr);
	}
	return result;
}

/*得到当前EXE的路径（不包含文件名）*/
char *GetExePath()
{
	static char result[MAX_PATH];
	memset(result,0x00,sizeof(result));
	strcpy(result,SubString(__EXE__,0,LastIndexof(__EXE__,'\\')));
	return result;
}

/*第四部分--END*/






/*第五部分--BEGIN*/
/*配置文件处理*/



/* 得到关键词的值 source 为关键字*/
char *GetConfig(char *source)
{
	int flag=0;
	char tmpstr[MAX_PATH];
	static char result[MAX_PATH];
	memset(result,0x00,sizeof(result));
	
	FILE *cfgfp;
	char linebuf[300];
	char res1[300];
	char res2[300];
	char *p;
	ConvertEnv(CONFIG_NAME);
	cfgfp=fopen(CONFIG_NAME,"r");
	if(cfgfp==NULL)
	{
		if((strcasecmp(source,"logpath")==0)||(strcasecmp(source,"tmppath")==0))
		{
			strcpy(result,GetExePath());
		}
		else if(strcasecmp(source,"logbutton")==0)
		{
			strcpy(result,"on");
		}
		else if(strcasecmp(source,"WeekLanguage")==0)
		{
			strcpy(result,"chinese");
		}
		else if(strcasecmp(source,"diyholidayfile")==0)
		{
			strcpy(result,GetExePath());
			strcat(result,"\\DiyHoliday.cfg");
		}
		else
		{
			flag=-1;
			strcpy(result,"");
		}
	}
	else
	{
		while(!feof(cfgfp))
		{
			memset(linebuf,0x00,sizeof(linebuf));
			memset(res1,0x00,sizeof(res1));
			memset(res2,0x00,sizeof(res2));
			fgets( linebuf, sizeof(linebuf), cfgfp );
			if((strlen(linebuf)==0)||(strcasecmp(linebuf,"\n")==0))
				continue;
			strcpy(linebuf,strtok(linebuf,"\n"));
			trim(linebuf);
			if(strlen(linebuf)==0)
				continue;
			if(linebuf[0]=='#')
				continue;
			p=NULL;
			p=strstr(linebuf,"=");
			if(p==NULL)
				continue;
			strdiv(linebuf,res1,res2,'=',1);
			if(strcasecmp(source,res1)==0)
			{
				strcpy(result,res2);
				break;
			}
		}
		fclose(cfgfp);
	}
	if(strlen(result)==0)
	{
		memset(tmpstr,0x00,sizeof(tmpstr));
		if(flag==(-1))
		{
			sprintf(tmpstr,"找不到程序配置文件！--%s",CONFIG_NAME);
			MessageBox(NULL,tmpstr,"错误",MB_OK|MB_ICONERROR);
		}
		else
		{
			sprintf(tmpstr,"找不到%s的值！",source);
			MessageBox(NULL,tmpstr,"错误",MB_OK|MB_ICONERROR);
		}
		AppExit(0);
	}
	else
	{
		ConvertEnv(result);
	}
	return result;
}

/* 设置配置文件 ARGS 为[KEYWPRD=VALUES]*/
int SetConfig(char *source)
{
	int i=0,len=0,flag=0;
	char content[5000];
	char newvalue[100];
	char cmpstr[100];
	char str1[100];
	char str2[100];
	char linebuf[300];
	char sou1[300];
	char sou2[300];
	char *p;
	FILE *cfgfp;
	FILE *tp;

	memset(newvalue,0x00,sizeof(newvalue));
	memset(cmpstr,0x00,sizeof(cmpstr));
	strcpy(newvalue,source);
	flag=Indexof(newvalue,'=');
	if(flag==-1)
	{
		printf("New Value is a Wrong format![%s]\n",newvalue);
		return -1;
	}
	strncpy(cmpstr,newvalue,flag+1);
	len=strlen(cmpstr);
	ConvertEnv(CONFIG_NAME);
	cfgfp=fopen(CONFIG_NAME,"r");
	if(cfgfp==NULL)
	{
		printf("Config file open  Err![%s]\n",CONFIG_NAME);
		return -1;
	}
	memset(content,0x00,sizeof(content));
	while(!feof(cfgfp))
	{
		memset(linebuf,0x00,sizeof(linebuf));
		fgets(linebuf,sizeof(linebuf),cfgfp);
		trim(linebuf);
		if(strlen(linebuf)==0)
		{
			strcat(content,"\n");
			continue;
		}
		if(linebuf[0]=='#')
		{
			strcat(content,linebuf);
			continue;
		}
		memset(str1,0x00,sizeof(str1));
		memset(str2,0x00,sizeof(str2));
		strcpy(str1,cmpstr);
		strcpy(str2,linebuf);
		strcpy(str1,strlwr(str1));
		strcpy(str2,strlwr(str2));
		if(memcmp(str1,str2,len)==0)
		{
			strcat(content,newvalue);
			strcat(content,"\n");
			continue;
		}
		else
		{
			strcat(content,linebuf);
			continue;
		}
	}
	fclose(cfgfp);
	cfgfp=NULL;
	if(strlen(content)!=0)
	{
		cfgfp=fopen(CONFIG_NAME,"w");
		if(cfgfp==NULL)
		{
			printf("Config file open  Err![%s]\n",CONFIG_NAME);
			return -1;
		}
		content[strlen(content)-1]='\0';
		fprintf(cfgfp,"%s",content);
		fclose(cfgfp);
	}
	return 0;
}

/*第五部分--END*/





/*第六部分--BEGIN*/
/*写日志模块*/


/*日志开关 0-关 其他-开*/
int SetLogButton(int logstate)
{
	if(logstate!=0)
		logstate=1;
	LOG_BUTTON=logstate;
	return 0;
}

/*冲缓冲池，将缓冲池内数据写入日志文件，主调函数末尾必须要添加该函数*/
int LogFlush()
{
	int i=0;
	if (LOG_BUTTON==0)
		return -1;
	if(strlen(LOG_FILE)==0)
		return -1;
	FILE *fp;
	fp=fopen(LOG_FILE,"a+");
	if(fp==NULL)
	{
		printf("LogFile [%s] Open Error!\n",LOG_FILE);
		return -1;
	}
	else
	{
		if (LOG_BUFFNOWNUM>0)
		{
			for(i=0;i<LOG_BUFFNOWNUM;i++)
				fwrite(LOG_BUFF[i],strlen(LOG_BUFF[i]),1,fp);
		}
		fclose(fp);
		memset(LOG_BUFF,0x00,sizeof(LOG_BUFF));
		LOG_BUFFNOWNUM=0;
		return 0;
	}
	return 0;
}

/*写日志*/
int WriteLog(char *zhufile,int lnum,char *fmt,...)
{
	va_list args;
	char    tmpmsg[LOG_MANBUFFLEN];
	char	tmphead[LOG_MANBUFFLEN];
	char	tmpsfile[MAX_PATH];
	if(LOG_BUTTON==0)
		return -1;
	if(strlen(LOG_FILE)==0)
		return -1;
	memset(tmpsfile,0x00,sizeof(tmpsfile));
	memset(tmpmsg,0x00,sizeof(tmpmsg));
	memset(tmphead,0x00,sizeof(tmphead));
	strcpy(tmpsfile,StdFile(zhufile));
	va_start(args, fmt);
	vsnprintf(tmpmsg, sizeof(tmpmsg) - 1, fmt, args);
	va_end(args);
	sprintf(tmphead,"%08s|%10s|%s|%s-%04d|%s\n",GetSysDate(),GetSysMilTime(),GetWeek(GetSysDate(),WEEK_LANG_TYPE),tmpsfile,lnum,tmpmsg);
	if(LOG_BUFFNOWNUM==LOG_MAXBUFFNUM)
		LogFlush();
	memset(LOG_BUFF[LOG_BUFFNOWNUM],0x00,sizeof(LOG_BUFF[LOG_BUFFNOWNUM]));
	strcpy(LOG_BUFF[LOG_BUFFNOWNUM++],tmphead);
	return 0;
}

/*日志初始化，包括日志文件名设置、初始化缓冲池、当前缓冲个数*/
int CpyLogFile(char *logfilename)
{
	int len=0;
	char logsta[10];
	char logpath[MAX_PATH];
	if(LOG_BUTTON==0)
		return -1;
	if(LOG_BUFFNOWNUM!=0)
		LogFlush();
	memset(logsta,0x00,sizeof(logsta));
	memset(LOG_FILE,0x00,sizeof(LOG_FILE));
	memset(logpath,0x00,sizeof(logpath));
	sprintf(logpath,"%s\\",GetConfig("logpath"));
	sprintf(logsta,"%s",GetConfig("logButton"));
	if(strcasecmp(logsta,"off")==0)
	{
		SetLogButton(0);
	}
	else if(strcasecmp(logsta,"on")==0)
	{
		SetLogButton(1);
	}
	len=strlen(logfilename);
	if(len<=4)
	{
		if(len==0)
		{
			sprintf(logfilename,"%s.log",GetFileName(_pgmptr));
		}
		else
		{
			strcat(logfilename,".log");
		}
	}
	else
	{
		if(strcasecmp(SubString(logfilename,len-4,4),".log")!=0)
		{
			strcat(logfilename,".log");
		}
	}
	if(logfilename[1]==':')
	{
		strcpy(LOG_FILE,logfilename);
	}
	else
	{
		sprintf(LOG_FILE,"%s\\%s",GetConfig("logpath"),logfilename);
	}
	memset(LOG_BUFF,0x00,sizeof(LOG_BUFF));
	LOG_BUFFNOWNUM=0;
	if(APPTIMESTART==0)
	{
		APPTIMESTART=GetTickCount();
		memset(WEEK_LANG_TYPE,0x00,sizeof(WEEK_LANG_TYPE));
		strcpy(WEEK_LANG_TYPE,GetConfig("WeekLanguage"));
		WriteLog(LOGLVL,"====================Log Begin====================");
	}
	else
	{
		WriteLog(LOGLVL,"===================Log Continue==================");
	}
	return 0;
}

/*第六部分--END*/






/*第七部分--BEGIN*/
/*文件及文件夹处理*/


/* 创建文件夹--可以多级创建 */
/* 返回0成功，-1失败 */
int CreateDir(char *path)
{
	int i=0,len=0,k=0;
	int dirdeep[MAX_DIRDEEP]={0};
	len=strlen(path);
	if(len<=2)
		return 0;
	if(strcon(path,"\\")!=0)
		return 0;
	for(i=0;i<len;i++)
	{
		if(path[i]=='\\')
			dirdeep[k++]=i;
	}
	if(i>1)
	{
		for(i=1;i<k;i++)
			mkdir(SubString(path,0,dirdeep[i]));	
	}
	mkdir(path);
	return 0;
}

/* 判断目录是否为空 返回零为空 .和..不包含在内 */
int GetDirNum(char *str)
{
	DIR *dirp;
	int num=0;
	dirp = opendir(str);
	while (dirp)
	{
		if ( readdir(dirp) != NULL)
			++num;
		else
			break;
	}
	closedir(dirp);
	num=num-2;
	return num;
}

/* 判断是否是".."目录和"."目录*/
/* 0--是 1--否*/
/* 非接口*/
int is_special_dir(const char *path)
{
	if((strcmp(path,"..")==0)||(strcmp(path,".")==0))
		return 0;
	return -1;
}

/* 判断文件属性是目录还是文件--包含特殊文件夹.和..*/
/* 0--目录 1--文件*/
/* 接口*/
int IsDir(struct _finddata_t dirinfo)
{
	int i=0,len=0;
	char tmpstr[20];
	char tmpstr1[100];
	char tmpstr2[10];
	memset(tmpstr,0x00,sizeof(tmpstr));
	memset(tmpstr1,0x00,sizeof(tmpstr1));
	memset(tmpstr2,0x00,sizeof(tmpstr2));
	sprintf(tmpstr,"%x",dirinfo.attrib);
	strcpy(tmpstr1,"00000000");
	len=strlen(tmpstr);
	
	for(i=0;i<len;i++)
	{
		if(tmpstr[i]=='0')
		{
			strcat(tmpstr1,"0000");
		}
		else if(tmpstr[i]=='1')
		{
			strcat(tmpstr1,"0001");
		}
		else if(tmpstr[i]=='2')
		{
			strcat(tmpstr1,"0010");
		}
		else if(tmpstr[i]=='3')
		{
			strcat(tmpstr1,"0011");
		}
		else if(tmpstr[i]=='4')
		{
			strcat(tmpstr1,"0100");
		}
		else if(tmpstr[i]=='5')
		{
			strcat(tmpstr1,"0101");
		}
		else if(tmpstr[i]=='6')
		{
			strcat(tmpstr1,"0110");
		}
		else if(tmpstr[i]=='7')
		{
			strcat(tmpstr1,"0111");
		}
		else if(tmpstr[i]=='8')
		{
			strcat(tmpstr1,"1000");
		}
		else if(tmpstr[i]=='9')
		{
			strcat(tmpstr1,"1001");
		}
		else if((tmpstr[i]=='A')||(tmpstr[i]=='a'))
		{
			strcat(tmpstr1,"1010");
		}
		else if((tmpstr[i]=='B')||(tmpstr[i]=='b'))
		{
			strcat(tmpstr1,"1011");
		}
		else if((tmpstr[i]=='C')||(tmpstr[i]=='c'))
		{
			strcat(tmpstr1,"1100");
		}
		else if((tmpstr[i]=='D')||(tmpstr[i]=='d'))
		{
			strcat(tmpstr1,"1101");
		}
		else if((tmpstr[i]=='E')||(tmpstr[i]=='e'))
		{
			strcat(tmpstr1,"1110");
		}
		else if((tmpstr[i]=='F')||(tmpstr[i]=='f'))
		{
			strcat(tmpstr1,"1111");
		}
		
	}
	if(tmpstr1[strlen(tmpstr1)-5]=='1')
		return 0;
	return 1;
}

/* Copy和delete 目录时候用到，不作为接口用*/
/* 得到下一级目录的path*/
int get_file_path(char *path,char *filename,char *filepath)
{
	memset(filepath,0x00,sizeof(filepath));
	strcpy(filepath, path);
	filepath[strlen(filepath) - 1] = '\0';
	strcat(filepath, filename);
	strcat(filepath, "\\*");
	return 0;
}

/* copydir用，不作为接口*/
/* 得到下一个目标路径*/
int get_next_path(char *path,char *filename,char *filepath)
{
	memset(filepath,0x00,sizeof(filepath));
	sprintf(filepath,"%s\\%s",path,filename);
	return 0;
}

/*删除文件 0-成功 -1-失败*/
int RmFile(char *filename)
{
	int rec=0;
	char tmpstr[10];
	if(FORCEDEAL==0)
	{
		REINPUT:
		printf("Delete File -- %s ?(Yes/No)",filename);
		memset(tmpstr,0x00,sizeof(tmpstr));
		fgets(tmpstr,sizeof(tmpstr),stdin);
		if(strlen(tmpstr)==0)
			goto REINPUT;
		if(strcmp(tmpstr,"\n")==0)
			goto REINPUT;
		strrep(tmpstr,"\n","");
		if((strcasecmp(tmpstr,"yes")==0)||(strcasecmp(tmpstr,"y")==0))
		{
			rec=remove(filename);
		}
		else if((strcasecmp(tmpstr,"no")==0)||(strcasecmp(tmpstr,"n")==0))
		{
			return 0;
		}
		else
		{
			goto REINPUT;
		}
		
	}
	else
	{
		rec=remove(filename);
	}
	if(rec==(-1))
	{
		if(SHOWDEALINFO==1)
		{
			printf("Delete File Fail! -- %s\n",filename);
		}
		else if(SHOWDEALINFO==2)
		{
			WriteLog(LOGLVL,"Delete File Fail! -- %s",filename);
		}
		else if(SHOWDEALINFO==3)
		{
			printf("Delete File Fail! -- %s\n",filename);
			WriteLog(LOGLVL,"Delete File Fail! -- %s",filename);
		}
		return -1;
	}
	else
	{
		if(SHOWDEALINFO==1)
		{
			printf("Delete File OK! -- %s\n",filename);
		}
		else if(SHOWDEALINFO==2)
		{
			WriteLog(LOGLVL,"Delete File OK! -- %s",filename);
		}
		else if(SHOWDEALINFO==3)
		{
			printf("Delete File OK! -- %s\n",filename);
			WriteLog(LOGLVL,"Delete File OK! -- %s",filename);
		}
		return 0;
	}
}

/* 复制文件，参数必须为全路径 接口 */
/* 0-成功 -1失败 */
int CpFile(char *file1,char *file2)
{
	int ret=0;
	char tmpstr[10];
	if(FORCEDEAL==0)
	{
		ret=CopyFile(file1,file2,TRUE);
		if(ret==0)
		{
REINPUT:
			printf("File Already Exist -- %s ,OverWrite ? (Yes/No/All)",file2);
			memset(tmpstr,0x00,sizeof(tmpstr));
			fgets(tmpstr,sizeof(tmpstr),stdin);
			if(strlen(tmpstr)==0)
				goto REINPUT;
			if(strcmp(tmpstr,"\n")==0)
				goto REINPUT;
			strrep(tmpstr,"\n","");
			if((strcasecmp(tmpstr,"yes")==0)||(strcasecmp(tmpstr,"y")==0))
			{
				ret=CopyFile(file1,file2,FALSE);
			}
			else if((strcasecmp(tmpstr,"no")==0)||(strcasecmp(tmpstr,"n")==0))
			{
				return 0;
			}
			else if((strcasecmp(tmpstr,"all")==0)||(strcasecmp(tmpstr,"a")==0))
			{
				ret=CopyFile(file1,file2,FALSE);
				FORCEDEAL=1;
			}
			else
			{
				goto REINPUT;
			}
		}
	}
	else
	{
		ret=CopyFile(file1,file2,FALSE);
	}
	if(ret==0)
	{
		if(SHOWDEALINFO==1)
		{
			printf("Copy File Fail! -- %s -> %s\n",file1,file2);
		}
		else if(SHOWDEALINFO==2)
		{
			WriteLog(LOGLVL,"Copy File Fail! -- %s -> %s",file1,file2);
		}
		else if(SHOWDEALINFO==3)
		{
			printf("Copy File Fail! -- %s -> %s\n",file1,file2);
			WriteLog(LOGLVL,"Copy File Fail! -- %s -> %s",file1,file2);
		}
		return -1;
	}
	else
	{
		if(SHOWDEALINFO==1)
		{
			printf("Copy File OK! -- %s -> %s\n",file1,file2);
		}
		else if(SHOWDEALINFO==2)
		{
			WriteLog(LOGLVL,"Copy File OK! -- %s -> %s",file1,file2);
		}
		else if(SHOWDEALINFO==3)
		{
			printf("Copy File OK! -- %s -> %s\n",file1,file2);
			WriteLog(LOGLVL,"Copy File OK! -- %s -> %s",file1,file2);
		}
		return 0;
	}
		
	return 0;
}

/* copydir用，不作为接口*/
/* 复制文件*/
int cpy_file(char *path,char *filename,char *despath)
{
	int rec=0;
	char file1[MAX_PATH];
	char file2[MAX_PATH];
	memset(file1,0x00,sizeof(file1));
	memset(file2,0x00,sizeof(file2));
	sprintf(file1,"%s%s",SubString(path,0,strlen(path)-1),filename);
	sprintf(file2,"%s\\%s",despath,filename);
	rec=CpFile(file1,file2);
	
	if(rec!=0)
		return -1;
	return 0;
}

/* 递归搜索目录中文件并删除*/
/* 不作为接口用*/
int delete_file(char *path)
{
	struct _finddata_t dir_info;
	struct _finddata_t file_info;
	intptr_t f_handle;
	char tmp_path[_MAX_PATH];
	int result=0;
	if((f_handle = _findfirst(path, &dir_info)) != -1)
	{
		while(_findnext(f_handle, &file_info) == 0)
		{
			if(is_special_dir(file_info.name)==0)
				continue;
			
			if(IsDir(file_info)==0)
			{    
				get_file_path(path, file_info.name, tmp_path);
				result=delete_file(tmp_path);
				tmp_path[strlen(tmp_path) - 2] = '\0';
				if(_rmdir(tmp_path) == -1)
				{
					WriteLog(LOGLVL,"Err! Delete tmp_path [%s] dir Fail !",tmp_path);
					result=-1;
				}
			}
			else
			{
				strcpy(tmp_path, path);
				tmp_path[strlen(tmp_path) - 1] = '\0';
				strcat(tmp_path, file_info.name);
				if(RmFile(tmp_path) !=0)
				{
					WriteLog(LOGLVL,"Err! Delete tmp_path [%s] File Fail !",tmp_path);
					result=-1;
				}
			}
		}
		_findclose(f_handle);
	}
	else
	{
		WriteLog(LOGLVL,"Err! Open Dir Fail!");
		result=-1;
	}
	return result;
}

/* 递归复制目录  非接口模式*/
/* Add in 20120801*/
/* 参数一：原路径 后面必须带有\* */
/* 参数二：目标路径，最后面的必须和原路径最后一层相同 */
/* 参数三：是否只复制目录树 0--目录树 1--复制整个目录*/
/* 返回 0--成功 -1--失败*/
int copy_dir_list(char *path,char *despath,int dirtree)
{
	long Handle;
	char tmppath[MAX_PATH];
	char tmpdespath[MAX_PATH];
	struct _finddata_t FileInfo;
	
	memset(&FileInfo,0x00,sizeof(struct _finddata_t));
	
	if((Handle=_findfirst(path,&FileInfo))==-1L)
	{
		WriteLog(LOGLVL,"Err! 目录找不到--[%s]",path);
		return -1;
	}
	else
	{
		mkdir(despath);
		if(IsDir(FileInfo)==0)
		{
			if(is_special_dir(FileInfo.name)!=0)
            		{
				get_file_path(path, FileInfo.name, tmppath);
				get_next_path(despath,FileInfo.name,tmpdespath);
				copy_dir_list(tmppath,tmpdespath,dirtree);
			}
		}
		else
		{
			if(dirtree==1)
			{
				if(cpy_file(path,FileInfo.name,despath)!=0)
				{
					WriteLog(LOGLVL,"Err! 复制文件失败-- from [%s] to [%s],filename is [%s]",path,despath,FileInfo.name);
				}
			}
		}
		memset(&FileInfo,0x00,sizeof(struct _finddata_t));
		while( _findnext(Handle,&FileInfo)==0)
		{
			if(IsDir(FileInfo)==0)
			{
				if(is_special_dir(FileInfo.name)!=0)
                		{
					get_file_path(path, FileInfo.name, tmppath);
					get_next_path(despath,FileInfo.name,tmpdespath);
					copy_dir_list(tmppath,tmpdespath,dirtree);
				}
			}
			else
			{
				if(dirtree==1)
				{
					if(cpy_file(path,FileInfo.name,despath)!=0)
					{
						WriteLog(LOGLVL,"Err! 复制文件失败-- from [%s] to [%s],filename is [%s]",path,despath,FileInfo.name);
					}
				}
			}
			memset(&FileInfo,0x00,sizeof(struct _finddata_t));
		}
		_findclose(Handle);
	}
	return 0; 
}

/* 删除目录 0- 成功 -1 失败*/
/* 接口*/
int RemoveDir(char *dirpath)
{
	int rec=0,result=0;
	DWORD dw1=0,dw2=0,dwres=0;
	char nextpath[MAX_PATH];
	char tmpstr[10];
	
	if(FORCEDEAL==0)
	{
		REINPUT:
		printf("Delete Dir -- %s ?(Yes/No)",dirpath);
		memset(tmpstr,0x00,sizeof(tmpstr));
		fgets(tmpstr,sizeof(tmpstr),stdin);
		if(strlen(tmpstr)==0)
			goto REINPUT;
		if(strcmp(tmpstr,"\n")==0)
			goto REINPUT;
		strrep(tmpstr,"\n","");
		if((strcasecmp(tmpstr,"yes")==0)||(strcasecmp(tmpstr,"y")==0))
		{
			goto REALDEL;
		}
		else if((strcasecmp(tmpstr,"no")==0)||(strcasecmp(tmpstr,"n")==0))
		{
			return 0;
		}
		else
		{
			goto REINPUT;
		}
		
	}
	REALDEL:
	memset(nextpath,0x00,sizeof(nextpath));
	sprintf(nextpath,"%s\\*",dirpath);
	WriteLog(LOGLVL,"Now Begin Remove Dir -- [%s]",nextpath);
	dw1=GetTickCount();
	rec=delete_file(nextpath);
	if(rec==0)
	{
		if(_rmdir(dirpath) == -1)
		{
			WriteLog(LOGLVL,"Err! Delete dirpath dir --[%s] Fail !",dirpath);
			result=-1;
		}
		else
		{
			dw2=GetTickCount();
			dwres=dw2-dw1;
			WriteLog(LOGLVL,"Remove Dir [%s] Successfully! And Time consuming [%d] milliseconds.",dirpath,dwres);
			result=0;
		}
	}
	else
	{
		result=-1;
	}
	return result;
}

/* 复制目录  接口模式*/
/* Add in 20120801*/
/* 参数一：原路径 最后一层为需要复制的目录 */
/* 参数二：目标路径，不需要加最后一层，如果目标路径不存在，则会被创建 */
/* 参数三：是否只复制目录树 0--目录树 1--复制整个目录*/
/* 返回 0--成功 -1--失败*/
int CopyDir(char *path,char *path2,int dirtree)
{
	char soupath[MAX_PATH];
	char despath[MAX_PATH];
	DWORD dw1=0,dw2=0,dwres=0;
	memset(soupath,0x00,sizeof(soupath));
	memset(despath,0x00,sizeof(despath));
	
	dw1=GetTickCount();
	if(path[strlen(path)-1]=='\\')
	{
		path[strlen(path)-1]=='\0';
	}
	if(path2[strlen(path2)-1]=='\\')
	{
		path2[strlen(path2)-1]=='\0';
	}
	sprintf(soupath,"%s\\*",path);
	if(strcon(path,"\\")==0)
	{
		sprintf(despath,"%s\\%s",path2,SubString(path,LastIndexof(path,'\\')+1,strlen(path)-LastIndexof(path,'\\')-1));
	}
	else
	{
		if(path[1]==':')
		{
			sprintf(despath,"%s\\%s",path2,SubString(path,0,1));
		}
		else
		{
			WriteLog(LOGLVL,"Err! Path is Wrong [%s]",path);
			LogFlush();
			return -1;
		}
	}
	if(dirtree!=0)
		dirtree=1;
	CreateDir(despath);
	if(copy_dir_list(soupath,despath,dirtree)!=0)
	{
		WriteLog(LOGLVL,"Copy Dir Fail! southpath is [%s],despath is [%s],and dirtree is [%d]",soupath,despath,dirtree);
		LogFlush();
		return -1;
	}
	else
	{
		dw2=GetTickCount();
		dwres=dw2-dw1;
		WriteLog(LOGLVL,"Copy Dir Successfully! southpath is [%s],despath is [%s],and dirtree is [%d]",soupath,despath,dirtree);
		WriteLog(LOGLVL,"Copy Dir Time consuming [%d] milliseconds.",dwres);
	}
	LogFlush();
	return 0;
}

/* 删除EXE本身 --程序自删除 */
int DelAppSelf()
{
	char cmdbuf[MAX_PATH+20];

	/*设置程序为实时执行，快速退出*/
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	/*通知资源管理器不显示本程序*/
	/*当然如果程序没有真正的删除，刷新资源管理器后仍会显示出来的*/
	SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, _pgmptr, NULL);
	WriteLog(LOGLVL,"EXE File Name is [%s]",_pgmptr);

	/*调用cmd传入参数以删除自己*/
	sprintf(cmdbuf, "/c del /q %s", _pgmptr);
	WriteLog(LOGLVL,"Delete EXE cmd bufline is [%s]",cmdbuf);
	WriteLog(LOGLVL,"Now Application Will Delete self...");
	LogFlush();
	ShellExecute(NULL,"open","cmd.exe",cmdbuf,NULL,SW_HIDE);

	/*结束进程*/
	ExitProcess(0);
}

/*第七部分--END*/






/*第八部分--BEGIN*/
/*注册表处理*/


/*添加某个程序到右键菜单*/
/*注意：此选项默认添加到*下面*/
/*参数一为要在右键菜单中显示的名字*/
/*参数二为点击改名字需要执行的命令 使用%1 代表点击的文件名*/
/*返回0 为成功 -1为失败*/
int AddRightKey(char *showname,char *command)
{
	HKEY hkResult;
	char regname[100];
	memset(regname,0x00,sizeof(regname));
	
	if((strlen(showname)==0)||(strlen(command)==0))
		return -1;
	sprintf(regname,"*\\shell\\%s\\command",showname);
	
	/*创建注册表的键*/
	int ret=RegCreateKey(HKEY_CLASSES_ROOT,(LPCSTR)regname,&hkResult);
	if(ret != ERROR_SUCCESS)
	{
		return -1;
	}
	ret=RegSetValueEx(hkResult,NULL,0,REG_SZ,(byte *)command,strlen(command));
	if(ret==0)
	{
	        RegCloseKey(hkResult);
	}
	else
	{
	        RegCloseKey(hkResult);
	        return -1;
	}
	return 0;
}

/*删除文件右键菜单中的某项--只对自己新建的有效*/
/*注意：此选项默认删除到*下面shell*/
/*参数一为要在右键菜单中删除的名字*/
/*返回0 为成功 -1为失败*/
int DelRightKey(char *delname)
{
	int ret=0;
	HKEY hkResult;
	char lpFilename[MAX_PATH];
	char regname[MAX_PATH];
	
	/*第一步  删除command子键*/
	memset(regname,0x00,sizeof(regname));
	memset(lpFilename,0x00,sizeof(lpFilename));
	sprintf(regname,"*\\shell\\%s",delname);
	strcpy(lpFilename,"command");
	hkResult=NULL;
	ret=RegOpenKey(HKEY_CLASSES_ROOT,(LPCSTR)regname,&hkResult);
	if(ret != ERROR_SUCCESS)
	{
		return -1;
	}
	ret=RegDeleteKey(hkResult,(LPCSTR)lpFilename);
	if(ret==0)
	{
		RegCloseKey(hkResult);
	}
	else
	{
		RegCloseKey(hkResult);
		return -1;
	}
	
	/*第二步  删除名称键*/
	memset(regname,0x00,sizeof(regname));
	memset(lpFilename,0x00,sizeof(lpFilename));
	strcpy(regname,"*\\shell");
	strcpy(lpFilename,delname);
	hkResult=NULL;
	ret=RegOpenKey(HKEY_CLASSES_ROOT,(LPCSTR)regname,&hkResult);
	if(ret != ERROR_SUCCESS)
	{
		return -1;
	}
	ret=RegDeleteKey(hkResult,(LPCSTR)lpFilename);
	if(ret==0)
	{
		RegCloseKey(hkResult);
	}
	else
	{
		RegCloseKey(hkResult);
		return -1;
	}	
	return 0;
}

/*第八部分--END*/






/*第九部分--BEGIN*/
/*网络函数相关*/


/* Get Html Retun From Url */
int geturl(char *url, char *myfanhui)
{
	WSADATA WSAData={0};
	SOCKET sockfd;
	struct sockaddr_in addr;
	struct hostent *pURL;
	char myurl[MYBUFSIZ];
	char *pHost = 0, *pGET = 0;
	char host[MYBUFSIZ], GET[MYBUFSIZ];
	char header[MYBUFSIZ] = "";
	static char text[MYBUFSIZ];
	int i;
	int number,recvlen;
	int dizhi;
	int Mystrlen;
	
	/*windows下使用socket必须用WSAStartup初始化，否则不能调用*/
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
	{
		printf("WSA failed\n");
		return;
	}
	
	/*分离url中的主机地址和相对路径*/
	strcpy(myurl, url);
	for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost);
		if ( (int)(pHost - myurl) == strlen(myurl) )
			strcpy(GET, "/");
		else
			strcpy(GET, pHost);
	*pHost = '\0';
	strcpy(host, myurl);
	
	/*设定socket参数,并未真正初始化*/
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	pURL = gethostbyname(host);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
	addr.sin_port = htons(80);
	
	/*组织发送到web服务器的信息,为何要发送下面的信息请参考HTTP协议的约定*/
	strcat(header, "GET ");
	strcat(header, GET);
	strcat(header, " HTTP/1.1\r\n");
	strcat(header, "HOST: ");
	strcat(header, host);
	strcat(header, "\r\nConnection: Close\r\n\r\n");
	
	/*连接到服务器，发送请求header，并接受反馈（即网页源代码）*/
	connect(sockfd,(SOCKADDR *)&addr,sizeof(addr));
	send(sockfd, header, strlen(header), 0);
	number=0;
	recvlen=0; /*返回信息大小*/
	dizhi=0;
	Mystrlen=0;
	Mystrlen=recv(sockfd, text, MYBUFSIZ, 0);
	while ( Mystrlen > 1)
	{
		recvlen=recvlen+Mystrlen;
		if (number==0)
		{
			memcpy(myfanhui,text,Mystrlen);
			dizhi=(int)myfanhui;
			dizhi=dizhi+Mystrlen;
		}
		else
		{
			memcpy((PVOID)dizhi,text,Mystrlen);
			dizhi=dizhi+Mystrlen;
		}
		number=number+1;
		memset(text,0,MYBUFSIZ);
		Mystrlen=recv(sockfd, text, MYBUFSIZ, 0);
	}
	closesocket(sockfd);
	WSACleanup();
	return 0;
}

/*得到外网IP*/
char *GetPublicIP()
{
	int n1=0,n2=0;
	char result[MYBUFSIZ];
	char static ip[20];
	char *str1=(char *)malloc(MYBUFSIZ);
	memset(str1,0x00,MYBUFSIZ);
	char url[MYBUFSIZ];
	memset(url,0x00,MYBUFSIZ);
	strcpy(url,GetConfig("ipurl"));
	geturl(url,str1);
	memset(result,0x00,sizeof(result));
	memset(ip,0x00,sizeof(ip));
	strncpy(result,str1,sizeof(result));
	n1=Indexof(result,'[');
	n2=Indexof(result,']');
	sprintf(ip,"%s",SubString(result,n1+1,n2-n1-1));
	free(str1);
	return ip;
}

/*第九部分--END*/
