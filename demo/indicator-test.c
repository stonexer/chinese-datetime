#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <glibtop.h>
#include <pango/pango.h>
#include <gio/gio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

AppIndicator *indicator;
GtkWidget *indicator_menu;

GtkWidget *quit_item;
GtkWidget *label_item;
GtkWidget *sep;


gboolean update()
{
    gchar *label_guide = "11:22:00";   //maximum length label text, doesn't really work atm
    gchar label_text[10];

    time_t timer;
    struct tm *tblock;
    timer = time(NULL);
    tblock = localtime(&timer);

    sprintf(label_text,"%02d:%02d:%02d",tblock->tm_hour,tblock->tm_min,tblock->tm_sec);

    app_indicator_set_label(indicator, label_text , label_guide);
    return TRUE;
}

int open = 0;

static void
scroll_event_cb (AppIndicator * ci, gint delta, guint direction, gpointer data)
{
    g_print("Got scroll event! delta: %d, direction: %d\n", delta, direction);
    if(open == 0 && direction == 1)
    {
        system("./chinese-calendar&");
        open = 1;
    }
    if(open == 1 && direction == 0)
    {
        system("echo bye");
        system("  ps aux | grep \"chinese-calendar\" | cut -c 9-15 | xargs kill -9  ");
        open = 0;
    }
}

/*
*判断是否闰年    y=年份值
*/
int isRunNian(int y)
{
    return ( (y % 4 == 0 && y % 100 != 0) || y % 400 == 0) ? 1 : 0;
}

/*
*计算某个月的天数
*参数:   y 整型,接收年份值; m 整型,接收月份值;
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
        days = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    case 2:
        days = isRunNian(y) ? 29 : 28;
        break;
    default:
        ;
    }
    return days;
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


int lunar(int year, int mon, int day,char szNongli[100],char szNongliDay[20],char szaday[10])
{
    char szShuXiang[10];

    /*天干名称*/
    const char *cTianGan[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
    /*地支名称*/
    const char *cDiZhi[] = {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};
    /*属相名称*/
    const char *cShuXiang[] = {"鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"};
    /*农历日期名*/
    const char *cDayName[] = {"*","初一","初二","初三","初四","初五",
                              "初六","初七","初八","初九","初十","十一","十二","十三","十四","十五","十六","十七","十八","十九","二十","廿一","廿二","廿三","廿四","廿五","廿六","廿七","廿八","廿九","三十"
                             };
    /*农历月份名*/
    const char *cMonName[] = {"*","正","二","三","四","五","六","七","八","九","十","十一","腊"};

    /*公历每月前面的天数*/
    const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
    /*农历数据*/
    const int wNongliData[100] = {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
                                  ,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
                                  ,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
                                  ,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
                                  ,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
                                  ,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
                                  ,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
                                  ,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
                                  ,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
                                  ,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877
                                 };
    static int wCurYear,wCurMonth,wCurDay;
    static int nTheDate,nIsEnd,m,k,n,i,nBit;
    /*---取当前公历年、月、日---*/
    wCurYear = year + 1900;
    wCurMonth = mon + 1;
    wCurDay = day;
    /*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/
    nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
    if((!(wCurYear % 4)) && (wCurMonth > 2))
        nTheDate = nTheDate + 1;



    /*--计算农历天干、地支、月、日---*/
    nIsEnd = 0;
    m = 0;
    while(nIsEnd != 1)
    {
        if(wNongliData[m] < 4095)
            k = 11;
        else
            k = 12;
        n = k;
        while(n>=0)
        {
            //获取wNongliData(m)的第n个二进制位的值
            nBit = wNongliData[m];
            for(i=1; i<n+1; i++)
                nBit = nBit/2;

            nBit = nBit % 2;

            if (nTheDate <= (29 + nBit))
            {
                nIsEnd = 1;
                break;
            }

            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }
        if(nIsEnd)
            break;
        m = m + 1;
    }
    wCurYear = 1921 + m;
    wCurMonth = k - n + 1;
    wCurDay = nTheDate;
    if (k == 12)
    {
        if (wCurMonth == wNongliData[m] / 65536 + 1)
            wCurMonth = 1 - wCurMonth;
        else if (wCurMonth > wNongliData[m] / 65536 + 1)
            wCurMonth = wCurMonth - 1;
    }



    /*--生成农历天干、地支、属相 ==> wNongli--*/
    sprintf( szShuXiang,"%s",cShuXiang[((wCurYear - 4) % 60) % 12] );

    sprintf(szNongli,"%s(%s%s)年",szShuXiang,cTianGan[((wCurYear - 4) % 60) % 10],cDiZhi[((wCurYear - 4) % 60) % 12]);

    /*--生成农历月、日 ==> wNongliDay--*/
    if (wCurMonth < 1)
        sprintf(szNongliDay,"闰%s",cMonName[-1 * wCurMonth]);
    else
        strcpy(szNongliDay,cMonName[wCurMonth]);

    strcat(szNongliDay,"月");
    strcat(szNongliDay,cDayName[wCurDay]);

    sprintf(szaday,"%s",cDayName[wCurDay]);

    return 0;
}


