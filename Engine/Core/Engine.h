#pragma once
#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level; //전방선언

struct EngineSetting
{
	//콘솔화면 가로 크기
	int width = 0;

	//콘솔화면 세로 크기
	int height = 0;

	//타겟 프레임 속도
	float framerate = 0.0f;
};
class Engine_API Engine
{
public:
	Engine();

	virtual ~Engine();

	void Run();

	static Engine& Get(); //싱글톤 접근 함수!

	void AddLevel(Level* newLevel);

	virtual void CleanUp();

	void Quit();

	int Width() const;
	int Height() const;

private:
	void BeginPlay();
	void Tick(float DeltaTime = 0.0f);
	void Render();

	//엔진 설정 로드 함수
	void LoadEngineSetting();

private:
	//엔진 종료 플래그
	bool isQuit = false;

	Level* mainLevel = nullptr;

	Input controller;

	static Engine* instance;
	//엔진은 단 한개만 존재해야하고 그 엔진이 총괄해야하니깐 싱글톤 구현

	EngineSetting settings;
};