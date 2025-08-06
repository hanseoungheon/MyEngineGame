#pragma once
#include "Level/Level.h"
#include "Utils/Timer.h"
#include "UI/MultiLine_UI.h"
#include "Math/Vector2.h"
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel,Level)

public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void ControllMainUI(MultiLine_UI* mainUI);
	//void SpawnEnemies(float DeltaTime);
	virtual void Render() override;


private:
	void ReadMapFile(const char* fileName);

	void CheckPlayerGravity();
	void UIController();
	void ProcessCollisionPlayerAndEnemyObject();

private:
	bool PlayerIsTurn = true;
	int UI_OperateNumber = 0;
	int hp = 92; //�÷��̾��� ü��

	//�÷��̾��� ����ó���� ���� ����
	bool isPlayerDead = false;

	//�÷��̾� ���� ��ġ ����
	Vector2 PlayerDeadPosition;

	//UI��Ʈ�ѷ�
	int UIcontroller; 

	int PlayerHp;

	int count = 0;

	bool IsMap = true;
public:
	void DeleteMap();

	//��Ʈ��
	//void LevelTest(float DeltaTime);
	void Intro(float DeltaTime);
	void BlackOut_1(float DeltaTime);

	//�������� 1
	void Stage1_1(float DeltaTime);
	void Stage1_2(float DeltaTime);
	void Stage1_3(float DeltaTime);
	void Stage1_4(float DeltaTime);
	void Stage1_5(float DeltaTime);
	void Stage1_5_1(float DeltaTime);
	void Stage1_5_2(float DeltaTime);
	void Stage1_5_3(float DeltaTime);

private:

	//�ݺ��� �ݺ������ ���� ī��Ʈ����
	int TimerArrayCount = 0;

	//�ݺ��� �ݺ��� �����ϱ� ���� ī��Ʈ ����
	int TimerEndCount = 0;

	//���� ������Ʈ�� ���� �� ����� ���� Ÿ�̸� 
	Timer enemyObejctSpawnTimer;

	//��Ʈ�� Ÿ�̸�
	Timer IntroTimer; //�� ó�� �����Ҷ� ���� Ÿ�̸�
	Timer BurningToHell; //�������� 1 ���������� Ÿ�̸�

	//�������� 1 Ÿ�̸�
	Timer TStage_1_1;
	Timer TStage_1_2;
	Timer TStage_1_3;
	Timer TStage_1_4;
	Timer TStage_1_5;
	Timer TStage_1_5_Array;


};