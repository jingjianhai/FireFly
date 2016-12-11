#pragma once
//#include "resource.h"
#include "sys.h"
//#include "ClientSock.h"
//#include "afxwin.h"
// CCmd �Ի���
class CFireFlyDlg;

class CCmd : public CDialogEx
{
	DECLARE_DYNAMIC(CCmd)

public:
	CCmd(CWnd* pParent,SOCKET sk);   // ��׼���캯��
	virtual ~CCmd();
	virtual void OnCancel();
// �Ի�������
	enum { IDD = IDD_CMDSHELL };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	SOCKET CurrentSock;
	CFireFlyDlg *pDlg;
public:
	virtual BOOL OnInitDialog();
	void CmdCommand(COMMAND cmd);
	CEdit m_CmdShow;
	void MyShowText(COMMAND cmd);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
