#pragma once
#include "Level/Level.h"
#include "Utils/Timer.h"
#include "UI/MultiLine_UI.h"
#include "Math/Vector2.h"
#include  "Actor/BreathActor.h"
#include "Actor/Monster.h"
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
	int UIcontrollerNum; 

	int PlayerHp;

	int count = 0;

	bool IsMapSmall = true;
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
	void Stage1_6(float DeltaTime);
	void Stage1_7(float DeltaTime);
	void Stage1_8(float DeltaTime);
	void Stage1_9(float DeltaTime);
	void Stage1_10(float DeltaTime);
	void Stage1_11(float DeltaTime);
	void Stage1_12(float DeltaTime);
	void Stage1_13(float DeltaTime);
	void Stage1_14(float DeltaTime);
	void Stage1_15(float DeltaTime);
	void Stage1_16(float DeltaTime);
	void Stage1_17(float DeltaTime);

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
	Timer TStage_1_6;
	Timer TStage_1_7;
	Timer TStage_1_8;
	Timer TStage_1_9;
	Timer TStage_1_10;
	Timer TStage_1_11;
	Timer TStage_1_12;
	Timer TStage_1_13;
	Timer TStage_1_14;
	Timer TStage_1_15;
	Timer TStage_1_16;
	Timer TStage_1_17;

	//�������� 2 Ÿ�̸�
	Timer TStage_1_17;

	//�� ī��Ʈ
	int TurnCount;
	bool bSansIsMoving = false;
	//bool bSansLeftRight = true;
public:
	//4���� ������ & 4���� �극��
	void MakeBlaster4();
	void DeleteBlaster4(Monster* monsterActor);
	void Breath4();
	
	//X�ں����� & X�� �극��
	void MakeXBlaster();
	void DeleteXBlaster(Monster* monsterActor);
	void BreathX();

	//���� ������ & �ʻ��
	void MakeBigBlaster();
	void DeleteBigBlaster(Monster* monsterActor);
	void BreathBig();

	void DeleteBreath(BreathActor* breaths);

};