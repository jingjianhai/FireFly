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