#include "StdAfx.h"
#include "GDIButton.h"


// ���ư�ť
void CGDIButton::DrawButton( Gdiplus::Graphics&  graphics)
{
	// ��ȡ��ťͼƬ��Ϣ
	UINT iCount = m_nImageCount;
	int	iButtonIndex = 0;
	if(m_bDisabled && iCount >= 4) iButtonIndex = 3;
	else if(m_bPressed && iCount >= 3)iButtonIndex = 2;
	else if(m_bHovering && iCount >= 2)iButtonIndex = 1;
	else iButtonIndex = 0;

	// ��ָ��λ�û��ư�ť
	int iWidth = m_pImage->GetWidth()/iCount;
	int iHeight = m_pImage->GetHeight();
	RectF grect;
	grect.X=(Gdiplus::REAL)m_rcRect.left;
	grect.Y=(Gdiplus::REAL)m_rcRect.top;
	grect.Width = (Gdiplus::REAL)m_rcRect.Width();
	grect.Height = (Gdiplus::REAL)m_rcRect.Height();

	graphics.DrawImage(m_pImage, grect, (Gdiplus::REAL)iWidth*iButtonIndex,0,(Gdiplus::REAL)iWidth,(Gdiplus::REAL)iHeight, UnitPixel);

}

// ���ư�ť ���� ���ݴ�������ͼƬ�������
void CGDIButton::DrawButton( Gdiplus::Graphics&  graphics,Image* pImage)
{
	// ��ȡ��ťͼƬ��Ϣ
	UINT iCount = m_nImageCount;
	int	iButtonIndex = 0;

	// ��ָ��λ�û��ư�ť
	int iWidth = pImage->GetWidth();
	int iHeight = pImage->GetHeight();
	RectF grect;
	grect.X=(Gdiplus::REAL)m_rcRect.left-15;
	grect.Y=(Gdiplus::REAL)m_rcRect.top-5;
	grect.Width = (Gdiplus::REAL)m_rcRect.Width()+30;
	grect.Height = (Gdiplus::REAL)m_rcRect.Height()+30;

	graphics.DrawImage(pImage, grect, (Gdiplus::REAL)iWidth*iButtonIndex,0,(Gdiplus::REAL)iWidth,(Gdiplus::REAL)iHeight, UnitPixel);

}


// ������ť 
void CGDIButton::CreateButton(LPCTSTR lpszCaption,LPRECT lpRect,CWnd* pParent, Image* pImage, UINT nCount/* = 4*/, UINT nID/* = 0*/)
{
	if (lpszCaption)
	{
		m_strCaption = lpszCaption;
	}
	m_pParent = pParent;
	m_rcRect = lpRect;
	m_pImage = pImage;
	m_nImageCount = nCount;
	m_nID = nID;
}

//���ð�ťͼ����Ϣ
void  CGDIButton::SetIconInfo(Image *pIcon,CPoint ptPos/* = CPoint(5,3)*/,BOOL bRedraw/*=FALSE*/)
{
    m_pIcon = pIcon;
	m_ptIcon = CPoint(m_rcRect.left+ptPos.x,m_rcRect.top+ptPos.y);
	if (bRedraw)
	{
		m_pParent->InvalidateRect(&m_rcRect);
	}
}

void CGDIButton::SetRect(LPCRECT lpRect)
{
	CPoint ptIconOrg(m_ptIcon.x - m_rcRect.left,m_ptIcon.y - m_rcRect.top);
	m_rcRect = lpRect;
	m_ptIcon = CPoint(m_rcRect.left+ptIconOrg.x,m_rcRect.top+ptIconOrg.y);
}