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





/*�궨�岿��--BEGIN*/


/*����������*/
#define MAXGDBCOUNT 200

/*���Ժ����õ���ͨ�ò���*/
#define GDB __FILE__,__FUNCTION__,__LINE__

/* ��ǰEXE�ļ��ľ���·���������ļ����� */
#define __EXE__ _pgmptr

/* Get Html Return Bufsize*/
#define MYBUFSIZ 1024

/*WriteLog Source File And Line NUM*/
#define LOGLVL __FILE__,__LINE__

/*�����������*/
#define LOG_MAXBUFFNUM 200

/*��������س���*/
#define LOG_MANBUFFLEN 30960

/* �����˳�ģʽ���� */
#define APP_PROMPT 0x01
#define APP_WINDOWS 0x02
#define APP_CHINESE 0x04

/* �����ļ���ʱ��·���������� */
#define MAX_DIRDEEP 100

/*�궨�岿��--END*/





/*ȫ�ֱ�������--BEGIN*/


/* �Ƿ�ǿ�ƴ���*/
/* �����ļ�ʱ���Ƿ���д��0-��ʾ 1-ֱ�Ӹ���*/
/* ɾ���ļ�ʱ���Ƿ���ʾ��0-��ʾ 1-ֱ��ɾ��*/
int FORCEDEAL=0;

/* ����/ɾ���ļ�ʱ���Ƿ���ʾ��ϸ��Ϣ */
/* 0-����ʾ��1-printf����̨��ʾ 2-Writelogд���ļ� 3-���߶�����*/
int SHOWDEALINFO=0;

/*ETC File*/
char CONFIG_NAME[MAX_PATH]="\%MOONHOME\%\\Etc\\MoonTalk.cfg";

/*��־�ļ���*/
char LOG_FILE[MAX_PATH]="";

/*��־���ݻ����*/
char LOG_BUFF[LOG_MAXBUFFNUM][LOG_MANBUFFLEN];

/*��ǰ����ظ���*/
int LOG_BUFFNOWNUM=0;

/*��־���� 0-�� ����-�� Ĭ�Ͽ�*/
int LOG_BUTTON=1;

/* WeekDay��Ӣ�ı�־ chinese or english */
char WEEK_LANG_TYPE[10]="chinese";

/* ����ʼʱ�� �Ǹ���CpyLogFile������¼�� */
DWORD APPTIMESTART=0;

/*�洢������Ϣ�Ľṹ��*/
struct TEST_GDB
{
	char func[50];
	int linenum;
	int count;
} test_gdb[MAXGDBCOUNT];

/*��ǰ���Ե�COUNT*/
int NOWGDBCOUNT=0;

/*ȫ�ֱ�������--END*/



/* ����Ԥ���岿��--BEGIN */
int WriteLog(char *zhufile,int lnum,char *fmt,...);
int LogFlush();
/* ����Ԥ���岿��--END */






/*����ͨ�ò���--BEGIN*/



/*Add in 20120818*/
/*������Ժ�����ֻ��Ҫ����궨�����GDB����*/
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
/* ����Ϊ�˳�ģʽ APP_PROMPT|APP_WINDOWS|APP_CHINESE */
/* APP_PROMPT �˳�ǰ��ʾ */
/* APP_WINDOWS MESSAGEBOX��ʽ��ʾ��Ĭ��Ϊ����̨��ʾ */
/* APP_CHINESE ������ʾ��Ĭ��ΪӢ�� */
/* 0-ֱ���˳� 1-Ĭ�Ͽ���̨Ӣ����ʾ */
/* 3-����Ӣ����ʾ 5-����̨������ʾ 7-����������ʾ */
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
				printf("\n����������˳�����...");
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
				MessageBox(NULL,"���OK��ť�˳�Ӧ�ó���","�˳�",MB_OK|MB_ICONINFORMATION);
			}
		}
	}
	exit(0);
}


/*����ͨ�ò���--END*/







/*��һ����--BEGIN*/
/*�ַ������������*/




/*�ж��ַ��ǲ������ں���*/
/*0--���� ����--���Ǻ���*/
int IsChinese(char c)
{
	if(~(c >> 8) == 0)
	{
		return 0;
	}
	return -1;
}

