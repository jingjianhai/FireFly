#pragma once
#include "sys.h"
#include "ClientSock.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <map>
#include "GDIButton.h"

// CSmsBoom �Ի���
class CFireFlyDlg;
class CSmsBoom : public CDialogEx
{
	DECLARE_DYNAMIC(CSmsBoom)

public:
	CSmsBoom(CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~CSmsBoom();

// �Ի�������
	enum { IDD = IDD_SMSBOOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CFireFlyDlg *pDlg;
	//ϵͳ��ť����
	int m_iSystemButtonHovering;
	map<UINT,CGDIButton> m_rcBtn;
	int m_iCommandButtonHovering;//���ܰ�ť������ID Ĭ��-1
	int m_iCommandButtonPushed;  //���ܰ�ť���µ�ID Ĭ��-1
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnCancel();

	CEdit m_PhoneNumber;
	afx_msg void OnBnClickedSend();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	UINT ButtonHitTest(CPoint pt,CRect& rcButton);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnOKBTN();
};
