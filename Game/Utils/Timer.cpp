#include "Timer.h"

Timer::Timer(float TargetTime) : targetTime(TargetTime)
{

}

void Timer::Tick(float DeltaTime)
{
	//경과시간변수에 Tick에서 DeltaTime을 계속 더해서 카운트시킴
	elaspedTime += DeltaTime; 
}

void Timer::Reset()
{
	elaspedTime = 0.0f;
}

bool Timer::IsTimeOut() const
{
	//경과시간이 타겟시간랑 같이지거나 지나면 true를 출력함
	return elaspedTime >= targetTime;
}

void Timer::SetTargetTime(float newTargetTime)
{
	targetTime = newTargetTime;
}