/*������0-9ת��Ϊ������-��*/
/*Add in 20120705 ��ũ��������������*/
char *GetHanZi(int n)
{
	static char result[3];
	memset(result,0x00,sizeof(result));
	switch (n)
	{
		case 0:strcpy(result,"��");break;
		case 1:strcpy(result,"һ");break;
		case 2:strcpy(result,"��");break;
		case 3:strcpy(result,"��");break;
		case 4:strcpy(result,"��");break;
		case 5:strcpy(result,"��");break;
		case 6:strcpy(result,"��");break;
		case 7:strcpy(result,"��");break;
		case 8:strcpy(result,"��");break;
		case 9:strcpy(result,"��");break;
		default:strcpy(result,"");break;
	};
	return result;
}

/*�ж�һ���ַ����ǲ������ִ�*/
/*0--�����ִ�  ����--�������ִ�*/
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

/*ȥ���ַ����ұߵĿո�*/
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

/*ȥ���ַ�����ߵĿո�*/
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

/*ȥ���ַ������˵Ŀո�*/
char *  trim(char *str)
{
	ltrim(str);
	rtrim(str);
	return(str);
}

/*Add in 201204*/
/*�����ַ���str�е�һ������char c��λ�ã����������±꣬û�з���-1 */
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
/*�����ַ���str�����һ��������char c��λ�ã����������±꣬û�з���-1 */
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
/* �˺���û���κ����� */
/* Ч��C# SubString ����������Բ�ˬ */
/* �ַ�����ȡ������ֵΪ��ȡ�Ĳ��֣�str���䣬iΪ��ʼλ���±꣬nΪ��ȡ���� */
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

/* add in 20120801 ��ԭ����StrContain�ģ��൱��StrContain(str1,str2,"matchcase") */
/* ���ִ�Сд*/
/* ȷ��str1�Ƿ����str2������Ϊ-1˵�������ڣ�����0Ϊ����  */
int strcon(char *str1,char *str2)
{
	char *p;
	p=NULL;
	p=strstr(str1,str2);
	if(p!=NULL)
		return 0;
	return -1;
}

/* add in 20120801 ��ԭ����StrContain�ģ��൱��StrContain(str1,str2,"-i") */
/* �����ִ�Сд*/
/* ȷ��str1�Ƿ����str2������Ϊ-1˵�������ڣ�����0Ϊ����  */
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
/* ���ִ�Сд*/
/* �滻�ַ���source��str1Ϊstr2��ȫ���滻*/
/* ����ѭ���滻������is--this �滻Ϊthis ֮���is�����滻*/
/* ��str2Ϊ��ʱ����ȥ��str1*/
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
/* �����ִ�Сд*/
/* �滻�ַ���source��str1Ϊstr2��ȫ���滻*/
/* ����ѭ���滻������is--this �滻Ϊthis ֮���is�����滻*/
/* ��str2Ϊ��ʱ����ȥ��str1*/
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

/* �ָ��ַ��� */
/* ����һ��Դ�ַ��� */
/* ��������ǰ��Ĳ��� */
/* ������������Ĳ��� */
/* �����ģ��ָ�� char���� */
/* �����壺�ڼ����ָ��� ������ʾ�Ӻ�ʼ */
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
/*ȥ���ַ����м�Ŀո�--�����ߵĲ�����*/
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
/*��С��99999������ת���ɺ�����ʽ*/
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
		return "��";
	}
	if(ncount<0)
	{
		strcpy(result,"��");
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
				case 1:if(tmpnum[i]==0){strcat(result,"��");}else{if((tmpnum[i]==1)&&(i==(k-1))){strcat(result,"ʮ");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"ʮ");}}break;
				case 2:if(tmpnum[i]==0){strcat(result,"��");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"��");}break;
				case 3:if(tmpnum[i]==0){strcat(result,"��");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"ǧ");}break;
				case 4:if(tmpnum[i]==0){strcat(result,"��");}else{strcat(result,GetHanZi(tmpnum[i]));strcat(result,"��");}break;
			};
		}
	}
	while(strcon(result,"����")==0)
	{
		strrep(result,"����","��");
	}
	len=strlen(result);
	if(len>=4)
	{
		if(strcmp(SubString(result,len-2,2),"��")==0)
		{
			strcpy(result,SubString(result,0,len-2));
		}
	}
	return result;
}

