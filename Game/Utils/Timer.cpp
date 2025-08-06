#include "Timer.h"

Timer::Timer(float TargetTime) : targetTime(TargetTime)
{

}

void Timer::Tick(float DeltaTime)
{
	//����ð������� Tick���� DeltaTime�� ��� ���ؼ� ī��Ʈ��Ŵ
	elaspedTime += DeltaTime; 
}

bool Timer::Update(float DeltaTime)
{
	if(IsComplete == true)
		return false;

	elaspedTime += DeltaTime;

	if (IsTimeOut())
	{
		IsComplete = true;
		return true;
	}

	return false;
}

void Timer::Reset()
{
	elaspedTime = 0.0f;
	IsComplete = false;
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

bool Timer::GetIsPause() const
{
	return IsPause;
}

void Timer::SetIsPause()
{
	IsPause = !IsPause;
}
