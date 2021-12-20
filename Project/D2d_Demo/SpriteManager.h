#pragma once
struct SpriteInfo;

class SpriteManager :public Singleton<SpriteManager>
{
private:
	//SpriteInfo�� �������� �ε��ϰ� ��γ�, ���� �̸��� Ű�� ��������
	//��ü�� �׸��� ���� �� �ִ� ���
	//2�� ū ��������Ʈ�� �߶󳻼� �Ŵ����� ������ �ֱ�
	//3�� ������Ʈ ���� static�ϰ� �̹����� ������ �ֱ�

	//���� ��� = Ű
	//�� ��Ʈ��
	std::map<PCWSTR, ID2D1Bitmap*> mBitmapMap;

public:
	//map<PCWSTR, vector<SpriteInfo*>> mSpriteInfo;
	void LoadImageFile(PCWSTR uri);

	ID2D1Bitmap* GetSpriteByPath(PCWSTR path);

	//������ �ε�
	//void LoadAllSpriteDataByFile();
	//void LoadAllBitMapByFile();


	//vector<SpriteInfo> GetAnimtaionData(PCWSTR uri, int motion, int maxfrm, int width, int height, POINT pivot);
	SpriteInfo GetAniData(int frm, PCWSTR uri, int motion, int width, int height, POINT pivot);
};

