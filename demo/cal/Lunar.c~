/*
 *    ProgramName      : Lunar.c
 *
 *    Version          : 2.0
 *
 *    OS & Environment : Windows NT, ANSI C, MinGW Compiler
 *
 *    Description      : Lunar Function Libaray--Chinese Calendar
 *
 *    History          : 2012.08.18 Modify Structure Version 1.0--Lunar_1.0.c
 *
 *	Date		Position	Author		Description	Address
 * ----------------------------------------------------------------------------
 *	2012.07.07	All		Chen Yunlong	Creation	SuZhou
 *	2012.08.18	All		Chen Yunlong	Modify		SuZhou
 *
*/




//#include "mybase.h"

/*一个回归年的秒数，即两个相同节气的相隔时间，如春分到春分*/
#define LOOPYEAR 31556925.9747

/*一个朔望月的平均天数*/
#define SHUOWANG 29.5306

/*初始化农历天数最大值*/
#define MAXLUNARDAY 450

/*自定义公历、农历节日（纪念日）的最大个数*/
#define MAXDIYHOLIDAY 30


/*公元1900年的节气时间点*/
const char LUNARJQBASE_1900[24][20]={"19000204140200000",	/*立春*/
					"19000219101300000",	/*雨水*/
					"19000306083200000",	/*惊蛰*/
					"19000321094900000",	/*春分*/
					"19000405140100000",	/*清明*/
					"19000420213500000",	/*谷雨*/
					"19000506080100000",	/*立夏*/
					"19000521212100000",	/*小满*/
					"19000606124200000",	/*芒种*/
					"19000622054000000",	/*夏至*/
					"19000707230900000",	/*小暑*/
					"19000723163300000",	/*大暑*/
					"19000808084500000",	/*立秋*/
					"19000823231400000",	/*处暑*/
					"19000908110900000",	/*白露*/
					"19000923201500000",	/*秋分*/
					"19001009020700000",	/*寒露*/
					"19001024045300000",	/*霜降*/
					"19001108043800000",	/*立冬*/
					"19001123015100000",	/*小雪*/
					"19001207210100000",	/*大雪*/
					"19001222145000000",	/*冬至*/
					"19010106080500000",	/*小寒*/
					"19010121013000000"	/*大寒*/
					};
/*公元1950年的节气时间点*/
const char LUNARJQBASE_1950[24][20]={"19500204172100000",	/*立春*/
					"19500219131800000",	/*雨水*/
					"19500306113700000",	/*惊蛰*/
					"19500321123500000",	/*春分*/
					"19500405164600000",	/*清明*/
					"19500420235800000",	/*谷雨*/
					"19500506102500000",	/*立夏*/
					"19500521232500000",	/*小满*/
					"19500606144900000",	/*芒种*/
					"19500622073200000",	/*夏至*/
					"19500708010900000",	/*小暑*/
					"19500723182500000",	/*大暑*/
					"19500808105000000",	/*立秋*/
					"19500824011800000",	/*处暑*/
					"19500908132900000",	/*白露*/
					"19500923223800000",	/*秋分*/
					"19501009044700000",	/*寒露*/
					"19501024073800000",	/*霜降*/
					"19501108073900000",	/*立冬*/
					"19501123045600000",	/*小雪*/
					"19501208002540520",	/*大雪*/
					"19501222180700000",	/*冬至*/
					"19510106112500000",	/*小寒*/
					"19510121044800000" 	/*大寒*/
					};
/*公元1970年的节气时间点*/
const char LUNARJQBASE_1970[24][20]={"19700204135000000",	/*立春*/
					"19700219094700000",	/*雨水*/
					"19700308080000000",	/*惊蛰*/
					"19700321085800000",	/*春分*/
					"19700405125900000",	/*清明*/
					"19700420201300000",	/*谷雨*/
					"19700506062900000",	/*立夏*/
					"19700521193300000",	/*小满*/
					"19700606104500000",	/*芒种*/
					"19700622033600000",	/*夏至*/
					"19700707210300000",	/*小暑*/
					"19700723142800000",	/*大暑*/
					"19700808064600000",	/*立秋*/
					"19700823212500000",	/*处暑*/
					"19700908093100000",	/*白露*/
					"19700923185300000",	/*秋分*/
					"19701009010150370",	/*寒露*/
					"19701024040200000",	/*霜降*/
					"19701108035700000",	/*立冬*/
					"19701123012700000",	/*小雪*/
					"19701207204100000",	/*大雪*/
					"19701222144200000",	/*冬至*/
					"19710106075400000",	/*小寒*/
					"19710121012300000" 	/*大寒*/
					};
/*公元1980年的节气时间点*/
const char LUNARJQBASE_1980[24][20]={"19800205001020260",	/*立春*/
					"19800219195800000",	/*雨水*/
					"19800305181400000",	/*惊蛰*/
					"19800320190500000",	/*春分*/
					"19800404231000000",	/*清明*/
					"19800420061600000",	/*谷雨*/
					"19800505163600000",	/*立夏*/
					"19800521053100000",	/*小满*/
					"19800605205000000",	/*芒种*/
					"19800620133100000",	/*夏至*/
					"19800707070600000",	/*小暑*/
					"19800723002545260",	/*大暑*/
					"19800807165000000",	/*立秋*/
					"19800823072200000",	/*处暑*/
					"19800907193800000",	/*白露*/
					"19800923054500000",	/*秋分*/
					"19801008110900000",	/*寒露*/
					"19801023140800000",	/*霜降*/
					"19801107141300000",	/*立冬*/
					"19801122113600000",	/*小雪*/
					"19801207065900000",	/*大雪*/
					"19801222005510740",	/*冬至*/
					"19810105181200000",	/*小寒*/
					"19810120113600000" 	/*大寒*/
					};
/*公元1990年的节气时间点*/
const char LUNARJQBASE_1990[24][20]={"19900204101800000",	/*立春*/
					"19900219061700000",	/*雨水*/
					"19900306042200000",	/*惊蛰*/
					"19900321052000000",	/*春分*/
					"19900405091400000",	/*清明*/
					"19900420162600000",	/*谷雨*/
					"19900506023600000",	/*立夏*/
					"19900521153600000",	/*小满*/
					"19900606064700000",	/*芒种*/
					"19900621233300000",	/*夏至*/
					"19900707170200000",	/*小暑*/
					"19900723102400000",	/*大暑*/
					"19900808024800000",	/*立秋*/
					"19900823172500000",	/*处暑*/
					"19900908054000000",	/*白露*/
					"19900923150000000",	/*秋分*/
					"19901008211600000",	/*寒露*/
					"19901024001859740",	/*霜降*/
					"19901108002229740",	/*立冬*/
					"19901122214900000",	/*小雪*/
					"19901207171500000",	/*大雪*/
					"19901222110800000",	/*冬至*/
					"19910106043000000",	/*小寒*/
					"19910120215000000" 	/*大寒*/
					};
/*公元2000年的节气时间点*/
const char LUNARJQBASE_2000[24][20]={"20000204203500000",	/*立春*/
					"20000219162900000",	/*雨水*/
					"20000305143500000",	/*惊蛰*/
					"20000320152900000",	/*春分*/
					"20000404192300000",	/*清明*/
					"20000420023200000",	/*谷雨*/
					"20000505123900000",	/*立夏*/
					"20000521013900000",	/*小满*/
					"20000605164600000",	/*芒种*/
					"20000621093500000",	/*夏至*/
					"20000707025900000",	/*小暑*/
					"20000722202600000",	/*大暑*/
					"20000807124500000",	/*立秋*/
					"20000823033000000",	/*处暑*/
					"20000907154000000",	/*白露*/
					"20000923010800000",	/*秋分*/
					"20001008071900000",	/*寒露*/
					"20001023103000000",	/*霜降*/
					"20001107103200000",	/*立冬*/
					"20001122080600000",	/*小雪*/
					"20001207032500000",	/*大雪*/
					"20001221212800000",	/*冬至*/
					"20010105144200000",	/*小寒*/
					"20010120081000000" 	/*大寒*/
					};
/*公元2010年的节气时间点*/
const char LUNARJQBASE_2010[24][20]={"20100204065200000",	/*立春*/
					"20100219024000000",	/*雨水*/
					"20100306004304052",	/*惊蛰*/
					"20100321013600000",	/*春分*/
					"20100405053500000",	/*清明*/
					"20100420123300000",	/*谷雨*/
					"20100505224700000",	/*立夏*/
					"20100521113700000",	/*小满*/
					"20100606025100000",	/*芒种*/
					"20100621193000000",	/*夏至*/
					"20100707130300000",	/*小暑*/
					"20100723062100000",	/*大暑*/
					"20100807225000000",	/*立秋*/
					"20100823132700000",	/*处暑*/
					"20100908014700000",	/*白露*/
					"20100923111000000",	/*秋分*/
					"20101008173000000",	/*寒露*/
					"20101023203700000",	/*霜降*/
					"20101107204600000",	/*立冬*/
					"20101122181700000",	/*小雪*/
					"20101207134200000",	/*大雪*/
					"20101222074200000",	/*冬至*/
					"20110106124939740",	/*小寒*/
					"20110120182400000" 	/*大寒*/
					};
/*公元2012年的节气时间点*/
const char LUNARJQBASE_2012[24][20]={"20120204182223000",	/*立春*/
					"20120219141735000",	/*雨水*/
					"20120305122102000",	/*惊蛰*/
					"20120320131425000",	/*春分*/
					"20120404170536000",	/*清明*/
					"20120420001204000",	/*谷雨*/
					"20120505101940000",	/*立夏*/
					"20120520231531000",	/*小满*/
					"20120605142553000",	/*芒种*/
					"20120621070848000",	/*夏至*/
					"20120707004043000",	/*小暑*/
					"20120722180051000",	/*大暑*/
					"20120807103032000",	/*立秋*/
					"20120823010650000",	/*处暑*/
					"20120907132900000",	/*白露*/
					"20120922224859000",	/*秋分*/
					"20121008051142000",	/*寒露*/
					"20121023081333000",	/*霜降*/
					"20121107082556000",	/*立冬*/
					"20121122055007000",	/*小雪*/
					"20121207011855000",	/*大雪*/
					"20121221191135000",	/*冬至*/
					"20130106064354000",	/*小寒*/
					"20130121000949000" 	/*大寒*/
					};


/*西元历下的节日*/
/*5月的第二个星期日---母亲节*/
/*6月的第三个星期日---父亲节*/
char XiYuan_Holiday[28][30]={"0101--元旦",
				"0214--圣瓦伦丁节",
				"0305--学雷锋日",
				"0308--妇女节",
				"0312--植树节",
				"0314--白色情人节",
				"0315--世界消费者权益日",
				"0401--愚人节",
				"0501--劳动节",
				"0504--青年节",
				"0512--国际护士节",
				"0531--世界无烟日",
				"0601--儿童节",
				"0605--世界环境日",
				"0606--全国爱眼日",
				"0626--国际禁毒日",
				"0701--建党节",
				"0707--抗日战争纪念日",
				"0801--建军节",
				"0910--教师节",
				"0920--全国爱牙日",
				"1001--国庆节",
				"1108--记者节",
				"1111--单身节",
				"1201--世界艾滋病日",
				"1224--平安夜",
				"1225--圣诞节",
				"",
				};

/*农历节日*/
/*清明节是根据清明节气得到的*/
/*除夕是根据每年的最后一天得到的*/
/*闰月不计节日*/
char Chinese_Holiday[10][20]={"0101--春节",
				"0115--元宵节",
				"0505--端午节",
				"0707--七夕节",
				"0715--鬼节",
				"0815--中秋节",
				"0909--重阳节",
				"1208--腊八",
				"1223--小年",
				"",
				};


/*自定义公历节日、纪念日*/
char Diy_XiYuan_Holiday[MAXDIYHOLIDAY][30];

/*自定义公历节日、纪念日*/
char Diy_Lunar_Holiday[MAXDIYHOLIDAY][30];

/*BASESHUO代表计算朔日的基准时间*/
const char BASESHUO[20]="19000100000000000";

/*FIRSTSHUO代表第一个朔日的准确时间*/
const char FIRSTSHUO[20]="19000131092100000";



/*农历年*/
struct Lunar_Year
{
	int lyear;			/*去年年份*/
	int year;			/*今年年份*/
	int nyear;			/*明年年份*/
	char lyearcn[20];		/*去年年份的中文表示 如：二零一一*/
	char yearcn[20];		/*今年年份的中文表示 如：二零一二*/
	char nyearcn[20];		/*明年年份的中文表示 如：二零一三*/
	char lganzhi[5];		/*去年年份的干支 如：丁卯*/
	char ganzhi[5];			/*今年年份的干支 如：戊辰*/
	char nganzhi[5];		/*明年年份的干支 如：己巳*/
	char lshengxiao[3];		/*去年年份的生肖 如：兔*/
	char shengxiao[3];		/*今年年份的生肖 如：龙*/
	char nshengxiao[3];		/*明年年份的生肖 如：蛇*/
	char lnianhao[30];		/*去年年份的年号 如：民国二十三年*/
	char nianhao[30];		/*今年年份的年号 如：民国二十四年*/
	char nnianhao[30];		/*明年年份的年号 如：民国二十五年*/
	char jieqi[33][20];		/*从去年的大雪，到下一年的清明，共33个节气*/
	char shuori[18][20];		/*从去年的十一月到明年的某月结束，取连续的18个月初一*/
	char jiufu[21][9];		/*从去年开始 的九九 三伏 九九，共21个*/
	int daysum;			/*今年的农历一年的总天数*/
	int rflag;			/*今年是否闰年标志 =1闰年 =0平年*/
} lunaryear;

/*农历月*/
struct Lunar_Month
{
	int month;			/*农历月的数字表示*/
	int year;			/*所属农历年的数字表示*/
	char runyue[3];			/*是否闰月，闰月时值为闰，否则为空*/
	char monthcn[10];		/*月的中文表示，如：正月、腊月*/
	char daxiao[3];			/*农历月的大小，取“大”、“小”两个值*/
	char chuyi[9];			/*这个农历月的初一对应的八位公历日期*/
	char nchuyi[9];			/*下一个农历月初一对应的八位公历日期*/
	char jieqi[60];			/*这个农历月的节气信息*/
	int daysum;			/*这个农历月的总天数*/
	int zqflag;			/*是否有中气  0--没有中气  1--有中气*/
} lunarmonth[17];

