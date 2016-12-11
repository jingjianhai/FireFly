
// FireFlyDlg.h : ͷ�ļ�
//

#pragma once
#include <map>
#include "GDIButton.h"
#include "CustomFuntion.h"
#include "ClientSock.h"

#include "Process.h"
using namespace std;

#define WM_ONLINE (WM_USER+100)   //����
#define WM_OFFLINE (WM_USER+101)  //����

// CFireFlyDlg �Ի���
class CFireFlyDlg : public CDialogEx
{
// ����
public:
	CFireFlyDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CFireFlyDlg();	
// �Ի�������
	enum { IDD = IDD_FIREFLY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void LoadPng(UINT ID,CString path);
private:
	ULONG_PTR	m_GdiplusToken; //GDI+ token
	//����ͼƬ����
	map<UINT,Image*> m_Image;
	//ϵͳ��ť����
	map<UINT,CGDIButton> m_rcBtn;
	//�ж�MouseMove
	BOOL m_bTracking;
	int m_iSystemButtonHovering;//ԭ�����ͣ��λ�õĿؼ�ID ���ڿؼ�����Ϊ-1
	int m_iCommandButtonHovering;//���ܰ�ť������ID Ĭ��-1
	int m_iCommandButtonPushed;  //���ܰ�ť���µ�ID Ĭ��-1
	int m_iListHover; //��꾭����Listview��Ŀ����
	int m_iListPress;//��갴�µ�Listview��Ŀ����
	CCustomFuntion m_custom;
	CRect m_rcTime;
	BOOL m_bUpdataListView;//�Ƿ������������ߣ���Ҫ�ػ�

public:
	CClientSock m_ClientSock;//socket������
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	UINT ButtonHitTest(CPoint pt,CRect& rcButton);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	LRESULT MyOnline(WPARAM wParam,LPARAM lParam); //����
	LRESULT MyOffline(WPARAM wParam,LPARAM lParam);//����

	afx_msg void OnProcess();//���̹���
	void MyDeleteProcess();
public:
	CProcess* m_Process;    //���̹������
};
