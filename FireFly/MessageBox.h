#pragma once
#include <map>
#include "GDIButton.h"

// CMessageBox �Ի���

class CMessageBox : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageBox)

public:
	//CMessageBox(CWnd* pParent=NULL);   // ��׼���캯��
	CMessageBox(UINT weight,UINT height,CString str,CString strTitle);   
	virtual ~CMessageBox();

// �Ի�������
	enum { IDD = IDD_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	UINT weight;
	UINT height;
	CString str;
	CString strTitle;
	//ϵͳ��ť����
	int m_iSystemButtonHovering;
	map<UINT,CGDIButton> m_rcBtn;
	int m_iCommandButtonHovering;//���ܰ�ť������ID Ĭ��-1
	int m_iCommandButtonPushed;  //���ܰ�ť���µ�ID Ĭ��-1
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	UINT ButtonHitTest(CPoint pt,CRect& rcButton);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnOKBTN();
};