/*某一农历天的天信息*/
struct Lunar_Day
{
	char westday[9];		/*公历日期格式为YYYYMMDD*/
	char eastday[10];		/*农历日期格式为YYYYMMDD 或者为YYYYRMMDD*/
	char daycn[20];			/*农历日期的中文表示法，如腊月初一*/
	char weekday[10];		/*对应的星期，中文表示*/
	char ganzhi[20];		/*农历对应的干支年月日*/
	char jieqi[15];			/*对应的节气和数伏数九，格式为 节气名 九伏*/
	char jieqitime[10];		/*节气对应的时间点，格式为HH:MM:SS*/
	char jieri[101];		/*是否是节日，是的话写出节日名称，不是则为空*/
} lunarday[MAXLUNARDAY];



/*地支增加或减少一定数目，以一个basedz地支为基础*/
/*num为负数表示减*/
char *Add_Lunar_DiZhi(char *basedz,int num)
{
	int basew=0;
	static char result[5];
	memset(result,0x00,sizeof(result));
	if(strcasecmp(basedz,"子")==0)
	{
		basew=1;
	}
	else if(strcasecmp(basedz,"丑")==0)
	{
		basew=2;
	}
	else if(strcasecmp(basedz,"寅")==0)
	{
		basew=3;
	}
	else if(strcasecmp(basedz,"卯")==0)
	{
		basew=4;
	}
	else if(strcasecmp(basedz,"辰")==0)
	{
		basew=5;
	}
	else if(strcasecmp(basedz,"巳")==0)
	{
		basew=6;
	}
	else if(strcasecmp(basedz,"午")==0)
	{
		basew=7;
	}
	else if(strcasecmp(basedz,"未")==0)
	{
		basew=8;
	}
	else if(strcasecmp(basedz,"申")==0)
	{
		basew=9;
	}
	else if(strcasecmp(basedz,"酉")==0)
	{
		basew=10;
	}
	else if(strcasecmp(basedz,"戌")==0)
	{
		basew=11;
	}
	else if(strcasecmp(basedz,"亥")==0)
	{
		basew=12;
	}
	
	basew=basew+num;
	while(basew<=0)
	{
		basew=basew+12;
	}
	switch (basew)
	{
		case 1:strcpy(result,"子");break;
		case 2:strcpy(result,"丑");break;
		case 3:strcpy(result,"寅");break;
		case 4:strcpy(result,"卯");break;
		case 5:strcpy(result,"辰");break;
		case 6:strcpy(result,"巳");break;
		case 7:strcpy(result,"午");break;
		case 8:strcpy(result,"未");break;
		case 9:strcpy(result,"申");break;
		case 10:strcpy(result,"酉");break;
		case 11:strcpy(result,"戌");break;
		case 12:strcpy(result,"亥");break;
	};
	return result;
}

/*天干增加或减少一定数目，以一个basetg天干为基础*/
/*num为负数表示减*/
char *Add_Lunar_TianGan(char *basetg,int num)
{
	int basew=0;
	static char result[5];
	memset(result,0x00,sizeof(result));
	if(strcasecmp(basetg,"甲")==0)
	{
		basew=1;
	}
	else if(strcasecmp(basetg,"乙")==0)
	{
		basew=2;
	}
	else if(strcasecmp(basetg,"丙")==0)
	{
		basew=3;
	}
	else if(strcasecmp(basetg,"丁")==0)
	{
		basew=4;
	}
	else if(strcasecmp(basetg,"戊")==0)
	{
		basew=5;
	}
	else if(strcasecmp(basetg,"己")==0)
	{
		basew=6;
	}
	else if(strcasecmp(basetg,"庚")==0)
	{
		basew=7;
	}
	else if(strcasecmp(basetg,"辛")==0)
	{
		basew=8;
	}
	else if(strcasecmp(basetg,"壬")==0)
	{
		basew=9;
	}
	else if(strcasecmp(basetg,"癸")==0)
	{
		basew=10;
	}
	
	basew=basew+num;
	while(basew<=0)
	{
		basew=basew+10;
	}
	switch (basew)
	{
		case 1:strcpy(result,"甲");break;
		case 2:strcpy(result,"乙");break;
		case 3:strcpy(result,"丙");break;
		case 4:strcpy(result,"丁");break;
		case 5:strcpy(result,"戊");break;
		case 6:strcpy(result,"己");break;
		case 7:strcpy(result,"庚");break;
		case 8:strcpy(result,"辛");break;
		case 9:strcpy(result,"壬");break;
		case 10:strcpy(result,"癸");break;
	};
	return result;
}

/*甲子增加或减少一定数目，以一个basegz干支为基础*/
/*num为负数表示减*/
char *Add_Lunar_JiaZi(char *basegz,int num)
{
	char tmpt[5];
	char tmpd[5];
	static char result[8];
	
	memset(tmpt,0x00,sizeof(tmpt));
	memset(tmpd,0x00,sizeof(tmpd));
	memset(result,0x00,sizeof(result));
	strcpy(tmpt,Add_Lunar_TianGan(SubString(basegz,0,2),num));
	strcpy(tmpd,Add_Lunar_DiZhi(SubString(basegz,2,2),num));
	sprintf(result,"%s%s",tmpt,tmpd);
	return result;
}

/*得到对应的节气名称*/
char *Get_Lunar_JQName(int i)
{
	static char result[5];
	memset(result,0x00,sizeof(result));
	switch(i)
	{
		case 0:strcpy(result,"大雪");break;
		case 1:strcpy(result,"冬至");break;
		case 2:strcpy(result,"小寒");break;
		case 3:strcpy(result,"大寒");break;
		case 4:strcpy(result,"立春");break;
		case 5:strcpy(result,"雨水");break;
		case 6:strcpy(result,"惊蛰");break;
		case 7:strcpy(result,"春分");break;
		case 8:strcpy(result,"清明");break;
		case 9:strcpy(result,"谷雨");break;
		case 10:strcpy(result,"立夏");break;
		case 11:strcpy(result,"小满");break;
		case 12:strcpy(result,"芒种");break;
		case 13:strcpy(result,"夏至");break;
		case 14:strcpy(result,"小暑");break;
		case 15:strcpy(result,"大暑");break;
		case 16:strcpy(result,"立秋");break;
		case 17:strcpy(result,"处暑");break;
		case 18:strcpy(result,"白露");break;
		case 19:strcpy(result,"秋分");break;
		case 20:strcpy(result,"寒露");break;
		case 21:strcpy(result,"霜降");break;
		case 22:strcpy(result,"立冬");break;
		case 23:strcpy(result,"小雪");break;
		case 24:strcpy(result,"大雪");break;
		case 25:strcpy(result,"冬至");break;
		case 26:strcpy(result,"小寒");break;
		case 27:strcpy(result,"大寒");break;
		case 28:strcpy(result,"立春");break;
		case 29:strcpy(result,"雨水");break;
		case 30:strcpy(result,"惊蛰");break;
		case 31:strcpy(result,"春分");break;
		case 32:strcpy(result,"清明");break;
	};
	return result;
}

/*读取自定义节日文件*/
/*填充到自定义节日数组中*/
int Read_Lunar_Diy_Holiday()
{
	int i=0,k=0,g=0;
	char filename[MAX_PATH];
	char bufline[100];
	char ctype='n';
	FILE *fp=NULL;
	memset(filename,0x00,sizeof(filename));
	strcpy(filename,GetConfig("diyholidayfile"));
	for(i=0;i<MAXDIYHOLIDAY;i++)
	{
		strcpy(Diy_XiYuan_Holiday[i],"");
		strcpy(Diy_Lunar_Holiday[i],"");
	}
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		return -1;
	}
	while(!feof(fp))
	{
		memset(bufline,0x00,sizeof(bufline));
		fgets(bufline,sizeof(bufline),fp);
		if(strlen(bufline)==0)
			continue;
		if(strcasecmp(bufline,"\n")==0)
			continue;
		if(strcon(bufline,"\n")==0)
			strrep(bufline,"\n","");
		trim(bufline);
		if(bufline[0]=='#')
		{
			if((strcasecon(bufline,"Gregorian")==0)&&(strcasecon(bufline,"begin")==0))
			{
				ctype='g';
			}
			else if((strcasecon(bufline,"Lunar")==0)&&(strcasecon(bufline,"begin")==0))
			{
				ctype='l';
			}
			continue;
		}
		if(strlen(bufline)<=6)
			continue;
		if(strcmp(SubString(bufline,4,2),"--")!=0)
			continue;
		if(isdigitstr(SubString(bufline,0,4))!=0)
			continue;
		if(ctype=='n')
			continue;
		if(ctype=='g')
		{
			if(k<MAXDIYHOLIDAY)
			{
				memset(Diy_XiYuan_Holiday[k],0x00,sizeof(Diy_XiYuan_Holiday[k]));
				strcpy(Diy_XiYuan_Holiday[k],bufline);
				k++;
			}
		}
		else if(ctype=='l')
		{
			if(g<MAXDIYHOLIDAY)
			{
				memset(Diy_Lunar_Holiday[g],0x00,sizeof(Diy_Lunar_Holiday[g]));
				strcpy(Diy_Lunar_Holiday[g],bufline);
				g++;
			}
		}
	}
	fclose(fp);
	return 0;
}


/*得到某一天的节日信息*/
/*参数为公历日期和农历日期,格式均为八位，农历可能为9位*/
/*返回结果为具体节日信息，格式 公历#公历|农历@农历*/
/*如果没有节日，返回空*/
char *Get_Lunar_JieRi(char *date1,char *date2)
{
	int i=0,len=0,rflag=0,hflag=0,sunday=0;;
	char dt1[5];
	char dt2[5];
	char tmpdate[9];
	char nowdate[9];
	char wkday[10];
	char tmpstr[51];
	char info[30];
	static char result[100+1];
	memset(dt1,0x00,sizeof(dt1));
	memset(dt2,0x00,sizeof(dt2));
	memset(result,0x00,sizeof(result));
	strcpy(result,"");
	strcpy(dt1,SubString(date1,4,4));
	len=strlen(date2);
	
	if(len==8)
	{
		strcpy(dt2,SubString(date2,4,4));
		rflag=0;
	}
	else if(len==9)
	{
		strcpy(dt2,SubString(date2,5,4));
		rflag=1;
	}
	/*先获取公历节日*/
	i=0;
	while(strlen(XiYuan_Holiday[i])!=0)
	{
		if(strcasecmp(dt1,SubString(XiYuan_Holiday[i],0,4))==0)
		{
			strcat(result,SubString(XiYuan_Holiday[i],6,strlen(XiYuan_Holiday[i])-6));
			break;
		}
		i++;
	}
	/*1、公历的母亲节*/
	/*5月的第二个星期日---母亲节*/
	memset(wkday,0x00,sizeof(wkday));
	strcpy(wkday,GetWeek(date1,"chinese"));
	if((strcasecmp(SubString(date1,4,2),"05")==0)&&(strcasecmp(wkday,"星期日")==0))
	{
		/*现在需要判断是不是第二个星期日*/
		/*需要知道这个月本个星期日前面有几个星期日*/
		sunday=0;
		memset(nowdate,0x00,sizeof(nowdate));
		strcpy(nowdate,date1);
		while(1)
		{
			memset(tmpdate,0x00,sizeof(tmpdate));
			strcpy(tmpdate,GetDate(nowdate,-7));
			memset(nowdate,0x00,sizeof(nowdate));
			strcpy(nowdate,tmpdate);
			if(strcasecmp(SubString(nowdate,4,2),"05")==0)
			{
				sunday++;
			}
			else
			{
				break;
			}
		}
		if(sunday==1)
		{
			/*如果这个月前面还有一个星期日，那么说明今天就是母亲节*/
			if(strlen(result)==0)
			{
				strcat(result,"母亲节");
			}
			else
			{
				strcat(result,"#母亲节");
			}
		}
	}
	
	/*2、公历的父亲节*/	
	/*6月的第三个星期日---父亲节*/
	memset(wkday,0x00,sizeof(wkday));
	strcpy(wkday,GetWeek(date1,"chinese"));
	if((strcasecmp(SubString(date1,4,2),"06")==0)&&(strcasecmp(wkday,"星期日")==0))
	{
		/*现在需要判断是不是第三个星期日*/
		/*需要知道这个月本个星期日前面有几个星期日*/
		sunday=0;
		memset(nowdate,0x00,sizeof(nowdate));
		strcpy(nowdate,date1);
		while(1)
		{
			memset(tmpdate,0x00,sizeof(tmpdate));
			strcpy(tmpdate,GetDate(nowdate,-7));
			memset(nowdate,0x00,sizeof(nowdate));
			strcpy(nowdate,tmpdate);
			if(strcasecmp(SubString(nowdate,4,2),"06")==0)
			{
				sunday++;
			}
			else
			{
				break;
			}
		}
		if(sunday==2)
		{
			/*如果这个月前面还有两个星期日，那么说明今天就是父亲节*/
			if(strlen(result)==0)
			{
				strcat(result,"父亲节");
			}
			else
			{
				strcat(result,"#父亲节");
			}
		}
	}
	/*开始加载自定义公历节日*/
	i=0;
	while(strlen(Diy_XiYuan_Holiday[i])!=0)
	{
		if(strcasecmp(dt1,SubString(Diy_XiYuan_Holiday[i],0,4))==0)
		{
			if(strlen(result)==0)
			{
				strcat(result,SubString(Diy_XiYuan_Holiday[i],6,strlen(Diy_XiYuan_Holiday[i])-6));
			}
			else
			{
				strcat(result,"#");
				strcat(result,SubString(Diy_XiYuan_Holiday[i],6,strlen(Diy_XiYuan_Holiday[i])-6));
			}
			break;
		}
		i++;
	}
	
	
	
	/*现在开始判断农历节日*/
	
	/*先判断是不是除夕，除夕与是否闰月无关*/
	if((strcasecmp(dt2,"1229")==0)||(strcasecmp(dt2,"1230")==0))
	{
		/*我要判断公历的明天是不是正月初一*/
		memset(tmpdate,0x00,sizeof(tmpdate));
		strcpy(tmpdate,GetDate(date1,1));
		for(i=0;i<17;i++)
		{
			if((strcmp(lunarmonth[i].chuyi,tmpdate)==0)&&(lunarmonth[i].month==1))
			{
				strcat(result,"|除夕");
				break;
			}
		}
	}
	/*再判断农历，是不是闰月,如果是闰月，那么除去上面的除夕外没有节日*/
	/*如果不是闰月*/
	if(rflag==0)
	{
		/*判断非农历闰月情况下的农历节日*/
		i=0;
		while(strlen(Chinese_Holiday[i])!=0)
		{
			memset(info,0x00,sizeof(info));
			strcpy(info,Chinese_Holiday[i]);
			if(strcasecmp(dt2,SubString(Chinese_Holiday[i],0,4))==0)
			{
				if(strlen(result)==0)
				{
					strcat(result,"|");
					strcat(result,SubString(Chinese_Holiday[i],6,strlen(Chinese_Holiday[i])-6));
				}
				else
				{
					if(strcon(result,"|")==0)
					{
						strcat(result,"@");
						strcat(result,SubString(Chinese_Holiday[i],6,strlen(Chinese_Holiday[i])-6));
					}
					else
					{
						strcat(result,"|");
						strcat(result,SubString(Chinese_Holiday[i],6,strlen(Chinese_Holiday[i])-6));
					}
				}
				break;
			}
			i++;
		}
		
		/*开始加载自定义农历节日*/
		i=0;
		while(strlen(Diy_Lunar_Holiday[i])!=0)
		{
			if(strcasecmp(dt2,SubString(Diy_Lunar_Holiday[i],0,4))==0)
			{
				if(strlen(result)==0)
				{
					strcat(result,"|");
					strcat(result,SubString(Diy_Lunar_Holiday[i],6,strlen(Diy_Lunar_Holiday[i])-6));
				}
				else
				{
					if(strcon(result,"|")==0)
					{
						strcat(result,"@");
						strcat(result,SubString(Diy_Lunar_Holiday[i],6,strlen(Diy_Lunar_Holiday[i])-6));
					}
					else
					{
						strcat(result,"|");
						strcat(result,SubString(Diy_Lunar_Holiday[i],6,strlen(Diy_Lunar_Holiday[i])-6));
					}
				}
				break;
			}
			i++;
		}
	}
	return result;
}


