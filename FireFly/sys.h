#pragma once

struct COMMAND
{
	int ID;
	int fID;
	char buffer[2048];
};


struct SYSINFO
{
	WCHAR cmpname[40];
	UINT memsize;
	DWORD os;
};

struct PROCESSINFO
{
	WCHAR pName[32];
	int Pid;
	WCHAR pPath[MAX_PATH];
};



//�����б���Ϣ;
struct SVICELISTINFO{
	wchar_t ServiceName[100]; //������ʵ����
	wchar_t DisplayName[100];//������ʾ����
	wchar_t Description[MAX_PATH];//����������Ϣ
	DWORD stype;//����������ʽ
	DWORD CurrentState; //����״̬
	wchar_t BinPath[MAX_PATH];
};


#define COMSIZE sizeof(COMMAND)

#define MYGETSYSINFO 0x001
#define MYEXITPROCESS 0x002
#define MYGETPROCESS  0x003
#define MYCMDSHELL	  0x004
#define MYSVCMANAGE   0x005

#define PROCESSLIST 1024+100
#define MODULELIST  1024+101
#define EXITPROCESS 1024+102
#define ENDPACKAGE  19880620
#define STARTCMD    1024+103
#define STARTCMDERROR   1024+104
#define WRITECMD   1024+105

#define MYLOGOFF   1024+106
#define MYRESTART  1024+107
#define MYSHUTDOWN 1024+108

#define MYSYSMANAGE 1024+109

#define MYGETSVCLIST   1024+110
#define MYSTARTSVC     1024+111
#define SVCMSG         1024+112 //����ִ�л�����Ϣ