/*��һ����--END*/






/*�ڶ�����--BEGIN*/
/*ʱ�䡢���ڴ�����*/


/*�õ���ǰϵͳʱ��--Сʱ ��ʽΪHH*/
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

/*�õ���ǰϵͳʱ��--���� ��ʽΪMM*/
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

/*�õ���ǰϵͳʱ��--�� ��ʽΪSS*/
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

/*�õ���ǰϵͳʱ����� ��ʽΪint MIS*/
int GetSysMilli()
{
	int miltime=0;
	static char str[20];
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	miltime=sysTime.wMilliseconds;
	return miltime;
}

/*�õ���ǰϵͳ������� ��ʽΪYYYY*/
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

/*�õ���ǰϵͳ�����·� ��ʽΪMM*/
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

/*�õ���ǰϵͳ������ ��ʽΪDD*/
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

/*�õ���ǰϵͳʱ�� ��ʽΪHHMMSS*/
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

/*�õ���ǰϵͳʱ�� ��ȷ�����뼶 ��ʽΪHHMMSS.MIS*/
char *GetSysMilTime()
{
	static char str[20];
	SYSTEMTIME   sysTime;
	GetLocalTime(&sysTime);
	sprintf(str,"%02d%02d%02d.%03d",sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
	return(str);
}

/*�õ���ǰϵͳ���� ��ʽΪYYYYMMDD*/
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

/*�õ���ǰϵͳ���� ��ʽΪYYYY.MM.DD*/
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

/*�õ���ǰϵͳ����ʱ�� ��ʽΪYYYYMMDDHHMMSS*/
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

/*�õ���ǰϵͳ����ʱ�� ��ʽΪYYYYMMDDHHMMSS.MIL*/
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

/*�õ���ǰϵͳ����ʱ�� ��ʽΪYYYYMMDDHHMMSS.minutes*/
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

/* �õ�ϵͳʱ�䣬��ʽΪYYYY.MM.DD HH:MM:SS */
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

/*�õ���ǰϵͳ����ʱ�� ��ʽΪYYYY.MM.DD HH:MM:SS.MIL*/
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

/* �ж��ǲ������� -1 ƽ��  0 ���� */
int RunNian(int year)
{
	/* return -1 ƽ��  0 ����*/
	if(((year%4==0)&&(year%100!=0))||(year%400==0))
		return 0;
	else return -1;
}

/*�жϹ��������Ƿ���ȷ �����ϳ���*/
/*��������λ�������� YYYYMMDD*/
/*���أ�0--��ȷ  -1--����ȷ*/
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


/*�ж�ũ�������Ƿ���ȷ �����ϳ���*/
/*��������λũ������ YYYYMMDD �� YYYYRMMDD*/
/*���أ�0--��ȷ  -1--����ȷ*/
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


/*�ж�ʱ���Ƿ���ȷ �����ϳ���*/
/*��������λʱ�� HHMMSS*/
/*���أ�0--��ȷ  -1--����ȷ*/
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

/* ����һ��ʱ�䵽00:00:00�������������ʽΪHHMMSS */
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

/* ���ؾ��� 1900.1.1 ������(����Ϊ����) ������ʽΪ:YYYYMMDD */
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

/* �õ�����ʱ��������֮�� ������ʽ��Ϊ:HHMMSS  */
int GetTimeMiaoCha(char *time1,char *time2)
{
	int summiao=0;
	summiao=GetMiaoChaFromBase(time1)-GetMiaoChaFromBase(time2);
	return summiao;
}

/* �˺�����Ϊ���ã����ؽ������Ϊ���� */
/* �õ���������֮��������� ������ʽΪYYYYMMDD */
int GetDayCha(char *date1,char *date2)
{
	int sumday=0;
	sumday=GetDayChaFromBase(date1)-GetDayChaFromBase(date2);
	return sumday;
}

/* �õ�ĳ��ʱ��㵽��ǰϵͳ����������Է��ظ��� ������ʽΪ:YYYYMMDD,HHMMSS */
/*�˺��������⣬�������������̫Զʱ������������Ա�������������ȷ������*/
/*Ŀǰֻ����S.c ��R.c��ʹ��������������ҿ���ȷ�����������*/
int GetMiaoChaFromSys(char *date,char *time)
{
	int summiao=0;
	summiao=GetDayCha(date,GetSysDate())*24*60*60+GetTimeMiaoCha(time,GetSysTime());
	return summiao;
}

/* �õ�����ʱ���֮��������� �����ʽΪ:YYYYMMDD,HHMMSS */
/*����������ϸ���������һ��������û��ʹ�øú������ļ�*/
/*���ڰ������������Ϊ�����������Ȼ���Ƿ���double���͵�*/
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
/*�ж�һ������dt2�Ƿ�����������dt1(С)��dt3(��)֮��,��ʽ��Ϊ��׼8λ*/
/*���ؽ��Ϊ0˵���ڣ�����-1˵�����ڣ�������������˵�*/
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

/* �õ�ϵͳ����ʱ�䣬��ʽΪYYYY.MM.DD HH:MM:SS */
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

/* �õ����� */
/* ����һ����׼���� YYYYMMDD */
/* �����������ӻ��߼��ٵ�����������Ϊ���� */
/* ���ؽ�������� YYYYMMDD */
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
/*��һ����׼����Ϊ����������һ�����������õ�һ������*/
/*ѭ��������Ϊ������ӣ�ֻ���������*/
/*����sourceΪ��׼���ڣ�addsecondΪҪ�ӵ�������numΪѭ�����������Ե����㣬numΪ����ʱ��ʾ���*/
/*���ؽ��Ϊ���֮������ڣ�source��result�ĸ�ʽ��ΪYYYYMMDDHHMMSSMIL*/
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
	
	
	/*�õ�һ����������ľ����졢ʱ���֡��롢����*/
	i=addsecond;
	lday=addsecond/86400;
	lhour=(addsecond-86400*lday)/3600;
	lminute=(addsecond-86400*lday-3600*lhour)/60;
	lsecond=addsecond-86400*lday-3600*lhour-60*lminute;
	lmils=(addsecond-i)*1000;
	
	
	/*��ʼ��basedΪ��׼����*/
	memset(based,0x00,sizeof(based));
	memset(result,0x00,sizeof(result));
	strncpy(based,source,sizeof(based));
	
	if(num<0)
	{
		num=-num;
		for(i=0;i<num;i++)
		{
			/*����based��ȥһ������ӵ�еĵ�������*/
			memset(olddate,0x00,sizeof(olddate));
			memset(newdate,0x00,sizeof(newdate));
			strncpy(olddate,SubString(based,0,8),sizeof(olddate));
			strncpy(newdate,GetDate(olddate,-lday),sizeof(newdate));
			memset(olddate,0x00,sizeof(olddate));
			strncpy(olddate,SubString(based,8,9),sizeof(olddate));
			memset(based,0x00,sizeof(based));
			sprintf(based,"%s%s",newdate,olddate);
			
			
			/*ʱ������밴˳�����*/
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
			/*���õ�һ����һ���������based*/
			memset(based,0x00,sizeof(based));
			sprintf(based,"%08s%02d%02d%02d%03d",newdate,nhour,nminute,nsecond,nmilsec);
			
			/*ѭ����β��ÿѭ��һ�μ�һ������*/
		}
	}
	else
	{
		for(i=0;i<num;i++)
		{
			/*����based����һ������ӵ�еĵ�������*/
			memset(olddate,0x00,sizeof(olddate));
			memset(newdate,0x00,sizeof(newdate));
			strncpy(olddate,SubString(based,0,8),sizeof(olddate));
			strncpy(newdate,GetDate(olddate,lday),sizeof(newdate));
			memset(olddate,0x00,sizeof(olddate));
			strncpy(olddate,SubString(based,8,9),sizeof(olddate));
			memset(based,0x00,sizeof(based));
			sprintf(based,"%s%s",newdate,olddate);
			
			
			/*ʱ������밴˳���*/
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
			/*���õ�һ����һ���������based*/
			memset(based,0x00,sizeof(based));
			
			sprintf(based,"%08s%02d%02d%02d%03d",newdate,nhour,nminute,nsecond,nmilsec);
			/*ѭ����β��ÿѭ��һ�μ�һ������*/
		}
	}
	strncpy(result,based,sizeof(result));
	return result;
}