/*得到农历数伏数九的名称*/
char *Get_Lunar_JiuFu_Name(int i)
{
	static char result[5];
	memset(result,0x00,sizeof(result));
	switch(i)
	{
		case 0:strcpy(result,"一九");break;
		case 1:strcpy(result,"二九");break;
		case 2:strcpy(result,"三九");break;
		case 3:strcpy(result,"四九");break;
		case 4:strcpy(result,"五九");break;
		case 5:strcpy(result,"六九");break;
		case 6:strcpy(result,"七九");break;
		case 7:strcpy(result,"八九");break;
		case 8:strcpy(result,"九九");break;
		case 9:strcpy(result,"初伏");break;
		case 10:strcpy(result,"二伏");break;
		case 11:strcpy(result,"三伏");break;
		case 12:strcpy(result,"一九");break;
		case 13:strcpy(result,"二九");break;
		case 14:strcpy(result,"三九");break;
		case 15:strcpy(result,"四九");break;
		case 16:strcpy(result,"五九");break;
		case 17:strcpy(result,"六九");break;
		case 18:strcpy(result,"七九");break;
		case 19:strcpy(result,"八九");break;
		case 20:strcpy(result,"九九");break;
	};
	return result;
}


/*得到某个日期和三伏九九的关联*/
/*参数为8位公历日期*/
/*返回为空  或者某某第几天 (第一天不返回)*/
char *Get_Lunar_JiuFu_Num(char *date)
{
	int i=0,dc1=0,dc2=0;
	static char result[20];
	memset(result,0x00,sizeof(result));
	
	strcpy(result,"");
	dc1=GetDayCha(date,lunaryear.jiufu[0]);
	if(dc1<0)
	{
		return result;
	}
	dc1=GetDayCha(date,lunaryear.jiufu[20]);
	if(dc1>=9)
	{
		return result;
	}
	dc1=GetDayCha(date,lunaryear.jiufu[8]);	
	dc2=GetDayCha(date,lunaryear.jiufu[9]);	
	if((dc1>=9)&&(dc2<0))
	{
		return result;
	}
	dc1=GetDayCha(date,lunaryear.jiufu[11]);	
	dc2=GetDayCha(date,lunaryear.jiufu[12]);	
	if((dc1>=10)&&(dc2<0))
	{
		return result;
	}
	for(i=0;i<9;i++)
	{
		if(i==8)
		{
			dc1=GetDayCha(date,lunaryear.jiufu[i]);	
			dc2=GetDayCha(date,GetDate(lunaryear.jiufu[i],9));	
		}
		else
		{
			dc1=GetDayCha(date,lunaryear.jiufu[i]);	
			dc2=GetDayCha(date,lunaryear.jiufu[i+1]);
		}
		if((dc1>0)&&(dc2<0))
		{
			dc1++;
			memset(result,0x00,sizeof(result));
			sprintf(result,"%s第%s天",Get_Lunar_JiuFu_Name(i),GetChineseSZ(dc1));
			return result;
		}
	}
	for(i=9;i<12;i++)
	{
		if(i==11)
		{
			dc1=GetDayCha(date,lunaryear.jiufu[i]);	
			dc2=GetDayCha(date,GetDate(lunaryear.jiufu[i],10));	
		}
		else
		{
			dc1=GetDayCha(date,lunaryear.jiufu[i]);	
			dc2=GetDayCha(date,lunaryear.jiufu[i+1]);
		}
		if((dc1>0)&&(dc2<0))
		{
			dc1++;
			memset(result,0x00,sizeof(result));
			sprintf(result,"%s第%s天",Get_Lunar_JiuFu_Name(i),GetChineseSZ(dc1));
			return result;
		}
	}
	for(i=12;i<21;i++)
	{
		if(i==20)
		{
			dc1=GetDayCha(date,lunaryear.jiufu[i]);	
			dc2=GetDayCha(date,GetDate(lunaryear.jiufu[i],9));	
		}
		else
		{
			dc1=GetDayCha(date,lunaryear.jiufu[i]);	
			dc2=GetDayCha(date,lunaryear.jiufu[i+1]);
		}
		if((dc1>0)&&(dc2<0))
		{
			dc1++;
			memset(result,0x00,sizeof(result));
			sprintf(result,"%s第%s天",Get_Lunar_JiuFu_Name(i),GetChineseSZ(dc1));
			return result;
		}
	}
	return result;
}

/*得到某天是不是节气，或者是数伏数九。。。。*/
/*参数为8位公历日期*/
/*返回为空  或者格式为  节气#YYYYMMDDHHMMSSMIL|九九  清明时节气写为清明节*/
char *Get_Lunar_Day_JieQi(char *date)
{
	int i=0;
	static char result[40];
	memset(result,0x00,sizeof(result));
	strcpy(result,"");
	for(i=0;i<33;i++)
	{
		if(strcmp(date,SubString(lunaryear.jieqi[i],0,8))==0)
		{
			strcat(result,Get_Lunar_JQName(i));
			if(strcmp(result,"清明")==0)
			{
				strcat(result,"节");
			}
			strcat(result,"#");
			strcat(result,lunaryear.jieqi[i]);
			break;
		}
	}
	for(i=0;i<21;i++)
	{
		if(strcmp(date,lunaryear.jiufu[i])==0)
		{
			if(strlen(result)!=0)
				strcat(result,"|");
			strcat(result,Get_Lunar_JiuFu_Name(i));
			break;
		}
	}
	return result;
}



/*得到月地支*/
/*参数为八位公历日期*/
char *Get_Lunar_Month_DiZhi(char *date)
{
	int i=0,dc1=0,dc2=0;
	static char result[3];
	memset(result,0x00,sizeof(result));
	dc1=GetDayCha(SubString(lunaryear.jieqi[0],0,8),date);
	if(dc1>0)
	{
		strcpy(result,"亥");
		return result;
	}
	dc1=GetDayCha(SubString(lunaryear.jieqi[32],0,8),date);
	if(dc1<=0)
	{
		strcpy(result,"辰");
		return result;
	}
	for(i=0;i<32;i=i+2)
	{
		dc1=GetDayCha(SubString(lunaryear.jieqi[i],0,8),date);
		dc2=GetDayCha(date,SubString(lunaryear.jieqi[i+2],0,8));
		if((dc1<=0)&&(dc2<0))
		{
			switch(i)
			{
				case 0:strcpy(result,"子");break;
				case 2:strcpy(result,"丑");break;
				case 4:strcpy(result,"寅");break;
				case 6:strcpy(result,"卯");break;
				case 8:strcpy(result,"辰");break;
				case 10:strcpy(result,"巳");break;
				case 12:strcpy(result,"午");break;
				case 14:strcpy(result,"未");break;
				case 16:strcpy(result,"申");break;
				case 18:strcpy(result,"酉");break;
				case 20:strcpy(result,"戌");break;
				case 22:strcpy(result,"亥");break;
				case 24:strcpy(result,"子");break;
				case 26:strcpy(result,"丑");break;
				case 28:strcpy(result,"寅");break;
				case 30:strcpy(result,"卯");break;
			};
			break;
		}
	}
	return result;
}

/* 由年干支和月地支得到月天干 */
/* 参数一为年干支，参数二为月地支 */
/* 返回结果为月天干 */
char *Get_Lunar_Month_TianGan(char *ygz,char *mondz)
{
	static char result[5];
	memset(result,0x00,sizeof(result));
	if(strcmp(mondz,"寅")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"丙");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"戊");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"庚");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"壬");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"甲");
		}	
	}
	else if(strcmp(mondz,"卯")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"丁");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"己");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"辛");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"癸");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"乙");
		}	
	}
	else if(strcmp(mondz,"辰")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"戊");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"庚");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"壬");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"甲");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"丙");
		}	
	}
	else if(strcmp(mondz,"巳")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"己");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"辛");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"癸");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"乙");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"丁");
		}	
	}
	else if(strcmp(mondz,"午")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"庚");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"壬");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"甲");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"丙");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"戊");
		}	
	}
	else if(strcmp(mondz,"未")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"辛");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"癸");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"乙");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"丁");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"己");
		}	
	}
	else if(strcmp(mondz,"申")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"壬");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"甲");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"丙");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"戊");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"庚");
		}	
	}
	else if(strcmp(mondz,"酉")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"癸");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"乙");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"丁");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"己");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"辛");
		}	
	}
	else if(strcmp(mondz,"戌")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"甲");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"丙");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"戊");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"庚");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"壬");
		}	
	}
	else if(strcmp(mondz,"亥")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"乙");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"丁");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"己");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"辛");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"癸");
		}	
	}
	else if(strcmp(mondz,"子")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"丙");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"戊");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"庚");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"壬");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"甲");
		}	
	}
	else if(strcmp(mondz,"丑")==0)
	{
		if((strcon(ygz,"甲")==0)||(strcon(ygz,"己")==0))
		{
			strcpy(result,"丁");
		}
		else if((strcon(ygz,"乙")==0)||(strcon(ygz,"庚")==0))
		{
			strcpy(result,"己");
		}
		else if((strcon(ygz,"丙")==0)||(strcon(ygz,"辛")==0))
		{
			strcpy(result,"辛");
		}
		else if((strcon(ygz,"丁")==0)||(strcon(ygz,"壬")==0))
		{
			strcpy(result,"癸");
		}
		else if((strcon(ygz,"戊")==0)||(strcon(ygz,"癸")==0))
		{
			strcpy(result,"乙");
		}	
	}
	return result;
}

/* 得到某一天的日干支 */
/* 参数为八位公历日期 */
/* 返回结果为日干支 */
char *Get_Lunar_Day_GanZhi(char *date)
{
	int daycha=0,yushu=0;
	static char result[10];
	memset(result,0x00,sizeof(result));
	daycha=GetDayChaFromBase(date);
	if(daycha>=0)
	{
		yushu=daycha%10;
		switch (yushu)
		{
			case 0:strcpy(result,"甲");break;
			case 1:strcpy(result,"乙");break;
			case 2:strcpy(result,"丙");break;
			case 3:strcpy(result,"丁");break;
			case 4:strcpy(result,"戊");break;
			case 5:strcpy(result,"己");break;
			case 6:strcpy(result,"庚");break;
			case 7:strcpy(result,"辛");break;
			case 8:strcpy(result,"壬");break;
			case 9:strcpy(result,"癸");break;
		};
		yushu=daycha%12;
		switch (yushu)
		{
			case 0:strcat(result,"戌");break;
			case 1:strcat(result,"亥");break;
			case 2:strcat(result,"子");break;
			case 3:strcat(result,"丑");break;
			case 4:strcat(result,"寅");break;
			case 5:strcat(result,"卯");break;
			case 6:strcat(result,"辰");break;
			case 7:strcat(result,"巳");break;
			case 8:strcat(result,"午");break;
			case 9:strcat(result,"未");break;
			case 10:strcat(result,"申");break;
			case 11:strcat(result,"酉");break;
		};
	}
	else
	{
		daycha=-daycha;
		yushu=daycha%10;
		switch (yushu)
		{
			case 0:strcpy(result,"甲");break;
			case 1:strcpy(result,"癸");break;
			case 2:strcpy(result,"壬");break;
			case 3:strcpy(result,"辛");break;
			case 4:strcpy(result,"庚");break;
			case 5:strcpy(result,"己");break;
			case 6:strcpy(result,"戊");break;
			case 7:strcpy(result,"丁");break;
			case 8:strcpy(result,"丙");break;
			case 9:strcpy(result,"乙");break;
		};
		yushu=daycha%12;
		switch (yushu)
		{
			case 0:strcat(result,"戌");break;
			case 1:strcat(result,"酉");break;
			case 2:strcat(result,"申");break;
			case 3:strcat(result,"未");break;
			case 4:strcat(result,"午");break;
			case 5:strcat(result,"巳");break;
			case 6:strcat(result,"辰");break;
			case 7:strcat(result,"卯");break;
			case 8:strcat(result,"寅");break;
			case 9:strcat(result,"丑");break;
			case 10:strcat(result,"子");break;
			case 11:strcat(result,"亥");break;
		};
	}
	return result;
}

