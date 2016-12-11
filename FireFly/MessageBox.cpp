// MessageBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FireFly.h"
#include "MessageBox.h"
#include "afxdialogex.h"
#include "GDIButton.h"

// CMessageBox �Ի���

IMPLEMENT_DYNAMIC(CMessageBox, CDialogEx)

//CMessageBox::CMessageBox(CWnd* pParent /*=NULL*/)
//	: CDialogEx(CMessageBox::IDD, pParent)
//{
//
//}

CMessageBox::CMessageBox(UINT weight,UINT height,CString str,CString strTitle)
	: CDialogEx(CMessageBox::IDD)
{
	this->weight=weight;
	this->height=height;
	this->str=str;
	this->strTitle=strTitle;
	m_iSystemButtonHovering=-1;
	m_iCommandButtonHovering=-1;
	m_iCommandButtonPushed=-1;
}

CMessageBox::~CMessageBox()
{
}

void CMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageBox, CDialogEx)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_OK_BT,&CMessageBox::OnOKBTN)
END_MESSAGE_MAP()


// CMessageBox ��Ϣ�������


int CMessageBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	CWnd::SetWindowPos(NULL,0,0,weight,height,SWP_NOZORDER|SWP_NOMOVE);
	CenterWindow(GetParent());

	// �رհ�ťͼƬ188*22
	//�رհ�ť
	//�رհ�ť��λ��
	CRect rtButton;
	CGDIButton dButton;
	rtButton.left=weight-47;
	rtButton.top=0;
	rtButton.right=weight;
	rtButton.bottom=22;

	//����MAP�� ���ÿ������캯�������ɶ��󸱱��������������������ʱ���󣬲�Ӱ��map�еĶ���
	dButton.CreateButton(_T("�ر�"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_CLOSE),4,IDC_CLOSE_BT);
	m_rcBtn[IDC_CLOSE_BT]=dButton;

	rtButton.left=weight/2-30;
	rtButton.top=height-50;
	rtButton.right=weight/2+30;
	rtButton.bottom=height-20;

	//����MAP�� ���ÿ������캯�������ɶ��󸱱��������������������ʱ���󣬲�Ӱ��map�еĶ���
	dButton.CreateButton(_T("ȷ��"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_MESSAGEBOXBUTTON),1,IDC_OK_BT);
	m_rcBtn[IDC_OK_BT]=dButton;
	return 0;
}


