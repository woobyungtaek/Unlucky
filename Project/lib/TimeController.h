#pragma once


class TimeController :public Singleton<TimeController>
{

private:

	__int64 m_Frequency;

	LARGE_INTEGER m_StartTimeStamp;
	LARGE_INTEGER m_EndTimeStamp;

	__int64 m_ElaspedTime;

	float m_FPS;				// ���ϴ� FPS
	float m_TargetElaspedTime;	//�׷��� �����ؾ��ϴ� �ð�(��: 16.7ms)
public:
	TimeController();
	~TimeController();
public:

	void Initialize();

	//������ ����
	void SetFPS(float fps);

	//������ �ð� üũ
	void CheckTime();
	//�ð� üũ ����
	void StartTimeStamp();
	//�ð� üũ ��
	void EndTimeStamp();

	float GetElaspedTimeSec() const;

	//������ üũ
	bool FPSCheck();

};