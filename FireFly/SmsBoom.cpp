// SmsBoom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FireFly.h"
#include "SmsBoom.h"
#include "afxdialogex.h"
#include "FireFlyDlg.h"
#include "GDIButton.h"
#include "MessageBox.h"
#include "SendSms.h"
// CSmsBoom �Ի���

IMPLEMENT_DYNAMIC(CSmsBoom, CDialogEx)

CSmsBoom::CSmsBoom(CWnd* pParent)
	: CDialogEx(CSmsBoom::IDD, pParent)
{
	//	pDlg= (CFireFlyDlg*)AfxGetMainWnd();���ͬ������
	pDlg = (CFireFlyDlg*)AfxGetApp()->m_pMainWnd;
	m_iSystemButtonHovering=-1;
	m_iCommandButtonHovering=-1;
	m_iCommandButtonPushed=-1;

}

CSmsBoom::~CSmsBoom()
{
}

void CSmsBoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PhoneNumber, m_PhoneNumber);
}


BEGIN_MESSAGE_MAP(CSmsBoom, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_SEND, &CSmsBoom::OnBnClickedSend)
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_OK_BT,&CSmsBoom::OnOKBTN)
END_MESSAGE_MAP()



//void CSmsBoom::OnPaint()
//{
//	CClientDC dc(this);
//	CMemoryDC mDC(&dc);
//
//	CRect rcClient;
//	GetClientRect(&rcClient);
//
//	// ��ȡ�ػ����λ��
//	CRect rcPaint;
//	mDC.GetClipBox(&rcPaint);
//	Gdiplus::Graphics graphics(mDC.m_hDC);
//
//	StringFormat stringFormat;
//	LOGFONT lfFont;
//	memset(&lfFont, 0, sizeof(lfFont));
//	lfFont.lfHeight = -13;
//	lfFont.lfWeight = 300;
//	lstrcpy(lfFont.lfFaceName, _T("΢���ź�"));
//	Gdiplus::Font font(mDC.GetSafeHdc(),&lfFont);
//
//	// ���Ʊ�����
//	RectF TitleRect;
//	CString strTitle=L"�������ڷǷ���;";
//	SolidBrush brush((ARGB)Color::Black);
//	TitleRect.X=5, TitleRect.Y=3; TitleRect.Width = 200; TitleRect.Height = 17;
//	graphics.DrawString(strTitle.GetBuffer(), strTitle.GetLength(),&font, TitleRect,&stringFormat, &brush);
//
//
//	//���ƹرհ�ť
//	map<UINT,CGDIButton>::iterator it;
//	for(it=m_rcBtn.begin();it!=m_rcBtn.end();it++)
//	{
//		CGDIButton& dButton = it->second;
//		CRect rcControl;
//		// ��ǰ��ť�Ǵ��ڹرհ�ť
//		dButton.GetRect(&rcControl);
//
//		// �жϵ�ǰ��ť�Ƿ���Ҫ�ػ�
//		if(!rcPaint.IsRectEmpty() && !CRect().IntersectRect(&rcControl, rcPaint))
//		{
//			continue;
//		}
//		dButton.DrawButton(graphics);
//	}
//
//	//���� ȷ�� ����
//	CString Correct=L"ȷ��";
//	TitleRect.X=(REAL)rcClient.Width()/2-30+15, TitleRect.Y=(REAL)rcClient.Height()-45; TitleRect.Width = (REAL)60; TitleRect.Height = (REAL)30;
//	graphics.DrawString(Correct.GetBuffer(), Correct.GetLength(),&font, TitleRect,&stringFormat, &brush);
//
//	//���� �Ի�������
//	TitleRect.X=(REAL)5, TitleRect.Y=(REAL)rcClient.Height()/2; TitleRect.Width = (REAL)rcClient.Width(); TitleRect.Height = (REAL)rcClient.Height()/4;
//	graphics.DrawString(strTitle.GetBuffer(), strTitle.GetLength(),&font, TitleRect,&stringFormat, &brush);
//
//}


void CSmsBoom::OnMouseMove(UINT nFlags, CPoint point)
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


void CSmsBoom::OnLButtonUp(UINT nFlags, CPoint point)
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


void CSmsBoom::OnLButtonDown(UINT nFlags, CPoint point)
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

