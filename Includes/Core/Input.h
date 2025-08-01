#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;

	struct KeyState
	{
		//현재 프레임에 키가 눌려있는지 확인
		bool isKeyDown = false;

		//이전 프레임에 키가 눌렸었는지 확인
		bool previouseKeyDown = false;
	};

public:
	Input();

	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);

	static Input& GetController();
private:
	void ProcessInput();
	void SavePreviousKeyStates();

	//키 입력 정보 관리 변수
	KeyState keyStates[255] = {};

	//싱글톤 함수 => 왜? 컨트롤러는 단 하나만 존재해야하니깐!
	static Input* instance;
};
