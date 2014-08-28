#include <stdio.h>
#include <string.h>
#include "mybase.h"
#include "mylunar.h"

#define MINLUNARYEAR 1900
#define MAXLUNARYEAR 8704

#define CLOSETYPE APP_PROMPT|APP_CHINESE

int ShowDiyCfgFile()
{
	printf("\n--------------------------����Ϊ�Զ�������ļ�DiyHoliday.cfg��ģ������--------------------------\n\n");
	printf("#\t������ũ�����Զ�����ջ�����������ļ�\n");
	printf("#\tGregorian Diy Holiday��Lunar Diy Holiday��������������ũ���Ĺؼ��У���Ҫ�޸ģ�������ɾ\n");
	printf("#\tʹ��#�ַ�����ע�͵�һ��\n");
	printf("#\t������ũ�����Զ�����ո��������ܳ���30��������30���Ľ���Ч\n");
	printf("#\t��ʽ��Ϊ��MMDD--����\n");
	printf("#\tMMDD��ʾ��λ�����գ�����������Ҫ����������ʾ�����ƣ����Ʋ��ܳ���8�����ֻ�16���ַ�\n");
	printf("#\t���ں������м�����������Ǳ���Ҫ�е�\n");
	printf("#\t���������ϸ�ʽ���Զ������Ϊ��Ч\n");
	printf("\n\n\n");
	printf("#\tGregorian Diy Holiday begin --This line connot modify or delete.\n");
	printf("0808--���˼�����\n");
	printf("\n\n\n\n");
	printf("#\tLunar Diy Holiday begin --This line connot modify or delete.\n");
	printf("1219--�ҵ�����\n\n");
	return 0;
}

