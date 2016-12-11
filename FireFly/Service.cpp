// SvcManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FireFly.h"
#include "Service.h"
#include "afxdialogex.h"
#include "FireFlyDlg.h"

#include <WinSvc.h>
// CService �Ի���

IMPLEMENT_DYNAMIC(CService, CDialogEx)

CService::CService(CWnd* pParent,SOCKET sk)
	: CDialogEx(CService::IDD, pParent)
{
	CurrentSock=sk;
	pDlg = (CFireFlyDlg*)AfxGetApp()->m_pMainWnd;
}

CService::~CService()
{
}

void CService::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVICELIST, m_ServiceList);
}


BEGIN_MESSAGE_MAP(CService, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_SERVICELIST, &CService::OnNMRClickServicelist)
	ON_COMMAND(ID_REFRESHSERVICE, &CService::OnRefreshservice)
	ON_COMMAND(ID_STARTSERVICE, &CService::OnStartservice)
END_MESSAGE_MAP()


// CService ��Ϣ�������


void CService::OnCancel()
{
	CDialogEx::OnCancel();
	pDlg->MyDeleteService();
}


BOOL CService::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ServiceList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	//�ֳ��ĸ���Ŀ
	m_ServiceList.InsertColumn(0,L"����",0,120,-1);
	m_ServiceList.InsertColumn(1,L"��ʾ",0,120,-1);
	m_ServiceList.InsertColumn(2,L"״̬",0,120,-1);
	m_ServiceList.InsertColumn(3,L"����",0,120,-1);
	m_ServiceList.InsertColumn(4,L"����",0,120,-1);
	m_ServiceList.InsertColumn(5,L"·��",0,120,-1);
	pDlg->m_ClientSock.MySendCommand(CurrentSock,MYSVCMANAGE,NULL,0,MYGETSVCLIST);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CService::MySVCCommand(COMMAND cmd)
{
	WCHAR temp[MAX_PATH]={0};
	switch(cmd.fID)
	{
	case MYGETSVCLIST:
		ShowSVCList(cmd);
		break;
	case SVCMSG:		
		memcpy(temp,cmd.buffer,MAX_PATH);
		AfxMessageBox(temp);
		break;
	default:
		break;
	}
}


void CService::ShowSVCList(COMMAND cmd)
{
	SVICELISTINFO svcin;
	ZeroMemory(&svcin,sizeof(SVICELISTINFO));
	memcpy(&svcin,cmd.buffer,sizeof(SVICELISTINFO));
	int idx = m_ServiceList.GetItemCount();
	m_ServiceList.InsertItem(idx,svcin.ServiceName); //����
	m_ServiceList.SetItemText(idx,1,svcin.DisplayName);//��ʾ
	m_ServiceList.SetItemText(idx,2,MyGetCurrentState(svcin.CurrentState));//״̬
	m_ServiceList.SetItemText(idx,3,MyGetStartType(svcin.stype));//����
	m_ServiceList.SetItemText(idx,4,svcin.Description);//����
	m_ServiceList.SetItemText(idx,5,svcin.BinPath);//·��
}

CString CService::MyGetCurrentState(DWORD State)
{
	CString sst;
	switch (State)
	{
	case SERVICE_RUNNING:
		sst = _T("������");
		break;
	case SERVICE_PAUSED:
		sst = _T("��ͣ");
		break;
	case SERVICE_PAUSE_PENDING:
		sst = _T("������ͣ��...");
		break;
	case SERVICE_START_PENDING:
		sst = _T("����������..");
		break;
	case SERVICE_STOPPED:
		sst = _T("");
		break;
	case SERVICE_STOP_PENDING:
		sst = _T("����ֹͣ��..");
		break;
	default:
		sst = _T("");
		break;
	}
	return sst;
}
CString CService::MyGetStartType(DWORD StartType)
{
	CString sttr;
	switch(StartType)
	{
	case SERVICE_AUTO_START:
		sttr = _T("�Զ�");
		break;
	case SERVICE_DEMAND_START:
		sttr = _T("�ֶ�");
		break;
	case SERVICE_DISABLED:
		sttr = _T("�ѽ���");
		break;
	default:
		sttr = _T("");
		break;
	}
	return sttr;
}

void CService::OnNMRClickServicelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int idx=pNMItemActivate->iItem;
	if(idx<0)
	{
		return;
	}
	CMenu menu,*pMenu=NULL;
	menu.LoadMenuW(IDR_SERVICE);
	pMenu=menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);

	*pResult = 0;
	*pResult = 0;
}


void CService::OnRefreshservice()
{
	this->m_ServiceList.DeleteAllItems();
	pDlg->m_ClientSock.MySendCommand(CurrentSock,MYSVCMANAGE,NULL,0,MYGETSVCLIST);
}


void CService::OnStartservice()
{
	int idx = m_ServiceList.GetSelectionMark();
	wchar_t svcname[MAX_PATH];
	m_ServiceList.GetItemText(idx,0,svcname,MAX_PATH);
	pDlg->m_ClientSock.MySendCommand(CurrentSock,MYSVCMANAGE,(char*)svcname,MAX_PATH,MYSTARTSVC);
}
