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
	int hp = 92; //플레이어의 체력

	//플레이어의 죽음처리를 위한 변수
	bool isPlayerDead = false;

	//플레이어 죽은 위치 정보
	Vector2 PlayerDeadPosition;

	//UI컨트롤러
	int UIcontroller; 

	int PlayerHp;

	int count = 0;

	bool IsMap = true;
public:
	void DeleteMap();

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

public:
	//4방향 블래스터 & 4방향 브레스
	void MakeBlaster4();
	void Breath4();
	
	//X자블래스터 & X자 브레스
	void MakeXBlaster();
	void BreathX();

	//대형 블래스터 & 필살빔
	void MakeBigBlaster();
	void BreathBig();
};