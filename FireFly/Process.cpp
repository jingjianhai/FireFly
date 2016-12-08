// Process.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FireFly.h"
#include "Process.h"
#include "afxdialogex.h"
#include "FireFlyDlg.h"

// CProcess �Ի���

IMPLEMENT_DYNAMIC(CProcess, CDialogEx)

CProcess::CProcess(CWnd* pParent,SOCKET sk)
	: CDialogEx(CProcess::IDD, pParent)
{
	CurrentSock=sk;
	pDlg = (CFireFlyDlg*)AfxGetApp()->m_pMainWnd;
}

CProcess::~CProcess()
{
}

void CProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROCESS_LIST, m_ProcessList);
	DDX_Control(pDX, IDC_MODULE_LIST, m_ModuleList);
}


BEGIN_MESSAGE_MAP(CProcess, CDialogEx)
END_MESSAGE_MAP()


// CProcess ��Ϣ�������


BOOL CProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ProcessList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ProcessList.InsertColumn(0,_T("��������"),0,120,-1);
	m_ProcessList.InsertColumn(0,_T("PID"),0,120,-1);
	m_ProcessList.InsertColumn(0,_T("����·��"),0,120,-1);
	m_ModuleList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_ModuleList.InsertColumn(0,_T("ģ������"),0,120,-1);
	m_ModuleList.InsertColumn(0,_T("ģ��·��"),0,120,-1);

	pDlg->m_ClientSock.MySendCommand(CurrentSock,MYGETPROCESS,NULL,0,PROCESSLIST);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CProcess::OnCancel()
{
	CDialogEx::OnCancel();
	pDlg->MyDeleteProcess();

}