/* 得到某天的干支，输入的参数为8位公历日期YYYYMMDD*/
/* 返回参数为干支，之间用空格间隔*/
char *Get_Lunar_Date_GanZhi(char *date)
{
	int gyear=0,gmonth=0,gday=0,daycha=0;
	char lastlichun[9];
	char yeargz[10];
	char monthgz[10];
	char monthz[5];
	char monthg[5];
	char daygz[10];
	static char result[30];
	
	memset(lastlichun,0x00,sizeof(lastlichun));
	memset(yeargz,0x00,sizeof(yeargz));
	memset(monthgz,0x00,sizeof(monthgz));
	memset(monthz,0x00,sizeof(monthz));
	memset(monthg,0x00,sizeof(monthg));
	memset(daygz,0x00,sizeof(daygz));
	
	
	gyear=atoi(SubString(date,0,4));
	gmonth=atoi(SubString(date,4,2));
	gday=atoi(SubString(date,6,2));
	
	strcpy(lastlichun,SubString(lunaryear.jieqi[4],0,8));
	/*必须先得到年份的干支*/
	/*倘若日期是在立春之前，应该算前一年的干支*/
	daycha=GetDayCha(date,lastlichun);
	if(daycha<0)
	{
		strcpy(yeargz,lunaryear.lganzhi);
	}
	else
	{
		memset(lastlichun,0x00,sizeof(lastlichun));
		strcpy(lastlichun,SubString(lunaryear.jieqi[28],0,8));
		daycha=GetDayCha(date,lastlichun);
		if(daycha<0)
		{
			strcpy(yeargz,lunaryear.ganzhi);
		}
		else
		{
			strcpy(yeargz,lunaryear.nganzhi);
		}
	}
	
	strcpy(monthz,Get_Lunar_Month_DiZhi(date));
	strcpy(monthg,Get_Lunar_Month_TianGan(yeargz,monthz));
	sprintf(monthgz,"%s%s",monthg,monthz);
	
	
	strcpy(daygz,Get_Lunar_Day_GanZhi(date));
	memset(result,0x00,sizeof(result));
	sprintf(result,"%s %s %s",yeargz,monthgz,daygz);
	return result;
}


/*打印农历月信息*/
int PrintMonth()
{
	int i=0;
	printf("\n月信息\n\n");
	for(i=0;i<17;i++)
	{
		printf("月份：农历[%d]年[%d]月\n总天数：[%d]\n有无中气：[%d]\n",lunarmonth[i].year,lunarmonth[i].month,lunarmonth[i].daysum,lunarmonth[i].zqflag);
		printf("农历信息：[%s]\t[%s]\t[%s]\n",lunarmonth[i].runyue,lunarmonth[i].monthcn,lunarmonth[i].daxiao);
		printf("此月初一：[%s]\n下月初一：[%s]\n",lunarmonth[i].chuyi,lunarmonth[i].nchuyi);
		printf("节气：[%s]\n\n\n",lunarmonth[i].jieqi);
	}
	return 0;
}


/*打印农历年信息*/
int PrintYear()
{
	int i=0;
	printf("去年:[%d]\t[%s]\t[%s]\t[%s]\t[%s]\n",lunaryear.lyear,lunaryear.lyearcn,lunaryear.lganzhi,lunaryear.lshengxiao,lunaryear.lnianhao);
	printf("今年:[%d]\t[%s]\t[%s]\t[%s]\t[%s]\n",lunaryear.year,lunaryear.yearcn,lunaryear.ganzhi,lunaryear.shengxiao,lunaryear.nianhao);
	printf("明年:[%d]\t[%s]\t[%s]\t[%s]\t[%s]\n",lunaryear.nyear,lunaryear.nyearcn,lunaryear.nganzhi,lunaryear.nshengxiao,lunaryear.nnianhao);
	printf("\n节气信息\n");
	for(i=0;i<33;i++)
	{
		printf("%s\t[%s]\n",Get_Lunar_JQName(i),lunaryear.jieqi[i]);
	}
	printf("\n朔日信息\n");
	for(i=0;i<18;i++)
	{
		printf("[%s]\t第%d个朔日\n",lunaryear.shuori[i],i+1);
	}
	printf("\n总天数%d\n",lunaryear.daysum);
	if(lunaryear.rflag==1)
	{
		printf("闰年\n");
	}
	else
	{
		printf("平年\n");
	}
	
	return 0;
}




/*得到两个时间之间的秒差，格式为YYYYMMDDHHMMSSMIL*/
/*返回结果为double*/
/*由于计算机32位机器，存储整型数据长度不够*/
/*为了避免出现溢出错误，将函数定义改为时间之间的天数差*/
double Get_Lunar_DayCha(char *date1,char *date2)
{
	double result=0;
	char dt1[9];
	char dt2[9];
	char tm1[7];
	char tm2[7];
	memset(dt1,0x00,sizeof(dt1));
	memset(dt2,0x00,sizeof(dt2));
	memset(tm1,0x00,sizeof(tm1));
	memset(tm2,0x00,sizeof(tm2));
	
	strncpy(dt1,SubString(date1,0,8),sizeof(dt1));
	strncpy(dt2,SubString(date2,0,8),sizeof(dt2));
	strncpy(tm1,SubString(date1,8,6),sizeof(tm1));
	strncpy(tm2,SubString(date2,8,6),sizeof(tm2));

	result=GetTianCha(dt1,dt2,tm1,tm2);
	return result;
}


/*得到第m个朔日的时间，返回为日期YYYYMMDDHHMMSSMIL*/
/*m为以1900年为基准到现在的朔月个数*/
char *Get_Lunar_M_Shuo(int m)
{
	double addtian=0,addmiao=0;
	char basedate[20];
	static char result[20];
	memset(basedate,0x00,sizeof(basedate));
	memset(result,0x00,sizeof(result));
	strcpy(basedate,BASESHUO);
	addtian=1.6 + SHUOWANG * m + 0.4 * sin(1 - 0.45058 * m);
	addmiao=addtian*864;
	strncpy(result,CalcSecond(basedate,addmiao,100),sizeof(result));
	return result;
}


/*得到某一个节气之前的最近的一个朔日，参数为日期YYYYMMDDHHMMSSMIL*/
/*返回结果为int，表示从1900年开始后的第N个朔日*/
int Get_Lunar_DongYueShuo(char *date1)
{
	double daycha=0,d1=0,d2=0;
	int m=0;
	char fshuo[20];
	char dt1[20];
	char dt2[20];
	char dy1[9];
	char dy2[9];
	char dyb[9];
	memset(fshuo,0x00,sizeof(fshuo));
	memset(dyb,0x00,sizeof(dyb));
	strncpy(fshuo,FIRSTSHUO,sizeof(fshuo));
	strcpy(dyb,SubString(date1,0,8));
	daycha=Get_Lunar_DayCha(date1,fshuo);
	m=daycha/SHUOWANG;
	while(1)
	{
		memset(dt1,0x00,sizeof(dt1));
		memset(dt2,0x00,sizeof(dt2));
		strncpy(dt1,Get_Lunar_M_Shuo(m),sizeof(dt1));
		strncpy(dt2,Get_Lunar_M_Shuo(m+1),sizeof(dt2));
		memset(dy1,0x00,sizeof(dy1));
		memset(dy2,0x00,sizeof(dy2));
		strcpy(dy1,SubString(dt1,0,8));
		strcpy(dy2,SubString(dt2,0,8));
		d1=Get_Lunar_DayCha(dyb,dy1);
		d2=Get_Lunar_DayCha(dyb,dy2);
		if(d1<0)
		{
			m--;
		}
		else if(d1==0)
		{
			break;
		}
		else if(d1>0)
		{
			if(d2<0)
			{
				break;
			}
			else if(d2==0)
			{
				m=m+1;
				break;
			}
			else if(d2>0)
			{
				m++;
			}
		}
	}
	return m;
	
}


/*得到某一年的某个节气的具体点*/
/*参数为具体的一年，格式为int型，第二个参数为某个节气，从1开始，代表立春*/
/*返回结果为具体的日期，格式为YYYYMMDDHHMMSSMIL*/
char *Get_Lunar_Year_AnyJieqi(int year,int type)
{
	int fornum=0;
	char base_date[20];
	static char result[20];
	memset(result,0x00,sizeof(result));
	memset(base_date,0x00,sizeof(base_date));
	if (year<1950)
	{
		strcpy(base_date,LUNARJQBASE_1900[type-1]);
		fornum=year-1900;
	}
	else if (year<1970)
	{
		strcpy(base_date,LUNARJQBASE_1950[type-1]);
		fornum=year-1950;
	}
	else if (year<1980)
	{
		strcpy(base_date,LUNARJQBASE_1970[type-1]);
		fornum=year-1970;
	}
	else if (year<1990)
	{
		strcpy(base_date,LUNARJQBASE_1980[type-1]);
		fornum=year-1980;
	}
	else if (year<2000)
	{
		strcpy(base_date,LUNARJQBASE_1990[type-1]);
		fornum=year-1990;
	}
	else if (year<2010)
	{
		strcpy(base_date,LUNARJQBASE_2000[type-1]);
		fornum=year-2000;
	}
	else if (year<2012)
	{
		strcpy(base_date,LUNARJQBASE_2010[type-1]);
		fornum=year-2010;
	}
	else
	{
		strcpy(base_date,LUNARJQBASE_2012[type-1]);
		fornum=year-2012;
	}
	strcpy(result,CalcSecond(base_date,LOOPYEAR,fornum));
	return result;
}


/*得到年号，输入为年份，返回如：清 光绪二十四年*/
char *Get_Lunar_NianHao(int nyear)
{
	int nc=0;
	static char result[30];
	memset(result,0x00,sizeof(result));
	if((nyear>=1875)&&(nyear<=1908))
	{
		nc=nyear-1874;
		strcpy(result,"清 光绪");
		if(nc==1)
		{
			strcat(result,"元年");
		}
		else
		{
			strcat(result,GetChineseSZ(nc));
			strcat(result,"年");
		}
	}
	else if((nyear>=1909)&&(nyear<=1911))
	{
		nc=nyear-1908;
		strcpy(result,"清 宣统");
		if(nc==1)
		{
			strcat(result,"元年");
		}
		else
		{
			strcat(result,GetChineseSZ(nc));
			strcat(result,"年");
		}
	}
	else if((nyear>=1912)&&(nyear<=1949))
	{
		nc=nyear-1911;
		strcpy(result,"民国");
		if(nc==1)
		{
			strcat(result,"元年");
		}
		else
		{
			strcat(result,GetChineseSZ(nc));
			strcat(result,"年");
		}
	}
	else if(nyear>=1950)
	{
		nc=nyear-1949;
		strcpy(result,"共和");
		if(nc==1)
		{
			strcat(result,"元年");
		}
		else
		{
			strcat(result,GetChineseSZ(nc));
			strcat(result,"年");
		}
	}
	return result;
}


/*根据年干支得到生肖*/
char *Get_Lunar_YearSX(char *ganzhi)
{
	char di[3];
	static char result[3];
	memset(di,0x00,sizeof(di));
	memset(result,0x00,sizeof(result));
	strcpy(di,SubString(ganzhi,2,2));
	if(strcmp(di,"子")==0)
	{
		strcpy(result,"鼠");
	}
	else if(strcmp(di,"丑")==0)
	{
		strcpy(result,"牛");
	}
	else if(strcmp(di,"寅")==0)
	{
		strcpy(result,"虎");
	}
	else if(strcmp(di,"卯")==0)
	{
		strcpy(result,"兔");
	}
	else if(strcmp(di,"辰")==0)
	{
		strcpy(result,"龙");
	}
	else if(strcmp(di,"巳")==0)
	{
		strcpy(result,"蛇");
	}
	else if(strcmp(di,"午")==0)
	{
		strcpy(result,"马");
	}
	else if(strcmp(di,"未")==0)
	{
		strcpy(result,"羊");
	}
	else if(strcmp(di,"申")==0)
	{
		strcpy(result,"猴");
	}
	else if(strcmp(di,"酉")==0)
	{
		strcpy(result,"鸡");
	}
	else if(strcmp(di,"戌")==0)
	{
		strcpy(result,"狗");
	}
	else if(strcmp(di,"亥")==0)
	{
		strcpy(result,"猪");
	}
	return result;
}


/*得到某农历年的天干地支*/
/*输入参数为int型的年份*/
/*返回为干支*/
char *Get_Lunar_Year_GanZhi(int year)
{
	int ycha=0,yushu=0;
	char tian[3];
	char di[3];
	static char result[5];
	
	memset(tian,0x00,sizeof(tian));
	memset(di,0x00,sizeof(di));
	memset(result,0x00,sizeof(result));
	
	if(year>1900)
	{
		ycha=year-1900;
		yushu=ycha%10;
		switch (yushu)
		{
			case 0:strncpy(tian,"庚",sizeof(tian));break;
			case 1:strncpy(tian,"辛",sizeof(tian));break;
			case 2:strncpy(tian,"壬",sizeof(tian));break;
			case 3:strncpy(tian,"癸",sizeof(tian));break;
			case 4:strncpy(tian,"甲",sizeof(tian));break;
			case 5:strncpy(tian,"乙",sizeof(tian));break;
			case 6:strncpy(tian,"丙",sizeof(tian));break;
			case 7:strncpy(tian,"丁",sizeof(tian));break;
			case 8:strncpy(tian,"戊",sizeof(tian));break;
			case 9:strncpy(tian,"己",sizeof(tian));break;
		};
		yushu=ycha%12;
		switch (yushu)
		{
			case 0:strncpy(di,"子",sizeof(di));break;
			case 1:strncpy(di,"丑",sizeof(di));break;
			case 2:strncpy(di,"寅",sizeof(di));break;
			case 3:strncpy(di,"卯",sizeof(di));break;
			case 4:strncpy(di,"辰",sizeof(di));break;
			case 5:strncpy(di,"巳",sizeof(di));break;
			case 6:strncpy(di,"午",sizeof(di));break;
			case 7:strncpy(di,"未",sizeof(di));break;
			case 8:strncpy(di,"申",sizeof(di));break;
			case 9:strncpy(di,"酉",sizeof(di));break;
			case 10:strncpy(di,"戌",sizeof(di));break;
			case 11:strncpy(di,"亥",sizeof(di));break;
		};
	}
	else
	{
		ycha=1900-year;
		yushu=ycha%10;
		switch (yushu)
		{
			case 0:strncpy(tian,"庚",sizeof(tian));break;
			case 1:strncpy(tian,"己",sizeof(tian));break;
			case 2:strncpy(tian,"戊",sizeof(tian));break;
			case 3:strncpy(tian,"丁",sizeof(tian));break;
			case 4:strncpy(tian,"丙",sizeof(tian));break;
			case 5:strncpy(tian,"乙",sizeof(tian));break;
			case 6:strncpy(tian,"甲",sizeof(tian));break;
			case 7:strncpy(tian,"癸",sizeof(tian));break;
			case 8:strncpy(tian,"壬",sizeof(tian));break;
			case 9:strncpy(tian,"辛",sizeof(tian));break;
		};
		yushu=ycha%12;
		switch (yushu)
		{
			case 0:strncpy(di,"子",sizeof(di));break;
			case 1:strncpy(di,"亥",sizeof(di));break;
			case 2:strncpy(di,"戌",sizeof(di));break;
			case 3:strncpy(di,"酉",sizeof(di));break;
			case 4:strncpy(di,"申",sizeof(di));break;
			case 5:strncpy(di,"未",sizeof(di));break;
			case 6:strncpy(di,"午",sizeof(di));break;
			case 7:strncpy(di,"巳",sizeof(di));break;
			case 8:strncpy(di,"辰",sizeof(di));break;
			case 9:strncpy(di,"卯",sizeof(di));break;
			case 10:strncpy(di,"寅",sizeof(di));break;
			case 11:strncpy(di,"丑",sizeof(di));break;
		};
	}
	sprintf(result,"%s%s",tian,di);
	return result;
}


