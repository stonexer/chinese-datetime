#include <stdio.h>
//#include <wTypes.h>
//#include <Winsock2.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
//#include <windows.h>
//#include <io.h>
#include <ctype.h>
//#include <Math.h>
#include <time.h>
#include <dirent.h>
//#include <process.h>
//#include <winbase.h>
//#include <wincon.h>
//#include <shellapi.h>
//#include <mmsystem.h>
//#include <shlobj.h>


typedef unsigned long int DWORD;

#define __EXE__ _pgmptr
#define LOGLVL __FILE__,__LINE__
#define GDB __FILE__,__FUNCTION__,__LINE__
#define APP_PROMPT 0x01
#define APP_WINDOWS 0x02
#define APP_CHINESE 0x04

int FORCEDEAL;
int SHOWDEALINFO;



int AddRightKey(char *showname,char *command);
int AppExit(DWORD dwType);
int CheckDate(char *dt1,char *dt2,char *dt3);
int CopyDir(char *path,char *path2,int dirtree);
int CpFile(char *file1,char *file2);
int CpyLogFile(char *logfilename);
int CreateDir(char *path);
int DelAppSelf();
int DelRightKey(char *delname);
int gdb(const char *codefile,const char *func,int linenum);
int GetDirNum(char *str);
int GetMiaoChaFromSys(char *date,char *time);
int GetSysMilli();
int Indexof(char *str,char c);
int IsChinese(char c);
int isdate(char *date);
int isdigitstr(char *str);
int IsDir(struct _finddata_t dirinfo);
int islunardate(char *date);
int istime(char *time);
int LastIndexof(char *str,char c);
int LogFlush();
int RemoveDir(char *dirpath);
int RmFile(char *filename);
int RunNian(int year);
int SetConfig(char *source);
int SetLogButton(int buten);
int strcasecon(char *str1,char *str2);
int strcon(char *str1,char *str2);
int strdiv(char *source,char *res1,char *res2,char c,int num);
int WriteLog(char *zhufile,int lnum,char *fmt,...);


double GetTianCha(char *date1,char *date2,char *time1,char *time2);


char *CalcSecond(char *source,double addsecond,int num);
char *ConvertEnv(char *source);
char *GetChineseSZ(int ncount);
char *GetConfig(char *source);
char *GetDate(char *date,int num);
char *GetExePath();
char *GetFileName(char *str);
char *GetHanZi(int n);
char *GetPublicIP();
char *GetRandStr(int num);
char *GetSysBootTime();
char *GetSysCloseDT();
char *GetSysDate();
char *GetSysDateDot();
char *GetSysDateTime();
char *GetSysDay();
char *GetSysDTM();
char *GetSysDTMili();
char *GetSysDTMinutes();
char *GetSysHours();
char *GetSysMilTime();
char *GetSysMinute();
char *GetSysMonth();
char *GetSysSecond();
char *GetSysTime();
char *GetSysYear();
char *GetWeek(char *datestr,char *wtype);
char *ltrim(char* str);
char *mtrim(char *str);
char *rtrim(char* str);
char *StdFile(char *filename);
char *strcaserep(char *source,char *str1,char *str2);
char *strrep(char *source,char *str1,char *str2);
char *SubString(char *str,int i,int n);
char *trim(char *str);
