#include "StdAfx.h"
#include "CustomFuntion.h"


CCustomFuntion::CCustomFuntion(void)
{
}


CCustomFuntion::~CCustomFuntion(void)
{
}


//����ʱ��
int CCustomFuntion::MyGetTime(CString& CurrentTime)
{
	CTime t=CTime::GetCurrentTime();
	CurrentTime.Format(L"%4.4d��%2.2d��%2.2d��%2.2d:%2.2d:%2.2d",t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
	return 0;
}

//��ȡ����ϵͳ�汾
CString CCustomFuntion::MyGetOS(int id)
{

	switch (id)
	{
	case 2:
		return _T("Windows XP");
		break;
	case 3:
		return _T("Windows Server 2003");//Windows Server 2003
		break;
	case 4:
		return _T("Windows Vista");//	Windows Vista	
		break;
	case 5:
		return _T("Windows 7");//Windows Server 2008/Windows 7
		break;
	default:
		return _T("δ֪�汾");
		break;
	}
}

CString CCustomFuntion::MyCharToWide(char * ch)
{
	wchar_t temp[1024]={0};
	MultiByteToWideChar(CP_ACP,0,ch,1024,temp,1024);
	return temp;
}


char * CCustomFuntion::MyWideToChar(CString st)
{
	char temp[1204]={0};
	WideCharToMultiByte(CP_ACP,0,st,1024,temp,1024,NULL,NULL);
	return temp;
}