int main (int argc, char **argv)
{
    GtkWidget *calendar;
    GtkWidget *s;

    gtk_init (&argc, &argv);
    indicator_menu = gtk_menu_new();

    s = gtk_menu_item_new();

    calendar=gtk_calendar_new();
    gtk_container_add(GTK_CONTAINER(s),calendar);
    gtk_widget_show(calendar);

    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), s);

    char s_time[50];
    char* s_wday="星期日";

    time_t timer;
    struct tm *tblock;
    timer = time(NULL);
    tblock = localtime(&timer);

    int i,j,m;

    //判断星期
    switch(tblock->tm_wday)
    {
    case 0:
        s_wday = "星期日";
        break;
    case 1:
        s_wday = "星期一";
        break;
    case 2:
        s_wday = "星期二";
        break;
    case 3:
        s_wday = "星期三";
        break;
    case 4:
        s_wday = "星期四";
        break;
    case 5:
        s_wday = "星期五";
        break;
    case 6:
        s_wday = "星期六";
        break;
    }

    sprintf(s_time,"%d年%d月%d日    %s",tblock->tm_year + 1900,tblock->tm_mon + 1,tblock->tm_mday,s_wday);
    label_item = gtk_menu_item_new_with_label(s_time);
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);


    char Nongli[100];
    char NongliDay[20];
    char aday[10];

    lunar(tblock->tm_year,tblock->tm_mon,tblock->tm_mday,Nongli,NongliDay,aday);

    char s_nongli[100];
    sprintf(s_nongli,"%s\t%s",Nongli,NongliDay);

    label_item = gtk_menu_item_new_with_label(s_nongli);
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);

    //分割
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), sep);

    char s_ym[100];
    sprintf(s_ym,"%d年                       %d月",tblock->tm_year + 1900,tblock->tm_mon + 1);

    label_item = gtk_menu_item_new_with_label(s_ym);
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);

    int y = tblock->tm_year + 1900; //得到当前年份
    m = tblock->tm_mon + 1;

    int day = 1 - Week(y,m,1); //天数初始值，定位1号的位置
    int days = getDays(y,m);

    label_item = gtk_menu_item_new_with_label("   日      一      二      三      四      五      六");
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);

    int j2;

    for(i = 1; i <= 6; i++)
    {
        char s_days[20] ="  ";
        char s_aday[10];
        for(j = 1; j <= 7; j++)
        {
            if(day <= 0 || day > days)
                strcat(s_days,"     ");
            else
            {
                if(day<10)
                {
                    sprintf(s_aday,"  %d",day);
                    strcat(s_days,s_aday);
                }
                else
                {
                    sprintf(s_aday,"%d",day);
                    strcat(s_days,s_aday);
                }
            }
            j < 7 ? strcat(s_days,"      ") : i < 6 ? strcat(s_days,"      ") : strcat(s_days,"      ");
            day++;
        }
        label_item = gtk_menu_item_new_with_label(s_days);
        gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);

        day = day - 7;

        char s2_days[100] ="";
        char s2_aday[20];

        for(j2 = 1; j2 <= 7; j2++)
        {
            if(day <= 0 || day > days)
                strcat(s2_days,"         ");
            else
            {
                    lunar(tblock->tm_year,tblock->tm_mon,day,Nongli,NongliDay,aday);
                    sprintf(s2_aday," %s",aday);
                    strcat(s2_days,s2_aday);
            }
            j < 7 ? strcat(s2_days,"") : i < 6 ? strcat(s2_days,"") : strcat(s2_days,"");
            day++;
        }
        label_item = gtk_menu_item_new_with_label(s2_days);
        gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);
    }


    //quit item
    //quit_item = gtk_menu_item_new_with_label("退出");
    //gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), quit_item);
    //g_signal_connect(quit_item, "activate", G_CALLBACK (gtk_main_quit), NULL);

    gtk_widget_show_all(indicator_menu);

    //create app indicator
    indicator = app_indicator_new ("time", "s-idle", APP_INDICATOR_CATEGORY_SYSTEM_SERVICES);
    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_label(indicator, "time", "time");
    app_indicator_set_menu(indicator, GTK_MENU (indicator_menu));

    g_signal_connect(indicator,"scroll_event" , G_CALLBACK (scroll_event_cb), NULL);

    //set indicator position. default: all the way left
    app_indicator_set_ordering_index(indicator, 1);

    update();

    /* update period in milliseconds */
    g_timeout_add(1000, update, NULL);

    gtk_main();

    return 0;
}
