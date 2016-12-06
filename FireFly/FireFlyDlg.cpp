
// FireFlyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FireFly.h"
#include "FireFlyDlg.h"
#include "afxdialogex.h"
#include "GDIButton.h"

#define IDC_BASE      10000
#define IDC_BKG       IDC_BASE+1
#define IDC_CLOSE_BT  IDC_BASE+2
#define IDC_MIN_BT	  IDC_BASE+3
#define IDC_SET_BT	  IDC_BASE+4
#define IDC_MAINPAGE_BT	  IDC_BASE+5  //��ҳ
#define IDC_PROC_MANAGE_BT  IDC_BASE+6 //���̹���
#define IDC_REMOTECMD_BT	IDC_BASE+7 //Զ��CMD

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFireFlyDlg �Ի���


CFireFlyDlg::~CFireFlyDlg()
{
	CMemoryImage::UnLoad();
}

CFireFlyDlg::CFireFlyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFireFlyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICO);

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_GdiplusToken,&gdiplusStartupInput,NULL);

	Image* pImage=NULL;
	m_bTracking=FALSE;
	m_iSystemButtonHovering=-1;
	m_iCommandButtonHovering=-1;
	m_iCommandButtonPushed=-1;
	m_iListHover=-1;
	m_iListPress=-1;
	m_rcTime.left=270,m_rcTime.top=578,m_rcTime.right=460,m_rcTime.bottom=596;
	//�ļ�ͼƬ������ļ��ط�ʽ
	//pImage=CSkinManager::GetInstance()->GetSkinItem(L"bkg.jpg");
	//m_Image[IDC_BKG]=pImage;
	//pImage=CSkinManager::GetInstance()->GetSkinItem(L"Close.png");
	//m_Image[IDC_CLOSE_BT]=pImage;
	//pImage=CSkinManager::GetInstance()->GetSkinItem(L"Max.png");
	//m_Image[IDC_MAX_BT]=pImage;
	//pImage=CSkinManager::GetInstance()->GetSkinItem(L"Min.png");
	//m_Image[IDC_MIN_BT]=pImage;

	CMemoryImage::GetInstance()->ImageFromResource(IDB_BKG);//����
	CMemoryImage::GetInstance()->ImageFromResource(IDB_CLOSE);//�ر�
	CMemoryImage::GetInstance()->ImageFromResource(IDB_SET);//����
	CMemoryImage::GetInstance()->ImageFromResource(IDB_MIN);//��С��
	CMemoryImage::GetInstance()->ImageFromResource(IDB_TITLE);//��С��
	CMemoryImage::GetInstance()->ImageFromResource(IDB_BUTTOMEDGE);//��С��
	CMemoryImage::GetInstance()->ImageFromResource(IDB_MAINPAGE);//��ҳ
	CMemoryImage::GetInstance()->ImageFromResource(IDB_FRAME);//ListView����
	CMemoryImage::GetInstance()->ImageFromResource(IDB_LINE);//ListView������
	CMemoryImage::GetInstance()->ImageFromResource(IDB_LISTHOVER);//ListView��꾭��
	CMemoryImage::GetInstance()->ImageFromResource(IDB_LISTPRESS);//ListView��갴��
	CMemoryImage::GetInstance()->ImageFromResource(IDB_PROC_MANAGE);//���̹���
	CMemoryImage::GetInstance()->ImageFromResource(IDB_REMOTECMD);//Զ��CMD
}

void CFireFlyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFireFlyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CFireFlyDlg::LoadPng(UINT ID,CString path)
{
	CString myPath=_T("F:\\Զ��\\FireFly\\FireFly\\res\\")+path;
	m_Image[ID] = Image::FromFile(myPath);
}

// CFireFlyDlg ��Ϣ�������

