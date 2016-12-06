
#pragma once
#include <map>
using namespace std;

//�ڴ�ͼƬ������
class CMemoryImage
{
public:
	static CMemoryImage * GetInstance();
	map<UINT, Image*> m_pImage;
	~CMemoryImage(void);

	// �ͷ����н�����Դ
	void	Release();
	static void UnLoad();
	// �ͷŽ�����ԴId���ؽ�����Դ
	Image*	ImageFromResource(UINT uId);
	//ͨ���ؼ�ID���ͼƬָ��
	Image* CMemoryImage::GetImage(UINT uID);
private:
	CMemoryImage(void);
	static CMemoryImage* m_Instance; //Ψһ��ʵ��
	Image*	FromResource(UINT uId);
	//map<UINT, Image*> m_pImage;
};