int Help()
{
	printf("ũ��������1901��--8704�꡿��ũ������ת�����������ֲ�ѯ\n\n");
	printf("CAL [-L] [-G] [-B[:L/G]] [-DIY] [��[��[��]]]\n\n");
	printf("\t-L\t����������ת��Ϊ��Ӧ��ũ�����ڣ������λ���������磺YYYYMMDD.\n");
	printf("\t-G\t��ũ������ת��Ϊ��Ӧ�Ĺ������ڣ������ũ�����ڸ�ʽ��YYYYMMDD��YYYYRMMDD R��ʾ����.\n");
	printf("\t-B\t��ѯ�������֣�Ĭ�Ϲ����������ڣ���ʽΪYYYYMMDDHH��YYYYRMMDDHH  HHȡ00-23.\n");
	printf("\t\t:G  �����������ڣ���ʽ������YYYYMMDDHH.\n");
	printf("\t\t:L  ũ���������ڣ�ʹ��R���Ա�ʾ����.\n");
	printf("\t-DIY\t�鿴�Զ�����ա������������ļ�ģ��.\n\n");
	printf("��ʹ���κβ�����ʱ����Ĭ����ʾ�������ڵ���ϸ��Ϣ.\n");
	printf("��:CAL 2012��CAL 201208��CAL 20120818 ���ֱ���ʾ2012���ꡢ2012��8�¡�2012��8��18�յ�������Ϣ.\n");
	printf("�����Ҫ�Զ�����գ�������EXEĿ¼������ļ�DiyHoliday.cfg�ļ�������CAL -DIY���Բ鿴���ļ��ĸ�ʽ.\n");
	printf("�����������Ͽ��Լ���1901��--8704�����Ϣ�������Խ�����Ҳ��Խ��2300��֮ǰ������С��.\n");
	
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
		printf("����ʱ�����Ϸ���ֻ����0-23֮�䣡\n");
		printf("����CAL -help �ɲ鿴������\n");
		AppExit(CLOSETYPE);
	}
	strcpy(ganzhi,Get_ZB_BaZi(date));
	strcpy(wuxing,Get_ZB_WuXing(ganzhi));
	strcpy(nayin,Get_ZB_NaYin(ganzhi));
	strcpy(zhuming,SubString(wuxing,10,2));
	strcpy(que,"");
	if(strcon(wuxing,"��")!=0)
	{
		strcat(que,"��");
	}
	if(strcon(wuxing,"ľ")!=0)
	{
		strcat(que,"ľ");
	}
	if(strcon(wuxing,"ˮ")!=0)
	{
		strcat(que,"ˮ");
	}
	if(strcon(wuxing,"��")!=0)
	{
		strcat(que,"��");
	}
	if(strcon(wuxing,"��")!=0)
	{
		strcat(que,"��");
	}
	printf("��Ԫ���ڣ�%s\nũ�����ڣ�%s\n",SubString(date,0,8),ConvertGL_Info(SubString(date,0,8),"-l"));
	strrep(ganzhi," ","   ");
	strrep(wuxing," ","   ");
	printf("���֣�%s\n���У�%s\n������%s\n",ganzhi,wuxing,nayin);
	printf("����Ϊ%s��",zhuming);
	len=strlen(que);
	if(len==0)
	{
		printf("\n");
	}
	else if(len==2)
	{
		printf("������ȱ%s\n",que);
	}
	else if(len==4)
	{
		printf("������ȱ%s��%s\n",SubString(que,0,2),SubString(que,2,2));
	}
	else if(len==6)
	{
		printf("������ȱ%s��%s��%s\n",SubString(que,0,2),SubString(que,2,2),SubString(que,4,2));
	}
	else if(len==8)
	{
		printf("������ȱ%s��%s��%s��%s\n",SubString(que,0,2),SubString(que,2,2),SubString(que,4,2),SubString(que,6,2));
	}
	else if(len==10)
	{
		printf("������ȱ%s��%s��%s��%s��%s\n",SubString(que,0,2),SubString(que,2,2),SubString(que,4,2),SubString(que,6,2),SubString(que,8,2));
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
		/*���ڵĺϷ��Լ��*/
		if(isdigitstr(date)!=0)
		{
			printf("���ڲ��ܰ����������ַ���\n");
			printf("����CAL -help �ɲ鿴������\n");
			AppExit(CLOSETYPE);
		}
		
		if(len==8)
		{
			if(isdate(date)!=0)
			{
				printf("�������ڲ��Ϸ���\n");
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("ֻ�ܲ鿴%d�굽%d���������Ϣ��\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("����CAL -help �ɲ鿴������\n");
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
				printf("ֻ�ܲ鿴%d�굽%d���������Ϣ��\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			month=atoi(smonth);
			if((month>12)||(month<=0))
			{
				printf("�·ݱ�����1-12֮�䣡\n");
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			InitLunarCal(year);
			PrfCalendar(month);
			printf("\n�����ʾ��ʽ����������ʹ������\"%s %s >cal.txt\" �������ӡ��cal.txt�ļ��в鿴���ļ����������滻��\n",argv[0],argv[1]);
		}
		else if(len==4)
		{
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("ֻ�ܲ鿴%d�굽%d���������Ϣ��\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			InitLunarCal(year);
			PrfCalendar(year);
			printf("\n�����ʾ��ʽ����������ʹ������\"%s %s >cal.txt\" �������ӡ��cal.txt�ļ��в鿴���ļ����������滻��\n",argv[0],argv[1]);
		}
		else
		{
			printf("���ڳ��Ȳ���ȷ��\n");
			printf("����CAL -help �ɲ鿴������\n");
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
				printf("�������ڲ��Ϸ���\n");
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			memset(date,0x00,sizeof(date));
			strcpy(date,argv[2]);
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("ֻ�ܲ鿴%d�굽%d���������Ϣ��\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			PrfOneDay(date,"-g");
		}
		else if(strcasecmp(oprs,"-g")==0)
		{
			if(islunardate(argv[2])!=0)
			{
				printf("ũ�����ڸ�ʽ���Ϸ���ֻ��ΪYYYYMMDD��YYYYRMMDD��\n");
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
			memset(date,0x00,sizeof(date));
			strcpy(date,argv[2]);
			strcpy(syear,SubString(date,0,4));
			year=atoi(syear);
			if((year<=MINLUNARYEAR)||(year>MAXLUNARYEAR))
			{
				printf("ֻ�ܲ鿴%d�굽%d���������Ϣ��\n",MINLUNARYEAR,MAXLUNARYEAR);
				printf("����CAL -help �ɲ鿴������\n");
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
					printf("������ѯ����ʱ���������ڱ���Ϊ10λ--YYYYMMDDHH��\n");
					printf("����CAL -help �ɲ鿴������\n");
					AppExit(CLOSETYPE);
				}
				if(isdigitstr(date)!=0)
				{
					printf("������ѯ����ʱ���������ڲ��ܺ��з������ַ���\n");
					printf("����CAL -help �ɲ鿴������\n");
					AppExit(CLOSETYPE);
				}
				if(isdate(SubString(date,0,8))!=0)
				{
					printf("�����������ڲ��Ϸ���\n");
					printf("����CAL -help �ɲ鿴������\n");
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
					printf("ũ����ѯ����ʱ����������ֻ����10λ--YYYYMMDDHH ��11λ--YYYYRMMDDHH��\n");
					printf("����CAL -help �ɲ鿴������\n");
					AppExit(CLOSETYPE);
				}
				if(len==10)
				{
					if(isdigitstr(date)!=0)
					{
						printf("��������ʱ���������ڲ��ܺ��з������ַ���\n");
						printf("����CAL -help �ɲ鿴������\n");
						AppExit(CLOSETYPE);
					}
					if(islunardate(SubString(date,0,8))!=0)
					{
						printf("ũ���������ڲ��Ϸ���\n");
						printf("����CAL -help �ɲ鿴������\n");
						AppExit(CLOSETYPE);
					}
				}
				if(len==11)
				{
					if(islunardate(SubString(date,0,9))!=0)
					{
						printf("ũ���������ڲ��Ϸ���\n");
						printf("����CAL -help �ɲ鿴������\n");
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
				printf("�޴˲���ģʽ��\n");
				printf("����CAL -help �ɲ鿴������\n");
				AppExit(CLOSETYPE);
			}
		}
		else
		{
			printf("�޴˲���ģʽ��\n");
			printf("����CAL -help �ɲ鿴������\n");
			AppExit(CLOSETYPE);
		}
	}
	AppExit(CLOSETYPE);
}
