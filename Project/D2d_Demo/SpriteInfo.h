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
	PCWSTR		FileName;		//파일 이름 
	int			Motion;			//모션 번호
	int			Frame;			// 프레임
	D2D1_RECT_F	SrcRect;		//스프라이트 크기	
	POINT		Pivot;			//피벗
	float		Delay;			//딜레이
};