void CMessageBox::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rtButton;
	//CRect rtWindow;
	//GetClientRect(&rtWindow);

	//��������λ���ڲ��ڰ�ť��Χ��
	int iButton = ButtonHitTest(point, rtButton);

	//������Ի淶Χ�� �����ָ����Ϊ��ָ
	if(iButton!=-1)
	{
		::SetCursor(::LoadCursor(NULL,IDC_HAND));
	}
	//iButton  �������ͣ��λ�õĿؼ�ID
	//m_iButtonHovering ԭ�����ͣ��λ�õĿؼ�ID
	//�������Ϊ���ж� ���λ����û���뿪�����½���
	//�������ڿؼ������ƶ�������ĺ��������ߵģ�
	//��ǰ��ͣ���ؼ�ID==֮ǰ��ͣ���ؼ�ID ���ǲ���Ҫ�ػ��
	//�������֤���ǴӲ��ǿؼ���������룬��ӿؼ����뿪�����һ���ؼ�����һ���ؼ��ϡ�

	//m_iButtonHoveringĬ��ֵ-1֤���ڿؼ����档

	//���iButton != m_iButtonHovering ��ǰ��귶Χ �������ϴεķ�Χ��֤���ӿؼ��뿪��
	//m_iButtonHovering != -1��һ���ռ䲻�ǿհף�������һ���ؼ��ƶ�����һ���ռ䣬�ϵĿռ���Ҫ�ػ�
	//iButton != -1 ��ǰû���ƶ����հף������µĿؼ���Ҫ�ػ�
	if(iButton != m_iSystemButtonHovering)//֤��״̬�����仯
	{
		//������Ҫ�����������
		//��������һ����ť���뿪 �����A�ƶ���B  A��Ҫ�ظ�ԭ��״̬��Ҫ�ػ棬 B��Ϊ���ڵļ���״̬��Ҫ�ػ�
		if(m_iSystemButtonHovering != -1) //
		{
			m_rcBtn[m_iSystemButtonHovering].MouseLeave();
			m_iSystemButtonHovering = -1;
		}
		//����һ����ť�Ľ���
		if(iButton != -1)
		{
			m_iSystemButtonHovering = iButton;
			m_rcBtn[m_iSystemButtonHovering].MouseHover();
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMessageBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rcButton;
	int iButton=this->ButtonHitTest(point,rcButton);

	//���𣬰�-1��ֵ ֤��û�а���
	if(iButton!=-1)
	{
		m_iCommandButtonPushed=-1;
		this->m_rcBtn[iButton].LButtonUp();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMessageBox::OnLButtonDown(UINT nFlags, CPoint point)
{
//	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CRect rcButton;
	int iButton=this->ButtonHitTest(point,rcButton);

	if(iButton!=-1)
	{
		m_iCommandButtonPushed=iButton;
		this->m_rcBtn[iButton].LButtonDown();
		return;
	}

	//һ��Ҫ������� ���߾�ȷ�������϶���������ʶ�������Ӱ���Ժ���ж���
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMessageBox::OnPaint()
{
	CClientDC dc(this);
	CMemoryDC mDC(&dc);

	CRect rcClient;
	GetClientRect(&rcClient);

	// ��ȡ�ػ����λ��
	CRect rcPaint;
	mDC.GetClipBox(&rcPaint);
	Gdiplus::Graphics graphics(mDC.m_hDC);

	StringFormat stringFormat;
	LOGFONT lfFont;
	memset(&lfFont, 0, sizeof(lfFont));
	lfFont.lfHeight = -13;
	lfFont.lfWeight = 300;
	lstrcpy(lfFont.lfFaceName, _T("΢���ź�"));
	Gdiplus::Font font(mDC.GetSafeHdc(),&lfFont);

	//���е�ͼƬ����������CMemoryImage��
	//���Ʊ���
	graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_MESSAGEBOXDLG),0, 0, rcClient.Width(), rcClient.Height());

	// ���Ʊ�����
	RectF TitleRect;
	SolidBrush brush((ARGB)Color::Black);
	TitleRect.X=5, TitleRect.Y=3; TitleRect.Width = 200; TitleRect.Height = 17;
	graphics.DrawString(strTitle.GetBuffer(), strTitle.GetLength(),&font, TitleRect,&stringFormat, &brush);


	//���ƹرհ�ť
	map<UINT,CGDIButton>::iterator it;
	for(it=m_rcBtn.begin();it!=m_rcBtn.end();it++)
	{
		CGDIButton& dButton = it->second;
		CRect rcControl;
		// ��ǰ��ť�Ǵ��ڹرհ�ť
		dButton.GetRect(&rcControl);

		// �жϵ�ǰ��ť�Ƿ���Ҫ�ػ�
		if(!rcPaint.IsRectEmpty() && !CRect().IntersectRect(&rcControl, rcPaint))
		{
			continue;
		}
		dButton.DrawButton(graphics);
	}

	//���� ȷ�� ����
	CString Correct=L"ȷ��";
	TitleRect.X=(REAL)weight/2-30+15, TitleRect.Y=(REAL)height-45; TitleRect.Width = (REAL)60; TitleRect.Height = (REAL)30;
	graphics.DrawString(Correct.GetBuffer(), Correct.GetLength(),&font, TitleRect,&stringFormat, &brush);

	//���� �Ի�������
	TitleRect.X=(REAL)5, TitleRect.Y=(REAL)height/2; TitleRect.Width = (REAL)weight; TitleRect.Height = (REAL)height/4;
	graphics.DrawString(str.GetBuffer(), str.GetLength(),&font, TitleRect,&stringFormat, &brush);

}

UINT CMessageBox::ButtonHitTest(CPoint pt,CRect& rcButton)
{
	map<UINT,CGDIButton>::iterator it; //������ ����map
	for(it=m_rcBtn.begin();it!=m_rcBtn.end();it++)
	{
		CGDIButton& dButton=it->second; //ȡ����ť����
		if(dButton.PtInButton(pt))      //���λ���ڲ��ڰ�ť��Χ��
		{
			dButton.GetRect(&rcButton);//��õ�ǰ��ť��Χ
			return it->first;          //���ص�ǰID first�ǰ�ťID,second �ǰ�ť����
		}
	}
	return -1;
}

BOOL CMessageBox::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}


BOOL CMessageBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case IDC_CLOSE_BT:
		{
			SendMessage( WM_SYSCOMMAND,SC_CLOSE);
		}
		break;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

void CMessageBox::OnOKBTN()
{
	SendMessage( WM_SYSCOMMAND,SC_CLOSE);
}
