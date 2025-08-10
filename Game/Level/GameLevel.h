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
	void ReadAttackUIFile(const char* fileName,Color color);
	void MakeAttackUIFile();

	void CheckPlayerGravity();
	void SettingPlayerGravity(bool SetBool);
	void UIController();
	void ProcessCollisionPlayerAndEnemyObject();
	void ProcessCollisionPlayerAndBlock();

private:
	bool PlayerIsTurn = true;
	int UI_OperateNumber = 0;
	int hp = 92; //플레이어의 체력

	//플레이어의 죽음처리를 위한 변수
	bool isPlayerDead = false;

	//플레이어 죽은 위치 정보
	Vector2 PlayerDeadPosition;

	//UI컨트롤러
	int UIcontrollerNum; 

	int PlayerHp;

	int count = 0;

	bool IsMapSmall = true;

	bool AttackTrigger = false;

	bool HadEatenFood;
	bool TurnTwoFristFoodCheck = false;

	//bool isonblock = false;
	bool bGameOverTriggered = false;
	Timer GameOverDelay{ 2.0f };
	bool DieToDark = false;
public:

	void GameOver(float DeltaTime);
	void Die();
	void DieToClearFront();
	void DeleteMap();
	void DeleteAttackUI();

	void TurnStart();
	void TurnStart_MiniMap();
	void TurnEnd();

	void AttackSans();

	void EatItem();
	//인트로
	//void LevelTest(float DeltaTime);
	void Intro(float DeltaTime);
	void BlackOut_1(float DeltaTime);

	//스테이지 1
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

	//스테이지2
	void Stage2_1(float DeltaTime);
	void Stage2_2(float DeltaTime);
	void Stage2_3(float DeltaTime);
	void Stage2_4(float DeltaTime);
	void Stage2_5(float DeltaTime);

	//스테이지3
	void Stage3_1(float DeltaTime);
	void Stage3_2(float DeltaTime);
	void Stage3_3(float DeltaTime);
	void Stage3_4(float DeltaTime);
	void Stage3_5(float DeltaTime);
	void Stage3_6(float DeltaTime);
	void Stage3_7(float DeltaTime);
	void Stage3_8(float DeltaTime);
	void Stage3_9(float DeltaTime);

	//스테이지 4
	void Stage4_1(float DeltaTime);
	void Stage4_2(float DeltaTime);
	void Stage4_3(float DeltaTime);
	void Stage4_3_1(float DeltaTime);
	void Stage4_4(float DeltaTime);
	void Stage4_5(float DeltaTime);
	void Stage4_6(float DeltaTime);
	void Stage4_7(float DeltaTime);

	//스테이지 5
	void Stage5_1(float DeltaTime);
	void Stage5_2(float DeltaTime);
	void Stage5_3(float DeltaTime);
	void Stage5_4(float DeltaTime);

private:

	//반복시 반복재생을 위한 카운트변수
	int TimerArrayCount = 0;

	//반복시 반복을 종료하기 위한 카운트 변수
	int TimerEndCount = 0;

	//공격 오브젝트가 생성 시 계산을 위한 타이머 
	Timer enemyObejctSpawnTimer;

	//인트로 타이머
	Timer IntroTimer; //맨 처음 시작할때 쓰는 타이머
	Timer BurningToHell; //스테이지 1 시작을위한 타이머

	//스테이지 1 타이머
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

	//스테이지 2 타이머
	Timer TStage_2_1;
	Timer TStage_2_2;
	Timer TStage_2_3;
	Timer TStage_2_4;
	Timer TStage_2_5;

	//스테이지 3 타이머
	Timer TStage_3_1;
	Timer TStage_3_2;
	Timer TStage_3_3;
	Timer TStage_3_4;
	Timer TStage_3_5;
	Timer TStage_3_6;
	Timer TStage_3_7;
	Timer TStage_3_8;
	Timer TStage_3_9;

	//스테이지 4 타이머
	Timer TStage_4_1;
	Timer TStage_4_2;
	Timer TStage_4_3;
	Timer TStage_4_3_1;
	Timer TStage_4_4;
	Timer TStage_4_5;
	Timer TStage_4_6;
	Timer TStage_4_7;

	//스테이지 5 타이머
	Timer TStage_5_1;
	Timer TStage_5_2;
	Timer TStage_5_3;
	Timer TStage_5_4;


	//턴 카운트
	int TurnCount;
	bool bSansIsMoving = false;
	
	//게임 오버 체크
	//bool bSansLeftRight = true;
public:
	void Attack();
	void AttackAndStartTurn(int TurnCount);
	//4방향 블래스터 & 4방향 브레스
	void MakeBlaster4();
	void DeleteBlaster4(Monster* monsterActor);
	void Breath4();
	
	//X자블래스터 & X자 브레스
	void MakeXBlaster();
	void DeleteXBlaster(Monster* monsterActor);
	void BreathX();

	//대형 블래스터 & 필살빔
	void MakeBigBlaster();
	void DeleteBigBlaster(Monster* monsterActor);
	void BreathBig();

	void DeleteBreath(BreathActor* breaths);

};