/*将一串数字 int型的转换成对应的汉字*/
/*参数type为类型：0转换为年格式，1转换为月格式，2转化为日格式*/
/*返回为最长10个汉字的字符串*/
char *Get_Lunar_Chinese(int n,int type)
{
	int gewei=0,shiwei=0,baiwei=0,qianwei=0;
	static char result[21];
	memset(result,0x00,sizeof(result));
	gewei=n%10;
	shiwei=(n%100)/10;
	baiwei=(n%1000)/100;
	qianwei=(n%10000)/1000;
	if(type==0)
	{
		if((n>=0)&&(n<=9))
		{
			strcpy(result,GetHanZi(gewei));
		}
		else if((n>=10)&&(n<=99))
		{
			strcpy(result,GetHanZi(shiwei));
			strcat(result,GetHanZi(gewei));
		}
		else if((n>=100)&&(n<=999))
		{
			strcpy(result,GetHanZi(baiwei));
			strcat(result,GetHanZi(shiwei));
			strcat(result,GetHanZi(gewei));
		}
		else if (n>=1000)
		{
			strcpy(result,GetHanZi(qianwei));
			strcat(result,GetHanZi(baiwei));
			strcat(result,GetHanZi(shiwei));
			strcat(result,GetHanZi(gewei));
		}
		else
		{
			strcpy(result,"错误");
		}
		
	}
	else if(type==1)
	{
		switch (n)
		{
			case 1:strcpy(result,"正月");break;
			case 2:strcpy(result,"二月");break;
			case 3:strcpy(result,"三月");break;
			case 4:strcpy(result,"四月");break;
			case 5:strcpy(result,"五月");break;
			case 6:strcpy(result,"六月");break;
			case 7:strcpy(result,"七月");break;
			case 8:strcpy(result,"八月");break;
			case 9:strcpy(result,"九月");break;
			case 10:strcpy(result,"十月");break;
			case 11:strcpy(result,"冬月");break;
			case 12:strcpy(result,"腊月");break;
			default:strcpy(result,"错误");break;
		};
	}
	else if(type==2)
	{
		switch (n)
		{
			case 1:strcpy(result,"初一");break;
			case 2:strcpy(result,"初二");break;
			case 3:strcpy(result,"初三");break;
			case 4:strcpy(result,"初四");break;
			case 5:strcpy(result,"初五");break;
			case 6:strcpy(result,"初六");break;
			case 7:strcpy(result,"初七");break;
			case 8:strcpy(result,"初八");break;
			case 9:strcpy(result,"初九");break;
			case 10:strcpy(result,"初十");break;
			case 11:strcpy(result,"十一");break;
			case 12:strcpy(result,"十二");break;
			case 13:strcpy(result,"十三");break;
			case 14:strcpy(result,"十四");break;
			case 15:strcpy(result,"十五");break;
			case 16:strcpy(result,"十六");break;
			case 17:strcpy(result,"十七");break;
			case 18:strcpy(result,"十八");break;
			case 19:strcpy(result,"十九");break;
			case 20:strcpy(result,"二十");break;
			case 21:strcpy(result,"廿一");break;
			case 22:strcpy(result,"廿二");break;
			case 23:strcpy(result,"廿三");break;
			case 24:strcpy(result,"廿四");break;
			case 25:strcpy(result,"廿五");break;
			case 26:strcpy(result,"廿六");break;
			case 27:strcpy(result,"廿七");break;
			case 28:strcpy(result,"廿八");break;
			case 29:strcpy(result,"廿九");break;
			case 30:strcpy(result,"三十");break;
			default:strcpy(result,"错误");break;
		};
	}
	return result;
}

/*初始化年信息*/
/*参数为公历或者农历的一年*/
int Init_Lunar_Year(int year)
{
	int i=0,m=0,addday=0;
	double dc=0;
	char xiazhi[3];
	memset(&lunaryear,0x00,sizeof(struct Lunar_Year));
	lunaryear.lyear=year-1;
	lunaryear.year=year;
	lunaryear.nyear=year+1;
	strcpy(lunaryear.lyearcn,Get_Lunar_Chinese(lunaryear.lyear,0));
	strcpy(lunaryear.yearcn,Get_Lunar_Chinese(lunaryear.year,0));
	strcpy(lunaryear.nyearcn,Get_Lunar_Chinese(lunaryear.nyear,0));
	strcpy(lunaryear.lganzhi,Get_Lunar_Year_GanZhi(lunaryear.lyear));
	strcpy(lunaryear.ganzhi,Get_Lunar_Year_GanZhi(lunaryear.year));
	strcpy(lunaryear.nganzhi,Get_Lunar_Year_GanZhi(lunaryear.nyear));
	strcpy(lunaryear.lshengxiao,Get_Lunar_YearSX(lunaryear.lganzhi));
	strcpy(lunaryear.shengxiao,Get_Lunar_YearSX(lunaryear.ganzhi));
	strcpy(lunaryear.nshengxiao,Get_Lunar_YearSX(lunaryear.nganzhi));
	strcpy(lunaryear.lnianhao,Get_Lunar_NianHao(lunaryear.lyear));
	strcpy(lunaryear.nianhao,Get_Lunar_NianHao(lunaryear.year));
	strcpy(lunaryear.nnianhao,Get_Lunar_NianHao(lunaryear.nyear));
	strcpy(lunaryear.jieqi[0],Get_Lunar_Year_AnyJieqi(lunaryear.lyear,21));
	strcpy(lunaryear.jieqi[1],Get_Lunar_Year_AnyJieqi(lunaryear.lyear,22));
	strcpy(lunaryear.jieqi[2],Get_Lunar_Year_AnyJieqi(lunaryear.lyear,23));
	strcpy(lunaryear.jieqi[3],Get_Lunar_Year_AnyJieqi(lunaryear.lyear,24));
	for(i=0;i<24;i++)
	{
		strcpy(lunaryear.jieqi[4+i],Get_Lunar_Year_AnyJieqi(lunaryear.year,i+1));
	}
	for(i=0;i<6;i++)
	{
		strcpy(lunaryear.jieqi[28+i],Get_Lunar_Year_AnyJieqi(lunaryear.nyear,i+1));
	}
	m=Get_Lunar_DongYueShuo(lunaryear.jieqi[1]);
	for(i=0;i<18;i++)
	{
		strcpy(lunaryear.shuori[i],Get_Lunar_M_Shuo(m+i));
	}
	dc=Get_Lunar_DayCha(Get_Lunar_M_Shuo(Get_Lunar_DongYueShuo(lunaryear.jieqi[25])),lunaryear.shuori[0]);
	lunaryear.daysum=(int)dc;
	if(lunaryear.daysum>=377)
	{
		lunaryear.rflag=1;
	}
	else
	{
		lunaryear.rflag=0;
	}
	for(i=0;i<9;i++)
	{
		if(i==0)
		{
			strcpy(lunaryear.jiufu[i],SubString(lunaryear.jieqi[1],0,8));
		}
		else
		{
			strcpy(lunaryear.jiufu[i],GetDate(lunaryear.jiufu[i-1],9));
		}
	}
	memset(xiazhi,0x00,sizeof(xiazhi));
	strcpy(xiazhi,SubString(Get_Lunar_Day_GanZhi(SubString(lunaryear.jieqi[13],0,8)),0,2));
	if(strcmp(xiazhi,"庚")==0)
	{
		addday=20;
	}
	else if(strcmp(xiazhi,"辛")==0)
	{
		addday=29;
	}
	else if(strcmp(xiazhi,"壬")==0)
	{
		addday=28;
	}
	else if(strcmp(xiazhi,"癸")==0)
	{
		addday=27;
	}
	else if(strcmp(xiazhi,"甲")==0)
	{
		addday=26;
	}
	else if(strcmp(xiazhi,"乙")==0)
	{
		addday=25;
	}
	else if(strcmp(xiazhi,"丙")==0)
	{
		addday=24;
	}
	else if(strcmp(xiazhi,"丁")==0)
	{
		addday=23;
	}
	else if(strcmp(xiazhi,"戊")==0)
	{
		addday=22;
	}
	else if(strcmp(xiazhi,"己")==0)
	{
		addday=21;
	}
	strcpy(lunaryear.jiufu[9],GetDate(SubString(lunaryear.jieqi[13],0,8),addday));
	strcpy(lunaryear.jiufu[10],GetDate(lunaryear.jiufu[9],10));
	memset(xiazhi,0x00,sizeof(xiazhi));
	strcpy(xiazhi,SubString(Get_Lunar_Day_GanZhi(SubString(lunaryear.jieqi[16],0,8)),0,2));
	if(strcmp(xiazhi,"庚")==0)
	{
		addday=0;
	}
	else if(strcmp(xiazhi,"辛")==0)
	{
		addday=9;
	}
	else if(strcmp(xiazhi,"壬")==0)
	{
		addday=8;
	}
	else if(strcmp(xiazhi,"癸")==0)
	{
		addday=7;
	}
	else if(strcmp(xiazhi,"甲")==0)
	{
		addday=6;
	}
	else if(strcmp(xiazhi,"乙")==0)
	{
		addday=5;
	}
	else if(strcmp(xiazhi,"丙")==0)
	{
		addday=4;
	}
	else if(strcmp(xiazhi,"丁")==0)
	{
		addday=3;
	}
	else if(strcmp(xiazhi,"戊")==0)
	{
		addday=2;
	}
	else if(strcmp(xiazhi,"己")==0)
	{
		addday=1;
	}
	strcpy(lunaryear.jiufu[11],GetDate(SubString(lunaryear.jieqi[16],0,8),addday));
	for(i=0;i<9;i++)
	{
		if(i==0)
		{
			strcpy(lunaryear.jiufu[i+12],SubString(lunaryear.jieqi[25],0,8));
		}
		else
		{
			strcpy(lunaryear.jiufu[i+12],GetDate(lunaryear.jiufu[i+11],9));
		}
	}
	if(year==2012)
	{
		/*这里有点小问题，按照计算出来的农历七月的朔日是在8月18的00点多*/
		/*实际应该是17号的23点54分，虽然误差不大，但这一点误差却造成了一天的差距*/
		/*所以手动更改了*/
		memset(lunaryear.shuori[9],0x00,sizeof(lunaryear.shuori[9]));
		strcpy(lunaryear.shuori[9],"20120817235400000");
	}
	return 0;
}


/*得到两个公历日期间的节气信息 包含date1,不包含date2*/
/*返回格式:大寒 YYYYMMDDHHMMSSMIL|立春 YYYYMMDDHHMMSSMIL*/
char *Get_Lunar_Date_Jieqi(char *date1,char *date2)
{
	int i=0,dc1=0,dc2=0;
	char d1[9];
	char d2[9];
	char tmpdate[9];
	static char result[60];
	memset(result,0x00,sizeof(result));
	memset(d1,0x00,sizeof(d1));
	memset(d2,0x00,sizeof(d2));
	if(strlen(date1)!=8)
	{
		strcpy(d1,SubString(date1,0,8));
	}
	else
	{
		strcpy(d1,date1);
	}
	if(strlen(date2)!=8)
	{
		strcpy(d2,SubString(date2,0,8));
	}
	else
	{
		strcpy(d2,date2);
	}
	strcpy(result,"");
	for(i=0;i<33;i++)
	{
		memset(tmpdate,0x00,sizeof(tmpdate));
		strcpy(tmpdate,SubString(lunaryear.jieqi[i],0,8));
		dc1=GetDayCha(d1,tmpdate);
		dc2=GetDayCha(d2,tmpdate);
		if((dc1<=0)&&(dc2>0))
		{
			if(strlen(result)==0)
			{
				strcat(result,Get_Lunar_JQName(i));
				strcat(result," ");
				strcat(result,lunaryear.jieqi[i]);
			}
			else
			{
				strcat(result,"|");
				strcat(result,Get_Lunar_JQName(i));
				strcat(result," ");
				strcat(result,lunaryear.jieqi[i]);
			}
		}
	}
	return result;
}

