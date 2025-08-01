#include "Timer.h"

Timer::Timer(float TargetTime) : targetTime(TargetTime)
{

}

void Timer::Tick(float DeltaTime)
{
	//����ð������� Tick���� DeltaTime�� ��� ���ؼ� ī��Ʈ��Ŵ
	elaspedTime += DeltaTime; 
}

void Timer::Reset()
{
	elaspedTime = 0.0f;
}

bool Timer::IsTimeOut() const
{
	//����ð��� Ÿ�ٽð��� �������ų� ������ true�� �����
	return elaspedTime >= targetTime;
}

void Timer::SetTargetTime(float newTargetTime)
{
	targetTime = newTargetTime;
}
