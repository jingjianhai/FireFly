#pragma once

#include <GdiPlus.h>
using namespace Gdiplus;

class CGDIButton
{
public:
	// ��׼���캯��
	CGDIButton()
	{
		m_bCheck = FALSE;
		m_bHovering = FALSE;
		m_bPressed = FALSE;
		m_bDisabled = FALSE;
		m_pIcon = NULL;
		m_pParent = NULL;
	}

	virtual ~CGDIButton(){}

	// ���ð�ť����λ��
	void SetRect(LPCRECT lpRect);
	// ��ȡ��ť����λ��
	void GetRect(LPRECT lpRect){*lpRect = *m_rcRect;}
	// ���ָ�����Ƿ��ڰ�ť��
	BOOL PtInButton(CPoint& point){return m_rcRect.PtInRect(point);}
	// ���ư�ť
	void DrawButton( Gdiplus::Graphics&  graphics);
	void DrawButton( Gdiplus::Graphics&  graphics,Image* pImage);

	// ������ť
	void CreateButton(LPCTSTR lpszCaption,LPRECT lpRect,CWnd* pParent, Image* pImage, UINT nCount = 4, UINT nID = 0);
	//���ð�ťͼ����Ϣ
	void  SetIconInfo(Image *pIcon,CPoint ptPos = CPoint(5,3),BOOL bRedraw=FALSE);
	// ���ð�ť״̬
	void EnableButton(BOOL bEnable)
	{
		m_bDisabled = !bEnable;
		m_pParent->InvalidateRect(m_rcRect);
	}

	// ���ð�ťѡ��״̬
	void SetCheck(BOOL bCheck)
	{
		m_bCheck = bCheck;
		m_pParent->InvalidateRect(m_rcRect);
	}
	// ��ȡ��ťId
	UINT GetControlId(){return m_nID;};
	// ������ť�¼�
	void DoCommand()
	{
		if(!m_bDisabled)
		{
			m_bCheck = !m_bCheck;
			m_pParent->InvalidateRect(m_rcRect);
			m_pParent->PostMessage(WM_COMMAND, m_nID);
		}
	}

	// ��갴�°�ť�¼�
	void LButtonDown()
	{
		if(!m_bDisabled)
		{
			m_bPressed = TRUE;
			m_pParent->InvalidateRect(m_rcRect);
		}
	};
	// �����°�ť�¼�
	void LButtonUp()
	{
		if(!m_bDisabled)
		{
			if(m_bPressed == TRUE)
			{
				m_bCheck = !m_bCheck;
				m_bPressed = FALSE;
				m_pParent->InvalidateRect(m_rcRect);
				m_pParent->PostMessage(WM_COMMAND, m_nID);
			}
		}
	}
	// �����밴ť�����¼�
	void MouseHover()
	{
		if(!m_bDisabled)
		{
			m_bHovering = TRUE;
			m_pParent->InvalidateRect(m_rcRect);
		}
	}
	// ����뿪��ť�����¼�
	void MouseLeave()
	{
		if(!m_bDisabled)
		{
			m_bPressed = FALSE;
			m_bHovering = FALSE;
			m_pParent->InvalidateRect(m_rcRect);
		}
	}

protected:
	// ��ť����λ��
	CRect	m_rcRect;
	// ��ʶ�����밴ť����
	BOOL	m_bHovering;
	// ��ʶ�Ѿ������ť
	BOOL	m_bPressed;
	// ��ʶ��ť�Ѿ�������
	BOOL	m_bDisabled;
	// ��ʶ��ť�Ѿ���ѡ��
	BOOL	m_bCheck;
	// ��ťͼƬ
	Image *m_pImage;
	// ��ťͼƬ�а�����ͼƬ����
	UINT	m_nImageCount;

	//ͼ��(һ����ť���Ը�������һ��Сͼ��)
	Image *m_pIcon;
	//ͼ�����Ͻ�λ��
	CPoint m_ptIcon;

	// ��ťId��
	int		m_nID;
	// ��ť������
	CWnd*	m_pParent;
	//��ť�����ı�
	CString m_strCaption;
};
