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

	//레벨 시작을 위한 타이머
	Timer levelTimer;

	//공격 오브젝트가 생성 시 계산을 위한 타이머 
	Timer enemyObejctSpawnTimer;

	Timer IntroTimer; //맨 처음 시작할때 쓰는 타이머
	Timer Stage_1_Timer; //스테이지 1 시작을위한 타이머

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

	void LevelTest(float DeltaTime);
	void Stage1(float DeltaTime);
	void Stage2();
};