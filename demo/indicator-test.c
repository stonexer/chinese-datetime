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

    sprintf(s_time,"%d年%d月%d日 %s",tblock->tm_year + 1900,tblock->tm_mon + 1,tblock->tm_mday,s_wday);
    label_item = gtk_menu_item_new_with_label(s_time);
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);

    label_item = gtk_menu_item_new_with_label("\t马年\t八月初五");
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);

    //分割
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), sep);

    int i,j;

    int y = tblock->tm_year + 1900; //得到当前年份
    int m = tblock->tm_mon + 1;

    int day = 1 - Week(y,m,1); //天数初始值，定位1号的位置
    int days = getDays(y,m);

    label_item = gtk_menu_item_new_with_label("日\t一\t二\t三\t四\t五\t六");
    gtk_menu_shell_append(GTK_MENU_SHELL(indicator_menu), label_item);


    for(i = 1; i <= 6; i++)
    {
        char s_days[20] ="";
        char s_aday[10];
        for(j = 1; j <= 7; j++)
        {
            if(day <= 0 || day > days)
                strcat(s_days,"   ");
            else
            {
                if(day<10)
                {
                    sprintf(s_aday," %d",day);
                    strcat(s_days,s_aday);
                }
                else
                {
                    sprintf(s_aday,"%d",day);
                    strcat(s_days,s_aday);
                }
            }
            j < 7 ? strcat(s_days,"\t") : i < 6 ? strcat(s_days,"\t") : strcat(s_days,"\t");
            day++;
        }
        label_item = gtk_menu_item_new_with_label(s_days);
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