/* �õ��������ڵ����ڣ����ش�����һ�������յĺ��� */
/* typeΪchineseʱ�õ����ķ��أ�ռ6���ֽ�,��������Ӣ��,��ռ5���ֽ� */
/* 20120705 ��������һ���㷨����Ϊʹ����ͨ�㷨��ʱ��С��1980�����㲻���� */
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
			case 0:sprintf(str,"������");break;
			case 1:sprintf(str,"����һ");break;
			case 2:sprintf(str,"���ڶ�");break;
			case 3:sprintf(str,"������");break;
			case 4:sprintf(str,"������");break;
			case 5:sprintf(str,"������");break;
			case 6:sprintf(str,"������");break;
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
		/*����ĳһ�������*/
		/*������ƽ�������󲻳��������Ļ�����ô���ô˰취*/
		/*����ǧ������һ��һ����������Ϊ����*/
		/*���û����취������*/
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
					case 0:strcpy(str,"������");break;
					case 1:strcpy(str,"������");break;
					case 2:strcpy(str,"����һ");break;
					case 3:strcpy(str,"���ڶ�");break;
					case 4:strcpy(str,"������");break;
					case 5:strcpy(str,"������");break;
					case 6:strcpy(str,"������");break;
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
					case 0:strcpy(str,"������");break;
					case 1:strcpy(str,"������");break;
					case 2:strcpy(str,"������");break;
					case 3:strcpy(str,"������");break;
					case 4:strcpy(str,"���ڶ�");break;
					case 5:strcpy(str,"����һ");break;
					case 6:strcpy(str,"������");break;
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