/*初始化农历月信息---此操作必须再初始化农历年信息之后才能进行*/
int Init_Lunar_Month()
{
	int i=0;
	memset(&lunarmonth,0x00,sizeof(struct Lunar_Month)*16);
	lunarmonth[0].year=lunaryear.lyear;
	lunarmonth[0].month=11;
	strcpy(lunarmonth[0].monthcn,Get_Lunar_Chinese(lunarmonth[0].month,1));
	strcpy(lunarmonth[0].chuyi,SubString(lunaryear.shuori[0],0,8));
	strcpy(lunarmonth[0].nchuyi,SubString(lunaryear.shuori[1],0,8));
	lunarmonth[0].daysum=GetDayCha(lunarmonth[0].nchuyi,lunarmonth[0].chuyi);
	if(lunarmonth[0].daysum==30)
		strcpy(lunarmonth[0].daxiao,"大");
	else if(lunarmonth[0].daysum==29)
		strcpy(lunarmonth[0].daxiao,"小");
	else strcpy(lunarmonth[0].daxiao,"错");
	strcpy(lunarmonth[0].jieqi,Get_Lunar_Date_Jieqi(lunarmonth[0].chuyi,lunarmonth[0].nchuyi));
	if(strlen(lunarmonth[0].jieqi)==0)
		lunarmonth[0].zqflag=0;
	else
	{
		if(strcon(lunarmonth[0].jieqi,"|")==0)
			lunarmonth[0].zqflag=1;
		else lunarmonth[0].zqflag=0;
	}
	if(lunarmonth[0].zqflag==1)
		strcpy(lunarmonth[0].runyue,"");
	else strcpy(lunarmonth[0].runyue,"闰");
	for(i=1;i<17;i++)
	{
		strcpy(lunarmonth[i].chuyi,SubString(lunaryear.shuori[i],0,8));
		strcpy(lunarmonth[i].nchuyi,SubString(lunaryear.shuori[i+1],0,8));
		lunarmonth[i].daysum=GetDayCha(lunarmonth[i].nchuyi,lunarmonth[i].chuyi);
		if(lunarmonth[i].daysum==30)
			strcpy(lunarmonth[i].daxiao,"大");
		else if(lunarmonth[i].daysum==29)
			strcpy(lunarmonth[i].daxiao,"小");
		else strcpy(lunarmonth[i].daxiao,"错");
		strcpy(lunarmonth[i].jieqi,Get_Lunar_Date_Jieqi(lunarmonth[i].chuyi,lunarmonth[i].nchuyi));
		
		if(strlen(lunarmonth[i].jieqi)==0)
			lunarmonth[i].zqflag=0;
		else
		{
			if(strcon(lunarmonth[i].jieqi,"|")==0)
				lunarmonth[i].zqflag=1;
			else lunarmonth[i].zqflag=0;
		}
		if(lunarmonth[i].zqflag==1)
		{
			strcpy(lunarmonth[i].runyue,"");
			lunarmonth[i].year=lunarmonth[i-1].year;
			lunarmonth[i].month=lunarmonth[i-1].month+1;
			if(lunarmonth[i].month==13)
			{
				lunarmonth[i].year++;
				lunarmonth[i].month=1;
			}
			strcpy(lunarmonth[i].monthcn,Get_Lunar_Chinese(lunarmonth[i].month,1));
		}
		else
		{
			strcpy(lunarmonth[i].runyue,"闰");
			lunarmonth[i].year=lunarmonth[i-1].year;
			lunarmonth[i].month=lunarmonth[i-1].month;
			strcpy(lunarmonth[i].monthcn,Get_Lunar_Chinese(lunarmonth[i].month,1));
		}
	}
	return 0;
}


/*初始化农历日信息---此操作必须再初始化农历年、农历月信息之后才能进行*/
int Init_Lunar_Day()
{
	int i=0,k=0;
	char tmpstr[40];
	memset(&lunarday,0x00,sizeof(struct Lunar_Day)*MAXLUNARDAY);
	
	Read_Lunar_Diy_Holiday();
	
	strcpy(lunarday[0].westday,lunarmonth[0].chuyi);
	
	
	sprintf(lunarday[0].eastday,"%04d1101",lunarmonth[0].year);
	if(strcmp(SubString(lunarday[0].eastday,strlen(lunarday[0].eastday)-2,2),"01")==0)
	{
		sprintf(lunarday[0].daycn,"%s%s%s",lunarmonth[0].runyue,lunarmonth[0].monthcn,lunarmonth[0].daxiao);
	}
	else
	{
		sprintf(lunarday[0].daycn,"%s%s%s",lunarmonth[0].runyue,lunarmonth[0].monthcn,Get_Lunar_Chinese(atoi(SubString(lunarday[0].eastday,strlen(lunarday[0].eastday)-2,2)),2));
	}
	strcpy(lunarday[0].weekday,GetWeek(lunarday[0].westday,"chinese"));
	strcpy(lunarday[0].ganzhi,Get_Lunar_Date_GanZhi(lunarday[0].westday));
	memset(tmpstr,0x00,sizeof(tmpstr));
	strcpy(tmpstr,Get_Lunar_Day_JieQi(lunarday[0].westday));
	if(strlen(tmpstr)==0)
	{
		strcpy(lunarday[0].jieqi,"");
		strcpy(lunarday[0].jieqitime,"");
	}
	else if(strcon(tmpstr,"#")!=0)
	{
		strcpy(lunarday[0].jieqi,tmpstr);
		strcpy(lunarday[0].jieqitime,"");
	}
	else if(strcon(tmpstr,"|")==0)
	{
		strcpy(lunarday[0].jieqi,"");
		strcat(lunarday[0].jieqi,SubString(tmpstr,0,Indexof(tmpstr,'#')));
		strcat(lunarday[0].jieqi,"  ");
		strcat(lunarday[0].jieqi,SubString(tmpstr,Indexof(tmpstr,'|')+1,strlen(tmpstr)-Indexof(tmpstr,'|')-1));
		strcpy(lunarday[0].jieqitime,SubString(tmpstr,Indexof(tmpstr,'#')+1,Indexof(tmpstr,'|')-Indexof(tmpstr,'#')-1));
	}
	else
	{
		strcpy(lunarday[0].jieqi,SubString(tmpstr,0,Indexof(tmpstr,'#')));
		strcpy(lunarday[0].jieqitime,SubString(tmpstr,Indexof(tmpstr,'#')+1,strlen(tmpstr)-Indexof(tmpstr,'#')-1));
	}
	if(strlen(lunarday[0].jieqitime)!=0)
	{
		memset(tmpstr,0x00,sizeof(tmpstr));
		strcpy(tmpstr,lunarday[0].jieqitime);
		memset(lunarday[0].jieqitime,0x00,sizeof(lunarday[0].jieqitime));
		sprintf(lunarday[0].jieqitime,"%s:%s:%s",SubString(tmpstr,8,2),SubString(tmpstr,10,2),SubString(tmpstr,12,2));
	}
	strcpy(lunarday[0].jieri,Get_Lunar_JieRi(lunarday[0].westday,lunarday[0].eastday));
	k=0;
	for(i=1;i<MAXLUNARDAY;i++)
	{
		strcpy(lunarday[i].westday,GetDate(lunarday[i-1].westday,1));
		if(strcmp(lunarday[i].westday,lunarmonth[k].nchuyi)==0)
		{
			k++;
			sprintf(lunarday[i].eastday,"%04d",lunarmonth[k].year);
			if(strlen(lunarmonth[k].runyue)!=0)
			{
				strcat(lunarday[i].eastday,"R");
			}
			memset(tmpstr,0x00,sizeof(tmpstr));
			sprintf(tmpstr,"%02d01",lunarmonth[k].month);
			strcat(lunarday[i].eastday,tmpstr);
			sprintf(lunarday[i].daycn,"%s%s%s",lunarmonth[k].runyue,lunarmonth[k].monthcn,lunarmonth[k].daxiao);
		}
		else
		{
			sprintf(lunarday[i].eastday,"%s%02d",SubString(lunarday[i-1].eastday,0,strlen(lunarday[i-1].eastday)-2),atoi(SubString(lunarday[i-1].eastday,strlen(lunarday[i-1].eastday)-2,2))+1);
			sprintf(lunarday[i].daycn,"%s%s%s",lunarmonth[k].runyue,lunarmonth[k].monthcn,Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,strlen(lunarday[i].eastday)-2,2)),2));
		}
		
		
		strcpy(lunarday[i].weekday,GetWeek(lunarday[i].westday,"chinese"));
		strcpy(lunarday[i].ganzhi,Get_Lunar_Date_GanZhi(lunarday[i].westday));
		memset(tmpstr,0x00,sizeof(tmpstr));
		strcpy(tmpstr,Get_Lunar_Day_JieQi(lunarday[i].westday));
		if(strlen(tmpstr)==0)
		{
			strcpy(lunarday[i].jieqi,"");
			strcpy(lunarday[i].jieqitime,"");
		}
		else if(strcon(tmpstr,"#")!=0)
		{
			strcpy(lunarday[i].jieqi,tmpstr);
			strcpy(lunarday[i].jieqitime,"");
		}
		else if(strcon(tmpstr,"|")==0)
		{
			strcpy(lunarday[i].jieqi,"");
			strcat(lunarday[i].jieqi,SubString(tmpstr,0,Indexof(tmpstr,'#')));
			strcat(lunarday[i].jieqi,"  ");
			strcat(lunarday[i].jieqi,SubString(tmpstr,Indexof(tmpstr,'|')+1,strlen(tmpstr)-Indexof(tmpstr,'|')-1));
			strcpy(lunarday[i].jieqitime,SubString(tmpstr,Indexof(tmpstr,'#')+1,Indexof(tmpstr,'|')-Indexof(tmpstr,'#')-1));
		}
		else
		{
			strcpy(lunarday[i].jieqi,SubString(tmpstr,0,Indexof(tmpstr,'#')));
			strcpy(lunarday[i].jieqitime,SubString(tmpstr,Indexof(tmpstr,'#')+1,strlen(tmpstr)-Indexof(tmpstr,'#')-1));
		}
		if(strlen(lunarday[i].jieqitime)!=0)
		{
			memset(tmpstr,0x00,sizeof(tmpstr));
			strcpy(tmpstr,lunarday[i].jieqitime);
			memset(lunarday[i].jieqitime,0x00,sizeof(lunarday[i].jieqitime));
			sprintf(lunarday[i].jieqitime,"%s:%s:%s",SubString(tmpstr,8,2),SubString(tmpstr,10,2),SubString(tmpstr,12,2));
		}
		strcpy(lunarday[i].jieri,Get_Lunar_JieRi(lunarday[i].westday,lunarday[i].eastday));
	}
	return 0;
}


/*日历最上面的一行显示信息--显示当前月的两个（或者一个）节气信息*/
/*返回格式如：小寒:2012年01月06日 18:38:25   大寒:2012年01月21日 00:12:45*/
char *Prf_Lunar_Month_JieQi(char *date1,char *date2)
{
	char tmpstr[60];
	char str1[30];
	char str2[30];
	static char result[100];
	memset(tmpstr,0x00,sizeof(tmpstr));
	memset(result,0x00,sizeof(result));
	memset(str1,0x00,sizeof(str1));
	memset(str2,0x00,sizeof(str2));
	strcpy(tmpstr,Get_Lunar_Date_Jieqi(date1,date2));
	sprintf(str1,"%s:%s年%s月%s日 %s:%s:%s",SubString(tmpstr,0,4),SubString(tmpstr,5,4),SubString(tmpstr,9,2),SubString(tmpstr,11,2),SubString(tmpstr,13,2),SubString(tmpstr,15,2),SubString(tmpstr,17,2));
	if(strcon(tmpstr,"|")==0)
	{
		sprintf(str2,"%s:%s年%s月%s日 %s:%s:%s",SubString(tmpstr,23,4),SubString(tmpstr,28,4),SubString(tmpstr,32,2),SubString(tmpstr,34,2),SubString(tmpstr,36,2),SubString(tmpstr,38,2),SubString(tmpstr,40,2));
		sprintf(result,"%s    %s",str1,str2);
	}
	else
	{
		strcpy(result,str1);
	}
	return result;
}

/*按星期模块设定位置打印具体信息*/
/*参数一：从日信息的K位置开始打印*/
/*参数二：包含K共打印num天*/
/*参数三：从第几个位置开始打印，0表示第一个，6表示最后一个*/
int Prf_Cal_As_WeekMode(int now,int num,int type)
{
	int i=0,day=0,dex1=0,kong=0,k=0,zuo=0,you=0,len=0,ban=0;
	char glpf[30];
	char nlpf[10];
	char jieri[51];
	switch (type)
	{
		case 0:kong=1;break;
		case 1:kong=19;break;
		case 2:kong=37;break;
		case 3:kong=55;break;
		case 4:kong=73;break;
		case 5:kong=91;break;
		case 6:kong=109;break;
	};
	/*每一个模块长度占18位，前后各先空出一个空格来，还剩16位*/
	/*先打公历信息*/
	
	for(k=0;k<kong;k++)
	{
		printf(" ");
	}	
	for(i=now;i<now+num;i++)
	{
		/*先判断当天的节日信息*/
		memset(jieri,0x00,sizeof(jieri));
		memset(glpf,0x00,sizeof(glpf));
		if(strlen(lunarday[i].jieri)==0)
		{
			strcpy(glpf,SubString(lunarday[i].westday,6,2));
			/*
			day=atoi(glpf);
			memset(glpf,0x00,sizeof(glpf));
			sprintf(glpf,"%d",day);
			*/
		}
		else
		{
			strcpy(jieri,lunarday[i].jieri);
			dex1=Indexof(jieri,'|');
			if(dex1==(-1))
			{
				/*如果只存在公历*/
				strcpy(glpf,jieri);
				strrep(glpf,"#","  ");
			}
			else if(dex1==0)
			{
				strcpy(glpf,SubString(lunarday[i].westday,6,2));
				/*
				day=atoi(glpf);
				memset(glpf,0x00,sizeof(glpf));
				sprintf(glpf,"%d",day);
				*/
			}
			else
			{
				strcpy(glpf,SubString(jieri,0,dex1));
				strrep(glpf,"#","  ");
			}		
		}
		printf(" ");
		len=16-strlen(glpf);
		ban=len/2;
		if(ban*2==len)
		{
			zuo=ban;
			you=ban;
		}
		else
		{
			zuo=ban+1;
			you=ban;
		}
		if(zuo!=0)
		{
			for(k=0;k<zuo;k++)
			{
				printf(" ");
			}
		}
		printf("%s",glpf);
		if(you!=0)
		{
			for(k=0;k<you;k++)
			{
				printf(" ");
			}
		}
		printf(" ");		
	}
	printf("\n");
	/*再打印农历的信息*/
	
	for(k=0;k<kong;k++)
	{
		printf(" ");
	}	
	for(i=now;i<now+num;i++)
	{
		/*先判断当天的节日信息*/
		memset(jieri,0x00,sizeof(jieri));
		memset(nlpf,0x00,sizeof(nlpf));
		
		if(strlen(lunarday[i].jieri)==0)
		{
			strcpy(nlpf,"");
		}
		else
		{
			strcpy(jieri,lunarday[i].jieri);
			dex1=Indexof(jieri,'|');
			if(dex1==(-1))
			{
				strcpy(nlpf,"");
			}
			else
			{
				strcpy(nlpf,SubString(jieri,dex1+1,strlen(jieri)-dex1-1));
				strrep(glpf,"@","  ");
			}
		}
		if(strlen(lunarday[i].jieqi)!=0)
		{
			if(strlen(nlpf)==0)
			{
				strcpy(nlpf,lunarday[i].jieqi);
			}
			else
			{
				strcat(nlpf,"  ");
				strcat(nlpf,lunarday[i].jieqi);
			}
		}
		if(strlen(nlpf)==0)
		{
			strcpy(nlpf,lunarday[i].daycn);
		}
		
		
		printf(" ");
		len=16-strlen(nlpf);
		ban=len/2;
		if(ban*2==len)
		{
			zuo=ban;
			you=ban;
		}
		else
		{
			zuo=ban;
			you=ban+1;
		}
		if(zuo!=0)
		{
			for(k=0;k<zuo;k++)
			{
				printf(" ");
			}
		}
		printf("%s",nlpf);
		if(you!=0)
		{
			for(k=0;k<you;k++)
			{
				printf(" ");
			}
		}
		printf(" ");		
	}
	printf("\n");
	printf("\n");
	return 0;
}


