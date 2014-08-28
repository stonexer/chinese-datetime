#include "mybase.h"

int InitLunarCal(int year);
int PrfCalendar(int pmonth);
int PrfOneDay(char *date,char *type);
int PrintYear();
int PrintMonth();
int Init_Lunar_Year(int year);
int Init_Lunar_Month();
int Init_Lunar_Day();


char *ConvertGL(char *date,char *type);
char *ConvertGL_Info(char *date,char *type);
char *Get_ZB_BaZi(char *datestr);
char *Get_ZB_WuXing(char *bzstr);
char *Get_ZB_NaYin(char *bzstr);