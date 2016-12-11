#pragma once

#include "sys.h"
#include "ClientSock.h"
#include "afxcmn.h"
// CSERVICE �Ի���
class CFireFlyDlg;
class CService : public CDialogEx
{
	DECLARE_DYNAMIC(CService)

public:
	CService(CWnd* pParent,SOCKET sk);   // ��׼���캯��
	virtual ~CService();

// �Ի�������
	enum { IDD = IDD_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
private:
private:
	SOCKET CurrentSock;
	CFireFlyDlg *pDlg;
public:
	void MySVCCommand(COMMAND cmd);
	void ShowSVCList(COMMAND cmd);
	CString MyGetCurrentState(DWORD State);
	CString MyGetStartType(DWORD StartType);
	afx_msg void OnStartsvc();
	afx_msg void OnNMRClickSvcmanage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSvcRe();
	CListCtrl m_ServiceList;
	afx_msg void OnNMRClickServicelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRefreshservice();
	afx_msg void OnStartservice();
};
