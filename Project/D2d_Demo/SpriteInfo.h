#pragma once
struct SpriteInfo
{
/*public:
	SpriteInfo() {};
	SpriteInfo(PCWSTR fileName,int motion,int order, D2D1_RECT_F srcRect,POINT pivot,float delay) :
	FileName(fileName), Motion(motion), Frame(order), SrcRect(srcRect), Pivot(pivot), Delay(delay){};
	~SpriteInfo() {};
*/
//public:
	PCWSTR		FileName;		//���� �̸� 
	int			Motion;			//��� ��ȣ
	int			Frame;			// ������
	D2D1_RECT_F	SrcRect;		//��������Ʈ ũ��	
	POINT		Pivot;			//�ǹ�
	float		Delay;			//������
};

