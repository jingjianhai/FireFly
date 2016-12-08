#pragma once
#include "afxcmn.h"


// CProcess �Ի���

class CFireFlyDlg;

class CProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CProcess)

public:
	CProcess(CWnd* pParent,SOCKET sk);   // ��׼���캯��
	virtual ~CProcess();

// �Ի�������
	enum { IDD = IDD_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	SOCKET CurrentSock;
	CFireFlyDlg *pDlg;
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ProcessList;
	CListCtrl m_ModuleList;
	virtual void OnCancel();
};