UINT CSmsBoom::ButtonHitTest(CPoint pt,CRect& rcButton)
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
void CSmsBoom::OnCancel()
{
	CDialogEx::OnCancel();
	pDlg->MyDeleteSmsBoom();
}


int CSmsBoom::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CenterWindow(GetParent());
	CRect rcClient;
	GetClientRect(&rcClient);
	// �رհ�ťͼƬ188*22
	//�رհ�ť
	//�رհ�ť��λ��
	CRect rtButton;
	CGDIButton dButton;
	rtButton.left=rcClient.Width()-47;
	rtButton.top=0;
	rtButton.right=rcClient.Width();
	rtButton.bottom=22;

	//����MAP�� ���ÿ������캯�������ɶ��󸱱��������������������ʱ���󣬲�Ӱ��map�еĶ���
	dButton.CreateButton(_T("�ر�"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_CLOSE),4,IDC_CLOSE_BT);
	m_rcBtn[IDC_CLOSE_BT]=dButton;

	rtButton.left=rcClient.Width()/2-30;
	rtButton.top=rcClient.Height()-50;
	rtButton.right=rcClient.Width()/2+30;
	rtButton.bottom=rcClient.Height()-20;

	//����MAP�� ���ÿ������캯�������ɶ��󸱱��������������������ʱ���󣬲�Ӱ��map�еĶ���
	dButton.CreateButton(_T("ȷ��"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_MESSAGEBOXBUTTON),1,IDC_OK_BT);
	m_rcBtn[IDC_OK_BT]=dButton;
	return 0;
}


void CSmsBoom::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



BOOL CSmsBoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->m_PhoneNumber.SetLimitText(11);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CSmsBoom::OnEraseBkgnd(CDC* pDC)
{
		CClientDC dc(this);
		CMemoryDC mDC(&dc);
	
		CRect rcClient;
		GetClientRect(&rcClient);
	
		// ��ȡ�ػ����λ��
		CRect rcPaint;
		mDC.GetClipBox(&rcPaint);
		Gdiplus::Graphics graphics(mDC.m_hDC);
	//	graphics.
		StringFormat stringFormat;
		LOGFONT lfFont;
		memset(&lfFont, 0, sizeof(lfFont));
		lfFont.lfHeight = -13;
		lfFont.lfWeight = 300;
		lstrcpy(lfFont.lfFaceName, _T("΢���ź�"));
		Gdiplus::Font font(mDC.GetSafeHdc(),&lfFont);
	 
		//���е�ͼƬ����������CMemoryImage��
		//���Ʊ���
		graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_BOOMBKG),0, 0, rcClient.Width(), rcClient.Height());


		// ���Ʊ�����
		RectF TitleRect;
		CString strTitle=L"�������ڷǷ���;";
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
		CString Correct=L"����";
		TitleRect.X=(REAL)rcClient.Width()/2-30+15, TitleRect.Y=(REAL)rcClient.Height()-45; TitleRect.Width = (REAL)60; TitleRect.Height = (REAL)30;
		graphics.DrawString(Correct.GetBuffer(), Correct.GetLength(),&font, TitleRect,&stringFormat, &brush);

		//���� �Ի�������
		strTitle=L"�������ֻ��ţ�";
		TitleRect.X=(REAL)100, TitleRect.Y=(REAL)30; TitleRect.Width = (REAL)rcClient.Width(); TitleRect.Height = (REAL)rcClient.Height()/4;
		graphics.DrawString(strTitle.GetBuffer(), strTitle.GetLength(),&font, TitleRect,&stringFormat, &brush);

	return TRUE;
}


BOOL CSmsBoom::OnCommand(WPARAM wParam, LPARAM lParam)
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

void CSmsBoom::OnOKBTN()
{
	if(m_PhoneNumber.GetWindowTextLengthW()<11)
	{
		CString text=L"������Ϸ����ֻ�����";
		CMessageBox mb(300,200,text,text);
		mb.DoModal();
		return;
	}
	CSendSms ss;
	CString sNum;
	m_PhoneNumber.GetWindowTextW(sNum);
	UINT SendCount=ss.Send(sNum);

	CString sNumOfSms=L"�ɹ����������� "+SendCount;

	CMessageBox mb(300,200,L"���ź�ը",sNumOfSms);
	mb.DoModal();
}
