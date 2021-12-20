#pragma once


class TimeController :public Singleton<TimeController>
{

private:

	__int64 m_Frequency;

	LARGE_INTEGER m_StartTimeStamp;
	LARGE_INTEGER m_EndTimeStamp;

	__int64 m_ElaspedTime;

	float m_FPS;				// 원하는 FPS
	float m_TargetElaspedTime;	//그래서 도달해야하는 시간(예: 16.7ms)
public:
	TimeController();
	~TimeController();
public:

	void Initialize();

	//프레임 설정
	void SetFPS(float fps);

	//지나온 시간 체크
	void CheckTime();
	//시간 체크 시작
	void StartTimeStamp();
	//시간 체크 끝
	void EndTimeStamp();

	float GetElaspedTimeSec() const;

	//프레임 체크
	bool FPSCheck();

};