/*�ڶ�����--END*/






/*��������--BEGIN*/
/*�������*/


/*20120709 add*/
/*�õ���ʽΪHHMMSSMIL��λ�����������*/
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
/*����һ��numλ���ȵ�����������ַ�������ʽ����*/
/*�˺��������Ժ���Ϊ��λ�����ԣ��벻Ҫ��һ�����ڵ������μ�����*/
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

/*��������--END*/





/*���Ĳ���--BEGIN*/
/*�ļ�����·������*/


/* ����·�������еĻ������� */
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
			sprintf(tmpstr,"�Ҳ�������������--%s",envstr);
			MessageBox(NULL,tmpstr,"����",MB_OK|MB_ICONERROR);
			AppExit(0);
		}
		strcaserep(source,repstr,getenv(envstr));
	}
	return source;
}

/*��׼���ļ����ƣ������·�����Ϊ����·��*/
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

/* �õ���׼�ļ��� */
/* ������ʽ��ȫ·�����ļ�������ȫ·�����ļ������ļ�����dot���ļ�������dot */
/* ���ؽ����������׺���ļ��� */
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

/*�õ���ǰEXE��·�����������ļ�����*/
char *GetExePath()
{
	static char result[MAX_PATH];
	memset(result,0x00,sizeof(result));
	strcpy(result,SubString(__EXE__,0,LastIndexof(__EXE__,'\\')));
	return result;
}

/*���Ĳ���--END*/






/*���岿��--BEGIN*/
/*�����ļ�����*/



/* �õ��ؼ��ʵ�ֵ source Ϊ�ؼ���*/
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
			sprintf(tmpstr,"�Ҳ������������ļ���--%s",CONFIG_NAME);
			MessageBox(NULL,tmpstr,"����",MB_OK|MB_ICONERROR);
		}
		else
		{
			sprintf(tmpstr,"�Ҳ���%s��ֵ��",source);
			MessageBox(NULL,tmpstr,"����",MB_OK|MB_ICONERROR);
		}
		AppExit(0);
	}
	else
	{
		ConvertEnv(result);
	}
	return result;
}

/* ���������ļ� ARGS Ϊ[KEYWPRD=VALUES]*/
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

/*���岿��--END*/





/*��������--BEGIN*/
/*д��־ģ��*/


