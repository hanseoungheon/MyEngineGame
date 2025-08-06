#pragma once

// �� ������ �ð���꿡 �ʿ��� �� ���.
// EX) 3�ʰ� ������������ ����� �� ���

class Timer
{
public:
	Timer(float TargetTime = 0.0f);

	//�ʽð��� �ð��� �귯������ �ϱ� ���� �ʼ����� ��ġ 
	void Tick(float DeltaTime);

	//�ѹ� �۵��ϰ� ���ߴ� Ÿ�̸�
	bool Update(float DeltaTime);

	//Ÿ�̸� ���½�Ű�� �Լ�
	void Reset();

	//�����س��� �ð��� ����ߴ��� Ȯ���ϴ� �Լ�
	bool IsTimeOut() const;

	//Ÿ�̸� �ð� ���� �Լ�
	void SetTargetTime(float newTargetTime);

	bool GetIsPause() const;
	void SetIsPause();
private:
	float elaspedTime = 0.0f; //����ð�
	float targetTime = 0.0f; //��ǥ �ð� (������ �ð�)
	bool IsComplete = false;
	bool IsPause = false;
};