/*打印某一年（或者某一个月）的所有信息，以日历的方式打印*/
int PrfCalendar(int pmonth)
{
	int i=0,k=0,nowyear=0,num=0,j=0,end=0,nowmonth=0,nextmonth=0,kg=0,ban=0;
	char bdate[9];
	char date1[9];
	char date2[9];
	char tmpdate[9];
	char tmpstr[200];
	char wkday[10];
	char nowganzhi[5];
	char nowshengxiao[5];
	memset(bdate,0x00,sizeof(bdate));
	nowyear=lunaryear.year;
	/*先得到公历year年的0101*/
	if((pmonth>12)||(pmonth<1))
	{
		end=12;
		nowmonth=1;
	}
	else
	{	
		end=1;
		nowmonth=pmonth;
	}
	sprintf(bdate,"%04d%02d01",nowyear,nowmonth);
	
	for(i=0;i<MAXLUNARDAY;i++)
	{
		if(strcasecmp(lunarday[i].westday,bdate)==0)
		{
			k=i;
			break;
		}	
	}
	for(i=1;i<=end;i++)
	{
		if(nowmonth==13)
		{
			nowmonth=1;
			nowyear++;
		}
		memset(nowganzhi,0x00,sizeof(nowganzhi));
		memset(nowshengxiao,0x00,sizeof(nowshengxiao));
		strcpy(nowganzhi,Get_Lunar_Year_GanZhi(atoi(SubString(lunarday[k].eastday,0,4))));
		strcpy(nowshengxiao,Get_Lunar_YearSX(nowganzhi));
		/*
		if(nowyear>1949)
		{
			printf("\n\n\n\t\t\t\t\t\t%04d年%d月 农历 %s年 生肖 %s\n\n",nowyear,nowmonth,nowganzhi,nowshengxiao);
		}
		else
		{
			printf("\n\n\n\t\t\t\t\t%04d年%d月 %s 农历 %s年 生肖 %s\n\n",nowyear,nowmonth,Get_Lunar_NianHao(atoi(SubString(lunarday[k].eastday,0,4))),nowganzhi,nowshengxiao);
		}
		*/
		memset(tmpstr,0x00,sizeof(tmpstr));
		sprintf(tmpstr,"%04d年%d月 %s 农历 %s年 生肖 %s",nowyear,nowmonth,Get_Lunar_NianHao(atoi(SubString(lunarday[k].eastday,0,4))),nowganzhi,nowshengxiao);
		ban=(128-strlen(tmpstr))/2;
		printf("\n\n\n");
		for(kg=0;kg<ban;kg++)
		{
			printf(" ");
		}
		printf("%s\n\n",tmpstr);
		memset(date1,0x00,sizeof(date1));
		memset(tmpdate,0x00,sizeof(tmpdate));
		sprintf(date1,"%04d%02d01",nowyear,nowmonth);
		nextmonth=nowmonth+1;
		if(nextmonth==13)
		{
			nextmonth=1;
			sprintf(tmpdate,"%04d%02d01",nowyear+1,nextmonth);
		}
		else
		{
			sprintf(tmpdate,"%04d%02d01",nowyear,nextmonth);
		}
		
		for(kg=0;kg<34;kg++)
		{
			printf(" ");
		}
		printf("%s\n",Prf_Lunar_Month_JieQi(date1,tmpdate));
		printf("--------------------------------------------------------------------------------------------------------------------------------\n");
		printf("       星期日            星期一            星期二            星期三            星期四            星期五            星期六\n\n");
		while(1)
		{
			if(strcasecmp(lunarday[k].westday,tmpdate)==0)
			{
				break;
			}
			memset(wkday,0x00,sizeof(wkday));
			strcpy(wkday,lunarday[k].weekday);
			if(strcasecmp(wkday,"星期日")==0)
			{
				num=1;
				for(j=1;j<=6;j++)
				{
					if(strcasecmp(lunarday[k+j].westday,tmpdate)==0)
					{
						break;
					}
					num++;
				}
				Prf_Cal_As_WeekMode(k,num,0);
				k=k+num;
			}
			else if(strcasecmp(wkday,"星期一")==0)
			{
				num=1;
				for(j=1;j<=5;j++)
				{
					if(strcasecmp(lunarday[k+j].westday,tmpdate)==0)
					{
						break;
					}
					num++;
				}
				Prf_Cal_As_WeekMode(k,num,1);
				k=k+num;
			}
			else if(strcasecmp(wkday,"星期二")==0)
			{
				num=1;
				for(j=1;j<=4;j++)
				{
					if(strcasecmp(lunarday[k+j].westday,tmpdate)==0)
					{
						break;
					}
					num++;
				}
				Prf_Cal_As_WeekMode(k,num,2);
				k=k+num;
			}
			else if(strcasecmp(wkday,"星期三")==0)
			{
				num=1;
				for(j=1;j<=3;j++)
				{
					if(strcasecmp(lunarday[k+j].westday,tmpdate)==0)
					{
						break;
					}
					num++;
				}
				Prf_Cal_As_WeekMode(k,num,3);
				k=k+num;
			}
			else if(strcasecmp(wkday,"星期四")==0)
			{
				num=1;
				for(j=1;j<=2;j++)
				{
					if(strcasecmp(lunarday[k+j].westday,tmpdate)==0)
					{
						break;
					}
					num++;
				}
				Prf_Cal_As_WeekMode(k,num,4);
				k=k+num;
			}
			else if(strcasecmp(wkday,"星期五")==0)
			{
				num=1;
				for(j=1;j<=1;j++)
				{
					if(strcasecmp(lunarday[k+j].westday,tmpdate)==0)
					{
						break;
					}
					num++;
				}
				Prf_Cal_As_WeekMode(k,num,5);
				k=k+num;
			}
			else if(strcasecmp(wkday,"星期六")==0)
			{
				Prf_Cal_As_WeekMode(k,1,6);
				k=k+1;
			}
		}
		printf("--------------------------------------------------------------------------------------------------------------------------------\n\n");
		nowmonth++;
	}
	
	printf("注意：由于农历二十四节气交节时刻、朔月时刻采用近似算法，可能存在少量误差(120分钟内)\n");
	return 0;
}


/*初始化农历数据*/
int InitLunarCal(int year)
{
	Init_Lunar_Year(year);
	Init_Lunar_Month();
	Init_Lunar_Day();
	return 0;
}

/*打印某一天的详细信息，此函数可直接调用，不需要初始化数据*/
int PrfOneDay(char *date,char *type)
{
	int i=0,year=0,dex=0,dex1=0,len=0,pflag=0;
	char tmpdate[10];
	char glj[20];
	char nlj[20];
	char tmpstr[15];
	char jiufu[15];
	year=atoi(SubString(date,0,4));
	InitLunarCal(year);
	for(i=0;i<MAXLUNARDAY;i++)
	{
		memset(tmpdate,0x00,sizeof(tmpdate));
		if(strcasecmp(type,"-l")==0)
		{
			strcpy(tmpdate,lunarday[i].eastday);
		}
		else
		{
			strcpy(tmpdate,lunarday[i].westday);
		}
		if(strcasecmp(tmpdate,date)==0)
		{
			printf("%s   %s  生肖 %s\n\n",Get_Lunar_NianHao(atoi(SubString(lunarday[i].eastday,0,4))),SubString(lunarday[i].ganzhi,0,4),Get_Lunar_YearSX(SubString(lunarday[i].ganzhi,0,4)));
			printf("西元日期：%s年%s月%s日 %s\n",SubString(lunarday[i].westday,0,4),SubString(lunarday[i].westday,4,2),SubString(lunarday[i].westday,6,2),lunarday[i].weekday);
			printf("农历日期：%s年",Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,0,4)),0));
			if(strcasecon(lunarday[i].eastday,"R")==0)
			{
				printf("闰");
			}
			len=strlen(lunarday[i].eastday);
			printf("%s",Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,len-4,2)),1));
			printf("%s\n",Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,len-2,2)),2));
			printf("干支：%s\n",lunarday[i].ganzhi);
			memset(jiufu,0x00,sizeof(jiufu));
			strcpy(jiufu,Get_Lunar_JiuFu_Num(lunarday[i].westday));
			len=strlen(lunarday[i].jieqi);
			if(len!=0)
			{
				if(strcon(lunarday[i].jieqi," ")==0)
				{
					dex=Indexof(lunarday[i].jieqi,' ');
					printf("这天是%s，并且是%s第一天，%s时刻为%s\n",SubString(lunarday[i].jieqi,0,dex),SubString(lunarday[i].jieqi,dex+1,len-dex-1),SubString(lunarday[i].jieqi,0,dex),lunarday[i].jieqitime);	
				}
				else
				{
					if(strlen(lunarday[i].jieqitime)==0)
					{
						printf("这天是%s第一天\n",lunarday[i].jieqi);
					}
					else
					{
						if(strlen(jiufu)!=0)
						{
							printf("这天是%s，并且是%s，%s时刻为%s\n",lunarday[i].jieqi,jiufu,lunarday[i].jieqi,lunarday[i].jieqitime);
						}
						else
						{
							printf("这天是%s，时刻为%s\n",lunarday[i].jieqi,lunarday[i].jieqitime);
						}
					}
				}
				pflag=1;
			}
			else
			{
				if(strlen(jiufu)!=0)
				{
					printf("这天是%s\n",jiufu);
					pflag=1;
				}
			}
			memset(tmpstr,0x00,sizeof(tmpstr));
			if(pflag==1)
			{
				strcpy(tmpstr,"另外，这天还是");
			}
			else
			{
				strcpy(tmpstr,"这天是");
			}
			len=strlen(lunarday[i].jieri);
			if(len!=0)
			{
				dex=Indexof(lunarday[i].jieri,'|');
				if(dex==(-1))
				{
					if(strcon(lunarday[i].jieri,"#")==0)
					{
						dex1=Indexof(lunarday[i].jieri,'#');
						printf("%s%s、%s\n",tmpstr,SubString(lunarday[i].jieri,0,dex1),SubString(lunarday[i].jieri,dex1+1,len-dex1-1));
					}
					else
					{
						printf("%s%s\n",tmpstr,lunarday[i].jieri);
					}
				}
				else
				{
					if(dex==0)
					{
						if(strcon(lunarday[i].jieri,"@")==0)
						{
							dex1=Indexof(lunarday[i].jieri,'@');
							printf("%s%s、%s\n",tmpstr,SubString(lunarday[i].jieri,1,dex1-1),SubString(lunarday[i].jieri,dex1+1,len-dex1-1));
						}
						else
						{
							printf("%s%s\n",tmpstr,SubString(lunarday[i].jieri,1,strlen(lunarday[i].jieri)-1));
						}
					}
					else
					{
						memset(glj,0x00,sizeof(glj));
						memset(nlj,0x00,sizeof(nlj));
						
						strcpy(glj,SubString(lunarday[i].jieri,0,Indexof(lunarday[i].jieri,'|')));
						strcpy(nlj,SubString(lunarday[i].jieri,Indexof(lunarday[i].jieri,'|')+1,len-Indexof(lunarday[i].jieri,'|')-1));
						
						printf("%s",tmpstr);
						len=strlen(glj);
						if(strcon(glj,"#")==0)
						{
							dex1=Indexof(glj,'#');
							printf("%s、%s、",SubString(glj,0,dex1),SubString(glj,dex1+1,len-dex1-1));
						}
						else
						{
							printf("%s、",glj);
						}
						len=strlen(glj);
						if(strcon(nlj,"@")==0)
						{
							dex1=Indexof(nlj,'@');
							printf("%s、%s\n",SubString(nlj,0,dex1),SubString(nlj,dex1+1,len-dex1-1));
						}
						else
						{
							printf("%s\n",nlj);
						}
					}
				}
			}
			break;
		}
	}
	return 0;
}


/*农历和公历相互转换--接口模式*/
/*参数一：公历或者农历日期，公历时为八位，农历时可能为九位*/
/*参数二：转换类型，-l 转换成农历   -g 转换成公历*/
/*返回：八位或者九位的日期*/
char *ConvertGL(char *date,char *type)
{
	int i=0,year=0;
	static char result[10];
	memset(result,0x00,sizeof(result));
	year=atoi(SubString(date,0,4));
	InitLunarCal(year);
	
	strcpy(result,"");
	if(strcasecmp(type,"-l")==0)
	{
		for(i=0;i<MAXLUNARDAY;i++)
		{
			if(strcasecmp(lunarday[i].westday,date)==0)
			{
				strcpy(result,lunarday[i].eastday);
				break;
			}
		}
	}
	else if(strcasecmp(type,"-g")==0)
	{
		for(i=0;i<MAXLUNARDAY;i++)
		{
			if(strcasecmp(lunarday[i].eastday,date)==0)
			{
				strcpy(result,lunarday[i].westday);
				break;
			}
		}
	}
	return result;
}