/*��־���� 0-�� ����-��*/
int SetLogButton(int logstate)
{
	if(logstate!=0)
		logstate=1;
	LOG_BUTTON=logstate;
	return 0;
}

/*�建��أ��������������д����־�ļ�����������ĩβ����Ҫ��Ӹú���*/
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

/*д��־*/
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

/*��־��ʼ����������־�ļ������á���ʼ������ء���ǰ�������*/
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

/*��������--END*/






/*���߲���--BEGIN*/
/*�ļ����ļ��д���*/


/* �����ļ���--���Զ༶���� */
/* ����0�ɹ���-1ʧ�� */
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

/* �ж�Ŀ¼�Ƿ�Ϊ�� ������Ϊ�� .��..���������� */
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

/* �ж��Ƿ���".."Ŀ¼��"."Ŀ¼*/
/* 0--�� 1--��*/
/* �ǽӿ�*/
int is_special_dir(const char *path)
{
	if((strcmp(path,"..")==0)||(strcmp(path,".")==0))
		return 0;
	return -1;
}

/* �ж��ļ�������Ŀ¼�����ļ�--���������ļ���.��..*/
/* 0--Ŀ¼ 1--�ļ�*/
/* �ӿ�*/
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

/* Copy��delete Ŀ¼ʱ���õ�������Ϊ�ӿ���*/
/* �õ���һ��Ŀ¼��path*/
int get_file_path(char *path,char *filename,char *filepath)
{
	memset(filepath,0x00,sizeof(filepath));
	strcpy(filepath, path);
	filepath[strlen(filepath) - 1] = '\0';
	strcat(filepath, filename);
	strcat(filepath, "\\*");
	return 0;
}

/* copydir�ã�����Ϊ�ӿ�*/
/* �õ���һ��Ŀ��·��*/
int get_next_path(char *path,char *filename,char *filepath)
{
	memset(filepath,0x00,sizeof(filepath));
	sprintf(filepath,"%s\\%s",path,filename);
	return 0;
}

/*ɾ���ļ� 0-�ɹ� -1-ʧ��*/
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

/* �����ļ�����������Ϊȫ·�� �ӿ� */
/* 0-�ɹ� -1ʧ�� */
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

/* copydir�ã�����Ϊ�ӿ�*/
/* �����ļ�*/
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

/* �ݹ�����Ŀ¼���ļ���ɾ��*/
/* ����Ϊ�ӿ���*/
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

/* �ݹ鸴��Ŀ¼  �ǽӿ�ģʽ*/
/* Add in 20120801*/
/* ����һ��ԭ·�� ����������\* */
/* ��������Ŀ��·���������ı����ԭ·�����һ����ͬ */
/* ���������Ƿ�ֻ����Ŀ¼�� 0--Ŀ¼�� 1--��������Ŀ¼*/
/* ���� 0--�ɹ� -1--ʧ��*/
int copy_dir_list(char *path,char *despath,int dirtree)
{
	long Handle;
	char tmppath[MAX_PATH];
	char tmpdespath[MAX_PATH];
	struct _finddata_t FileInfo;
	
	memset(&FileInfo,0x00,sizeof(struct _finddata_t));
	
	if((Handle=_findfirst(path,&FileInfo))==-1L)
	{
		WriteLog(LOGLVL,"Err! Ŀ¼�Ҳ���--[%s]",path);
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
					WriteLog(LOGLVL,"Err! �����ļ�ʧ��-- from [%s] to [%s],filename is [%s]",path,despath,FileInfo.name);
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
						WriteLog(LOGLVL,"Err! �����ļ�ʧ��-- from [%s] to [%s],filename is [%s]",path,despath,FileInfo.name);
					}
				}
			}
			memset(&FileInfo,0x00,sizeof(struct _finddata_t));
		}
		_findclose(Handle);
	}
	return 0; 
}

/* ɾ��Ŀ¼ 0- �ɹ� -1 ʧ��*/
/* �ӿ�*/
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

