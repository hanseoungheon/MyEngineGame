#pragma once

// 초 단위로 시간계산에 필요할 때 사용.
// EX) 3초가 지났는지등을 사용할 때 사용

class Timer
{
public:
	Timer(float TargetTime = 0.0f);

	//초시계의 시간이 흘러가도록 하기 위해 필수적인 장치 
	void Tick(float DeltaTime);

	//타이머 리셋시키는 함수
	void Reset();

	//셋팅해놓은 시간이 경과했는지 확인하는 함수
	bool IsTimeOut() const;

	//타이머 시간 변경 함수
	void SetTargetTime(float newTargetTime);

private:
	float elaspedTime = 0.0f; //경과시간
	float targetTime = 0.0f; //목표 시간 (설정한 시간)
};