/* 得到某个时间对应的干支 */
/* 参数一为当天（00:00-23:59）的日干支，参数二为int型的小时整数，取0-23 */
/* 返回为当前的时辰干支 */
/* 当hour为23时，按照规则，将当前日干支加一，然后计算的 */
char *Get_Lunar_BZ_Hour(char *daygz,int hour)
{
	char tmpgz[5];
	static char result[10];
	memset(result,0x00,sizeof(result));
	switch(hour)
	{
		case 23:
			memset(tmpgz,0x00,sizeof(tmpgz));
			strcpy(tmpgz,Add_Lunar_JiaZi(daygz,1));
			if((strcon(tmpgz,"甲")==0)||(strcon(tmpgz,"己")==0))
			{
				strcpy(result,"甲");
			}
			else if((strcon(tmpgz,"乙")==0)||(strcon(tmpgz,"庚")==0))
			{
				strcpy(result,"丙");
			}
			else if((strcon(tmpgz,"丙")==0)||(strcon(tmpgz,"辛")==0))
			{
				strcpy(result,"戊");
			}
			else if((strcon(tmpgz,"丁")==0)||(strcon(tmpgz,"壬")==0))
			{
				strcpy(result,"庚");
			}
			else if((strcon(tmpgz,"戊")==0)||(strcon(tmpgz,"癸")==0))
			{
				strcpy(result,"壬");
			}
			break;
		case 0:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"甲");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"丙");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"戊");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"庚");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"壬");
			}
			break;
		case 1:
		case 2:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"乙");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"丁");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"己");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"辛");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"癸");
			}
			break;
		case 3:
		case 4:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"丙");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"戊");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"庚");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"壬");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"甲");
			}
			break;
		case 5:
		case 6:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"丁");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"己");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"辛");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"癸");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"乙");
			}
			break;
		case 7:
		case 8:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"戊");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"庚");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"壬");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"甲");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"丙");
			}
			break;
		case 9:
		case 10:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"己");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"辛");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"癸");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"乙");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"丁");
			}
			break;
		case 11:
		case 12:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"庚");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"壬");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"甲");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"丙");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"戊");
			}
			break;
		case 13:
		case 14:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"辛");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"癸");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"乙");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"丁");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"己");
			}
			break;
		case 15:
		case 16:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"壬");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"甲");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"丙");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"戊");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"庚");
			}
			break;
		case 17:
		case 18:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"癸");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"乙");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"丁");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"己");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"辛");
			}
			break;
		case 19:
		case 20:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"甲");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"丙");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"戊");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"庚");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"壬");
			}
			break;
		case 21:
		case 22:
			if((strcon(daygz,"甲")==0)||(strcon(daygz,"己")==0))
			{
				strcpy(result,"乙");
			}
			else if((strcon(daygz,"乙")==0)||(strcon(daygz,"庚")==0))
			{
				strcpy(result,"丁");
			}
			else if((strcon(daygz,"丙")==0)||(strcon(daygz,"辛")==0))
			{
				strcpy(result,"己");
			}
			else if((strcon(daygz,"丁")==0)||(strcon(daygz,"壬")==0))
			{
				strcpy(result,"辛");
			}
			else if((strcon(daygz,"戊")==0)||(strcon(daygz,"癸")==0))
			{
				strcpy(result,"癸");
			}
			break;
	};
	
	switch(hour)
	{
		case 23:
		case 0:strcat(result,"子");break;
		case 1:
		case 2:strcat(result,"丑");break;
		case 3:
		case 4:strcat(result,"寅");break;
		case 5:
		case 6:strcat(result,"卯");break;
		case 7:
		case 8:strcat(result,"辰");break;
		case 9:
		case 10:strcat(result,"巳");break;
		case 11:
		case 12:strcat(result,"午");break;
		case 13:
		case 14:strcat(result,"未");break;
		case 15:
		case 16:strcat(result,"申");break;
		case 17:
		case 18:strcat(result,"酉");break;
		case 19:
		case 20:strcat(result,"戌");break;
		case 21:
		case 22:strcat(result,"亥");break;
	};
	return result;
}


/*得到生辰八字*/
/*参数：10位公历日期 YYYYMMDDHH*/
/*返回：15位字符串，八字生辰 年月日时之间用空格间隔*/
char *Get_ZB_BaZi(char *datestr)
{
	int i=0,year=0,hour=0;
	char date[9];
	char dayganzhi[15];
	char hourgz[5];
	static char result[20];
	
	memset(date,0x00,sizeof(date));
	memset(dayganzhi,0x00,sizeof(dayganzhi));
	memset(hourgz,0x00,sizeof(hourgz));
	
	year=atoi(SubString(datestr,0,4));
	hour=atoi(SubString(datestr,8,2));
	InitLunarCal(year);

	strcpy(date,SubString(datestr,0,8));
	for(i=0;i<MAXLUNARDAY;i++)
	{
		if(strcmp(lunarday[i].westday,date)==0)
		{
			strcpy(dayganzhi,lunarday[i].ganzhi);
			break;
		}
	}
	strcpy(hourgz,Get_Lunar_BZ_Hour(SubString(dayganzhi,10,4),hour));
	
	memset(result,0x00,sizeof(result));
	sprintf(result,"%s %s",dayganzhi,hourgz);
	WriteLog(LOGLVL,"八字：%s",result);
	return result;
}


/* 干支和五行的对应关系，得到干支对应的五行 */
/* 参数为天干或者地支 */
/* 返回结果为五行之一 */
char *Get_Lunar_BZWX_Link(char *str)
{
	static char result[5];
	memset(result,0x00,sizeof(result));
	if((strcmp(str,"庚")==0)||(strcmp(str,"辛")==0)||(strcmp(str,"申")==0)||(strcmp(str,"酉")==0))
	{
		strcpy(result,"金");
	}
	else if((strcmp(str,"甲")==0)||(strcmp(str,"乙")==0)||(strcmp(str,"寅")==0)||(strcmp(str,"卯")==0))
	{
		strcpy(result,"木");
	}
	else if((strcmp(str,"壬")==0)||(strcmp(str,"癸")==0)||(strcmp(str,"子")==0)||(strcmp(str,"亥")==0))
	{
		strcpy(result,"水");
	}
	else if((strcmp(str,"丙")==0)||(strcmp(str,"丁")==0)||(strcmp(str,"巳")==0)||(strcmp(str,"午")==0))
	{
		strcpy(result,"火");
	}
	else if((strcmp(str,"戊")==0)||(strcmp(str,"己")==0)||(strcmp(str,"丑")==0)||(strcmp(str,"辰")==0)||(strcmp(str,"未")==0)||(strcmp(str,"戌")==0))
	{
		strcpy(result,"土");
	}	
	return result;
}


/* 得到五行 根据八字得到五行 */
/* 参数为八字 可是是连续的八字，也可以是中间用空格的八字*/
/* 结果为五行 中间用空格间隔*/
char *Get_ZB_WuXing(char *bzstr)
{
	int i=0;
	char tmpstr[20];
	static char result[20];
	memset(result,0x00,sizeof(result));
	memset(tmpstr,0x00,sizeof(tmpstr));
	strcpy(tmpstr,bzstr);
	if(strcon(tmpstr," ")==0)
	{
		strrep(tmpstr," ","");
	}
	strcpy(result,"");
	for(i=0;i<8;i++)
	{
		strcat(result,Get_Lunar_BZWX_Link(SubString(tmpstr,i*2,2)));
		if((i%2)==1)
			strcat(result," ");
	}
	trim(result);
	WriteLog(LOGLVL,"五行：%s",result);
	return result;
}


/* 纳音与六十甲子关系，此函数根据甲子得到纳音 */
/* 参数为甲子 */
/* 结果为纳音 */
char *Get_Lunar_JZNY_Link(char *str)
{
	static char result[10];
	memset(result,0x00,sizeof(result));
	if((strcmp(str,"甲子")==0)||(strcmp(str,"乙丑")==0	))
	{
		strcpy(result,"海中金");
	}
	else if((strcmp(str,"丙寅")==0)||(strcmp(str,"丁卯")==0	))
	{
		strcpy(result,"炉中火");
	}
	else if((strcmp(str,"戊辰")==0)||(strcmp(str,"己巳")==0	))
	{
		strcpy(result,"大林木");
	}
	else if((strcmp(str,"庚午")==0)||(strcmp(str,"辛未")==0	))
	{
		strcpy(result,"路旁土");
	}
	else if((strcmp(str,"壬申")==0)||(strcmp(str,"癸酉")==0	))
	{
		strcpy(result,"剑锋金");
	}
	else if((strcmp(str,"甲戌")==0)||(strcmp(str,"乙亥")==0	))
	{
		strcpy(result,"山头火");
	}
	else if((strcmp(str,"丙子")==0)||(strcmp(str,"丁丑")==0	))
	{
		strcpy(result,"涧下水");
	}
	else if((strcmp(str,"戊寅")==0)||(strcmp(str,"己卯")==0	))
	{
		strcpy(result,"城头土");
	}
	else if((strcmp(str,"庚辰")==0)||(strcmp(str,"辛巳")==0	))
	{
		strcpy(result,"白蜡金");
	}
	else if((strcmp(str,"壬午")==0)||(strcmp(str,"癸未")==0	))
	{
		strcpy(result,"杨柳木");
	}
	else if((strcmp(str,"甲申")==0)||(strcmp(str,"乙酉")==0	))
	{
		strcpy(result,"泉中水");
	}
	else if((strcmp(str,"丙戌")==0)||(strcmp(str,"丁亥")==0	))
	{
		strcpy(result,"屋上土");
	}
	else if((strcmp(str,"戊子")==0)||(strcmp(str,"己丑")==0	))
	{
		strcpy(result,"霹雳火");
	}
	else if((strcmp(str,"庚寅")==0)||(strcmp(str,"辛卯")==0	))
	{
		strcpy(result,"松柏木");
	}
	else if((strcmp(str,"壬辰")==0)||(strcmp(str,"癸巳")==0	))
	{
		strcpy(result,"长流水");
	}
	else if((strcmp(str,"甲午")==0)||(strcmp(str,"乙未")==0	))
	{
		strcpy(result,"砂中金");
	}
	else if((strcmp(str,"丙申")==0)||(strcmp(str,"丁酉")==0	))
	{
		strcpy(result,"山下火");
	}
	else if((strcmp(str,"戊戌")==0)||(strcmp(str,"己亥")==0	))
	{
		strcpy(result,"平地木");
	}
	else if((strcmp(str,"庚子")==0)||(strcmp(str,"辛丑")==0	))
	{
		strcpy(result,"壁上土");
	}
	else if((strcmp(str,"壬寅")==0)||(strcmp(str,"癸卯")==0	))
	{
		strcpy(result,"金箔金");
	}
	else if((strcmp(str,"甲辰")==0)||(strcmp(str,"乙巳")==0	))
	{
		strcpy(result,"覆灯火");
	}
	else if((strcmp(str,"丙午")==0)||(strcmp(str,"丁未")==0	))
	{
		strcpy(result,"天河水");
	}
	else if((strcmp(str,"戊申")==0)||(strcmp(str,"己酉")==0	))
	{
		strcpy(result,"大驿土");
	}
	else if((strcmp(str,"庚戌")==0)||(strcmp(str,"辛亥")==0	))
	{
		strcpy(result,"钗钏金");
	}
	else if((strcmp(str,"壬子")==0)||(strcmp(str,"癸丑")==0	))
	{
		strcpy(result,"桑松木");
	}
	else if((strcmp(str,"甲寅")==0)||(strcmp(str,"乙卯")==0	))
	{
		strcpy(result,"大溪水");
	}
	else if((strcmp(str,"丙辰")==0)||(strcmp(str,"丁巳")==0	))
	{
		strcpy(result,"沙中土");
	}
	else if((strcmp(str,"戊午")==0)||(strcmp(str,"己未")==0	))
	{
		strcpy(result,"天上火");
	}
	else if((strcmp(str,"庚申")==0)||(strcmp(str,"辛酉")==0	))
	{
		strcpy(result,"石榴木");
	}
	else if((strcmp(str,"壬戌")==0)||(strcmp(str,"癸亥")==0	))
	{
		strcpy(result,"大海水");
	}
	return result;
}


/* 得到五行纳音 根据八字得到五行纳音 */
/* 参数为八字 可是是连续的八字，也可以是中间用空格的八字*/
/* 结果为纳音，共计汉字3*4=12个 中间用空格间隔 */
char *Get_ZB_NaYin(char *bzstr)
{
	int i=0;
	char tmpstr[20];
	static char result[30];
	memset(result,0x00,sizeof(result));
	memset(tmpstr,0x00,sizeof(tmpstr));
	strcpy(tmpstr,bzstr);
	if(strcon(tmpstr," ")==0)
	{
		strrep(tmpstr," ","");
	}
	strcpy(result,"");
	for(i=0;i<4;i++)
	{
		strcat(result,Get_Lunar_JZNY_Link(SubString(tmpstr,i*4,4)));
		strcat(result," ");
	}
	trim(result);
	WriteLog(LOGLVL,"纳音：%s",result);
	return result;
}


/*公历和农历转换--转换成简易信息，供打印使用*/
/*参数一：公历或者农历日期，为通过格式，农历可能包含R*/
/*参数二：转换类型，-l 转换成农历  -g转换成公历*/
/*返回：简易的农历或者公历信息*/
char *ConvertGL_Info(char *date,char *type)
{
	int i=0,len=0,year=0;
	static char result[80];
	memset(result,0x00,sizeof(result));
	year=atoi(SubString(date,0,4));
	InitLunarCal(year);
	
	strcpy(result,"");
	if(strcasecmp(type,"-l")==0)
	{
		for(i=0;i<MAXLUNARDAY;i++)
		{
			if(strcasecmp(lunarday[i].westday,date)==0)
			{
				sprintf(result,"%s  %s年",SubString(lunarday[i].ganzhi,0,4),Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,0,4)),0));
				if(strcasecon(lunarday[i].eastday,"R")==0)
				{
					strcat(result,"闰");
				}
				len=strlen(lunarday[i].eastday);
				strcat(result,Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,len-4,2)),1));
				strcat(result,Get_Lunar_Chinese(atoi(SubString(lunarday[i].eastday,len-2,2)),2));
				strcat(result,"  生肖");
				strcat(result,Get_Lunar_YearSX(SubString(lunarday[i].ganzhi,0,4)));
				break;
			}
		}
	}
	else if(strcasecmp(type,"-g")==0)
	{
		for(i=0;i<MAXLUNARDAY;i++)
		{
			if(strcasecmp(lunarday[i].eastday,date)==0)
			{
				sprintf(result,"公元%s年%s月%s日",SubString(lunarday[i].westday,0,4),SubString(lunarday[i].westday,4,2),SubString(lunarday[i].westday,6,2));
				break;
			}
		}
	}
	return result;
}