/* ����Ŀ¼  �ӿ�ģʽ*/
/* Add in 20120801*/
/* ����һ��ԭ·�� ���һ��Ϊ��Ҫ���Ƶ�Ŀ¼ */
/* ��������Ŀ��·��������Ҫ�����һ�㣬���Ŀ��·�������ڣ���ᱻ���� */
/* ���������Ƿ�ֻ����Ŀ¼�� 0--Ŀ¼�� 1--��������Ŀ¼*/
/* ���� 0--�ɹ� -1--ʧ��*/
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

/* ɾ��EXE���� --������ɾ�� */
int DelAppSelf()
{
	char cmdbuf[MAX_PATH+20];

	/*���ó���Ϊʵʱִ�У������˳�*/
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	/*֪ͨ��Դ����������ʾ������*/
	/*��Ȼ�������û��������ɾ����ˢ����Դ���������Ի���ʾ������*/
	SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, _pgmptr, NULL);
	WriteLog(LOGLVL,"EXE File Name is [%s]",_pgmptr);

	/*����cmd���������ɾ���Լ�*/
	sprintf(cmdbuf, "/c del /q %s", _pgmptr);
	WriteLog(LOGLVL,"Delete EXE cmd bufline is [%s]",cmdbuf);
	WriteLog(LOGLVL,"Now Application Will Delete self...");
	LogFlush();
	ShellExecute(NULL,"open","cmd.exe",cmdbuf,NULL,SW_HIDE);

	/*��������*/
	ExitProcess(0);
}

/*���߲���--END*/






/*�ڰ˲���--BEGIN*/
/*ע�����*/


/*���ĳ�������Ҽ��˵�*/
/*ע�⣺��ѡ��Ĭ����ӵ�*����*/
/*����һΪҪ���Ҽ��˵�����ʾ������*/
/*������Ϊ�����������Ҫִ�е����� ʹ��%1 ���������ļ���*/
/*����0 Ϊ�ɹ� -1Ϊʧ��*/
int AddRightKey(char *showname,char *command)
{
	HKEY hkResult;
	char regname[100];
	memset(regname,0x00,sizeof(regname));
	
	if((strlen(showname)==0)||(strlen(command)==0))
		return -1;
	sprintf(regname,"*\\shell\\%s\\command",showname);
	
	/*����ע���ļ�*/
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

/*ɾ���ļ��Ҽ��˵��е�ĳ��--ֻ���Լ��½�����Ч*/
/*ע�⣺��ѡ��Ĭ��ɾ����*����shell*/
/*����һΪҪ���Ҽ��˵���ɾ��������*/
/*����0 Ϊ�ɹ� -1Ϊʧ��*/
int DelRightKey(char *delname)
{
	int ret=0;
	HKEY hkResult;
	char lpFilename[MAX_PATH];
	char regname[MAX_PATH];
	
	/*��һ��  ɾ��command�Ӽ�*/
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
	
	/*�ڶ���  ɾ�����Ƽ�*/
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

/*�ڰ˲���--END*/






/*�ھŲ���--BEGIN*/
/*���纯�����*/


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
	
	/*windows��ʹ��socket������WSAStartup��ʼ���������ܵ���*/
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
	{
		printf("WSA failed\n");
		return;
	}
	
	/*����url�е�������ַ�����·��*/
	strcpy(myurl, url);
	for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost);
		if ( (int)(pHost - myurl) == strlen(myurl) )
			strcpy(GET, "/");
		else
			strcpy(GET, pHost);
	*pHost = '\0';
	strcpy(host, myurl);
	
	/*�趨socket����,��δ������ʼ��*/
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	pURL = gethostbyname(host);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
	addr.sin_port = htons(80);
	
	/*��֯���͵�web����������Ϣ,Ϊ��Ҫ�����������Ϣ��ο�HTTPЭ���Լ��*/
	strcat(header, "GET ");
	strcat(header, GET);
	strcat(header, " HTTP/1.1\r\n");
	strcat(header, "HOST: ");
	strcat(header, host);
	strcat(header, "\r\nConnection: Close\r\n\r\n");
	
	/*���ӵ�����������������header�������ܷ���������ҳԴ���룩*/
	connect(sockfd,(SOCKADDR *)&addr,sizeof(addr));
	send(sockfd, header, strlen(header), 0);
	number=0;
	recvlen=0; /*������Ϣ��С*/
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

/*�õ�����IP*/
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

/*�ھŲ���--END*/