BOOL CFireFlyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	 this->SetWindowText(L"FireFlyԶ�̿���"); 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CFireFlyDlg::OnPaint()
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
	graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_BKG),0, 0, rcClient.Width(), rcClient.Height());
	//����ͼ��
	graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_TITLE),3, 3, 22, 22);
	//���Ƶױ�������
	graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_BUTTOMEDGE),0, 578, 900, 22);//height����������


	// ���Ʊ������汾
	RectF TitleRect;
	SolidBrush brush((ARGB)Color::White);
	CString sTitleName = L"FireflyԶ�̿��� 1.0 Beta��";
	TitleRect.X=30, TitleRect.Y=5; TitleRect.Width = 200; TitleRect.Height = 17;
	graphics.DrawString(sTitleName.GetBuffer(), sTitleName.GetLength(),&font, TitleRect,&stringFormat, &brush);


	//����������ʾ�� ListView
	RectF InfoRect;
	InfoRect.X = 0, InfoRect.Y = 115, InfoRect.Width = 1120, InfoRect.Height = 560;
	//graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor); 
	graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_FRAME),InfoRect,60,10,
						(REAL)CMemoryImage::GetInstance()->GetImage(IDB_FRAME)->GetWidth(),
						(REAL)CMemoryImage::GetInstance()->GetImage(IDB_FRAME)->GetHeight(),UnitPixel);

	//ListView������
	//for(int i=0;i<21;i++)
	//{
	//	RectF LineRect;
	//	LineRect.X = 0, LineRect.Y = REAL(111 + i*23), LineRect.Width = 900, LineRect.Height = 10; 

	//	graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor); 
	//	graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_LINE),LineRect,5,0,
	//		(REAL)CMemoryImage::GetInstance()->GetImage(IDB_LINE)->GetWidth(),
	//		(REAL)CMemoryImage::GetInstance()->GetImage(IDB_LINE)->GetHeight(),UnitPixel);
	//}
	if(m_iListHover>=0)
	{
		RectF ListHoverRect;
		ListHoverRect.X = 0, ListHoverRect.Y = REAL(138 + m_iListHover*23), ListHoverRect.Width = 900-1, ListHoverRect.Height = 23; 
		graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor); 
		//ͼƬ�Ҵ�5��ʼ����βΪ895 ��������ô����أ�
		//�ȸ߶Ⱥ���
		graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_LISTHOVER),ListHoverRect,5,0,
			893,
			23,UnitPixel);
	}

	if(m_iListPress>=0)
	{
		RectF ListHoverRect;
		ListHoverRect.X = 0, ListHoverRect.Y = REAL(138 + m_iListPress*23), ListHoverRect.Width = 900-1, ListHoverRect.Height = 23; 
		graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor); 
		//ͼƬ�Ҵ�5��ʼ����βΪ895 ��������ô����أ�
		//�ȸ߶Ⱥ���
		graphics.DrawImage(CMemoryImage::GetInstance()->GetImage(IDB_LISTPRESS),ListHoverRect,0,0,
			900,
			23,UnitPixel);
	}

	//ListView����
	RectF ListViewTitleRect;
	SolidBrush ListViewTitlebrush((ARGB)Color::Black);
	CString sListViewTitleName = L"IP��ַ";
	TitleRect.X=10, TitleRect.Y=117; TitleRect.Width = 50; TitleRect.Height = 17;
	graphics.DrawString(sListViewTitleName.GetBuffer(), sListViewTitleName.GetLength(),&font, TitleRect,&stringFormat, &ListViewTitlebrush);

	sListViewTitleName = L"�������";
	TitleRect.X=150, TitleRect.Y=117; TitleRect.Width = 150; TitleRect.Height = 17;
	graphics.DrawString(sListViewTitleName.GetBuffer(), sListViewTitleName.GetLength(),&font, TitleRect,&stringFormat, &ListViewTitlebrush);

	sListViewTitleName = L"����ϵͳ";
	TitleRect.X=400, TitleRect.Y=117; TitleRect.Width = 150; TitleRect.Height = 17;
	graphics.DrawString(sListViewTitleName.GetBuffer(), sListViewTitleName.GetLength(),&font, TitleRect,&stringFormat, &ListViewTitlebrush);

	sListViewTitleName = L"�ڴ�";
	TitleRect.X=600, TitleRect.Y=117; TitleRect.Width = 150; TitleRect.Height = 17;
	graphics.DrawString(sListViewTitleName.GetBuffer(), sListViewTitleName.GetLength(),&font, TitleRect,&stringFormat, &ListViewTitlebrush);

	sListViewTitleName = L"����λ��";
	TitleRect.X=700, TitleRect.Y=117; TitleRect.Width = 150; TitleRect.Height = 17;
	graphics.DrawString(sListViewTitleName.GetBuffer(), sListViewTitleName.GetLength(),&font, TitleRect,&stringFormat, &ListViewTitlebrush);

	//���Ƶױ�����Ϣ
	SolidBrush Bottombrush((ARGB)Color::Black);
	RectF BottomRect;
	CString sBottomName = L"������汾��1.0.0.0000";
	BottomRect.X=3,BottomRect.Y=578,BottomRect.Width=900,TitleRect.Height=18;
	graphics.DrawString(sBottomName.GetBuffer(), sBottomName.GetLength(),&font, BottomRect,&stringFormat, &Bottombrush);

	sBottomName=L"��ǰʱ�䣺";
	BottomRect.X=200,BottomRect.Y=578,BottomRect.Width=80,TitleRect.Height=18;
	graphics.DrawString(sBottomName.GetBuffer(), sBottomName.GetLength(),&font, BottomRect,&stringFormat, &Bottombrush);

	sBottomName=L"����������";
	BottomRect.X=600,BottomRect.Y=578,BottomRect.Width=80,TitleRect.Height=18;
	graphics.DrawString(sBottomName.GetBuffer(), sBottomName.GetLength(),&font, BottomRect,&stringFormat, &Bottombrush);

	//��ʾ����ʱ��
	CString sTime;
	m_custom.MyGetTime(sTime);
	BottomRect.X=270,BottomRect.Y=578,BottomRect.Width=180,TitleRect.Height=18;
	graphics.DrawString(sTime.GetBuffer(), sTime.GetLength(),&font, BottomRect,&stringFormat, &Bottombrush);


	//�������Ͻ�������ť
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

	/*
	rtButton.left=25;
	rtButton.top=45;
	rtButton.right=25+48;
	rtButton.bottom=45+48;
	*/

	SolidBrush Funbrush((ARGB)Color::White);
	CString sFunName=L"��ҳ";
	BottomRect.X=32,BottomRect.Y=95-7,BottomRect.Width=60,TitleRect.Height=30;
	graphics.DrawString(sFunName.GetBuffer(), sFunName.GetLength(),&font, BottomRect,&stringFormat, &Funbrush);

	sFunName=L"���̹���";
	BottomRect.X=102,BottomRect.Y=95-7,BottomRect.Width=60,TitleRect.Height=30;
	graphics.DrawString(sFunName.GetBuffer(), sFunName.GetLength(),&font, BottomRect,&stringFormat, &Funbrush);

	sFunName=L"Զ��CMD";
	BottomRect.X=177,BottomRect.Y=95-7,BottomRect.Width=70,TitleRect.Height=30;
	graphics.DrawString(sFunName.GetBuffer(), sFunName.GetLength(),&font, BottomRect,&stringFormat, &Funbrush);

	//���ƹ��ܰ�ť,����Ǿ���״̬ ����Ҫ��������һ��ͼƬ >IDC_MAINPAGE_BT�����ఴť����Ҫ���Ʊ���
	if(m_iCommandButtonHovering>=IDC_MAINPAGE_BT) //������������
	{
		Image *pBackHover = CMemoryImage::GetInstance()->ImageFromResource(IDB_HOVER);
		m_rcBtn[m_iCommandButtonHovering].DrawButton(graphics,pBackHover);
	}

	if(m_iCommandButtonPushed>=IDC_MAINPAGE_BT) //�������갴��
	{
		Image *pBackPushed = CMemoryImage::GetInstance()->ImageFromResource(IDB_PUSHED);
		m_rcBtn[m_iCommandButtonPushed].DrawButton(graphics,pBackPushed);
	}
	CDialogEx::OnPaint();

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFireFlyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CFireFlyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//������ʾһ��800*600�ĶԻ���
	CRect DlgRect(0,0,900,600);
	CWnd::SetWindowPos(NULL,0,0,DlgRect.Width(),DlgRect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	CenterWindow(GetParent());

	CRect rcClient;
	GetClientRect(&rcClient);
	
	//����һ��Բ�Ǳ߿�
	CRgn rgnClient;													//6λԲ�νǶ�
	rgnClient.CreateRoundRectRgn(0,0,rcClient.Width(),rcClient.Height(),6,6);
	SetWindowRgn(rgnClient,FALSE); 

	//�رհ�ť��λ��
	CRect rtButton;
	CRect rtTempButton;
	CGDIButton dButton;

	GetClientRect(&rtButton);
	rtTempButton=rtButton;

	//����ڶԻ���İ�ťλ��

	//����900*600�ĶԻ������  �رհ�ťͼƬ188*22
	//�رհ�ť
	rtButton.left=900-47;
	rtButton.top=0;
	rtButton.right=900;
	rtButton.bottom=22;

	//����MAP�� ���ÿ������캯�������ɶ��󸱱��������������������ʱ���󣬲�Ӱ��map�еĶ���
	dButton.CreateButton(_T("�ر�"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_CLOSE),4,IDC_CLOSE_BT);
	m_rcBtn[IDC_CLOSE_BT]=dButton;

	////��󻯰�ť     ��󻯰�ťͼƬ 132*22
	rtButton.left=900-47-33;
	rtButton.top=0;
	rtButton.right=900-47;
	rtButton.bottom=22;

	dButton.CreateButton(_T("���"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_SET),4,IDC_SET_BT);
	m_rcBtn[IDC_SET_BT]=dButton;

	////��С����ť ��С����ťͼƬ 132*22
	rtButton.left=900-47-33-33;
	rtButton.top=0;
	rtButton.right=900-47-33;
	rtButton.bottom=22;

	dButton.CreateButton(_T("��С��"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_MIN),4,IDC_MIN_BT);
	m_rcBtn[IDC_MIN_BT]=dButton;

	//��ҳ��ť
	//���й��ܰ�ťͼƬ����48*48
	rtButton.left=25;
	rtButton.top=38;
	rtButton.right=25+48;
	rtButton.bottom=38+48;
	dButton.CreateButton(_T("��ҳ"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_MAINPAGE),1,IDC_MAINPAGE_BT);
	m_rcBtn[IDC_MAINPAGE_BT]=dButton;

	rtButton.left=25+80;
	rtButton.top=38;
	rtButton.right=25+48+80;
	rtButton.bottom=38+48;
	dButton.CreateButton(_T("���̹���"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_PROC_MANAGE),1,IDC_PROC_MANAGE_BT);
	m_rcBtn[IDC_PROC_MANAGE_BT]=dButton;

	rtButton.left=25+80+80;
	rtButton.top=38;
	rtButton.right=25+48+80+80;
	rtButton.bottom=38+48;
	dButton.CreateButton(_T("Զ��CMD"),&rtButton,this,CMemoryImage::GetInstance()->GetImage(IDB_REMOTECMD),1,IDC_REMOTECMD_BT);
	m_rcBtn[IDC_REMOTECMD_BT]=dButton;

	//�±���ʱ�䶨ʱ��
	//SetTimer(1,1000,NULL);

	AfxBeginThread(m_ClientSock.MyControllingFunction,this);

	return 0;
}


void CFireFlyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize=sizeof(TRACKMOUSEEVENT);
		tme.dwFlags=TME_LEAVE|TME_HOVER;
		tme.hwndTrack=m_hWnd;
		tme.dwHoverTime=10;
		m_bTracking=TRUE;
	}

	CRect rtButton;
	//CRect rtWindow;
	//GetClientRect(&rtWindow);

	//��������λ���ڲ��ڰ�ť��Χ��
	int iButton = ButtonHitTest(point, rtButton);

	if(iButton>=IDC_MAINPAGE_BT)
	{
		m_iCommandButtonHovering=iButton;
	}

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
			m_iCommandButtonHovering= -1;
		}
		//����һ����ť�Ľ���
		if(iButton != -1)
		{
			m_iSystemButtonHovering = iButton;
			m_rcBtn[m_iSystemButtonHovering].MouseHover();
		}
	}

	//�������ͣ������һ��
	if(point.y>138 && point.y<575)
	{
		CRect rcListLine;
		m_iListHover=int(point.y/23)-6;
		rcListLine.left=0;
		rcListLine.top=138 + m_iListHover*23;
		rcListLine.right=900;
		rcListLine.bottom=138+m_iListHover*23+23;
		InvalidateRect(rcListLine);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CFireFlyDlg::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_iSystemButtonHovering=-1;
	CDialogEx::OnMouseLeave();
}


void CFireFlyDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnMouseHover(nFlags, point);
}

UINT CFireFlyDlg::ButtonHitTest(CPoint pt,CRect& rcButton)
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


//
//OnEraseBkgnd :�ڴ��ڱ�����Ҫ�ػ�ʱ����.
//OnPaint : ��ʱOnEraseBkgnd�Ѿ����ù���,�����ڴ���Ӧ�������ڶԱ������еĲ���������
//�Ȳ����ٻ��ƣ�return TRUE ����Ҫ���������������ɫ������˸
BOOL CFireFlyDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}


void CFireFlyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcButton;
	int iButton=this->ButtonHitTest(point,rcButton);

	//����m_iCommandButtonPushed�Ѱ��µ�ID��ֵ
	if(iButton!=-1)
	{
		m_iCommandButtonPushed=iButton;
		this->m_rcBtn[iButton].LButtonDown();
		return;
	}
	//���ڶ�������105������ Ϊ������
	if(point.y < 115 /*&& point.x<787*/)   // ��ƭϵͳ��Ϊ�����϶������� �ó�������ť��λ��
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
		return;
	}

	//�������ͣ������һ��
	if(point.y>138 && point.y<575)
	{
		CRect rcListLine;
		m_iListPress=int(point.y/23)-6;
		rcListLine.left=0;
		rcListLine.top=138 + m_iListPress*23;
		rcListLine.right=900;
		rcListLine.bottom=138+m_iListPress*23+23;
		InvalidateRect(rcListLine);
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}


void CFireFlyDlg::OnLButtonUp(UINT nFlags, CPoint point)
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


BOOL CFireFlyDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case IDC_CLOSE_BT:
			{
				SendMessage( WM_SYSCOMMAND,SC_CLOSE);
			}
			break;
		case IDC_SET_BT:
			{
				//SendMessage( WM_SYSCOMMAND,SC_MAXIMIZE);
			}
			break;
		case IDC_MIN_BT:
			{
				SendMessage( WM_SYSCOMMAND,SC_MINIMIZE);
			}
			break;
		case IDC_MAINPAGE_BT:
			{
				MessageBoxW(L"��ҳ",0,0);
			}
			break;
	}
	return CDialogEx::OnCommand(wParam, lParam);
}


void CFireFlyDlg::OnTimer(UINT_PTR nIDEvent)
{
	this->InvalidateRect(m_rcTime);
	//bUpdateTime=TRUE;
	CDialogEx::OnTimer(nIDEvent);
}
