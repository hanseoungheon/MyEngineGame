#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Core.h"
#include <Windows.h>
#include "RTTI.h"

class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor, RTTI)


public:
	Actor(const char* image = " ", Color color = Color::White,
		const Vector2& position = Vector2::Zero,bool IsUI = false);

	virtual ~Actor();

	//객체 생애주기에 1번(생성시)만 실행됨
	virtual void BeginPlay();

	//매 프레임마다 호출됨(반복성 작업 Update/Step 등)
	virtual void Tick(float DeltaTime);

	//cmd창에 문자를 출력해서 그리는 함수
	virtual void Render();

	//BeginPlay 호출여부 확인
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetPosition(const Vector2& newPosition);
	Vector2 GetActorPosition() const;

	//문자열 길이 반환
	int GetWidth() const;

	//Sorting Order 설정
	void SetSortingOrder(unsigned int sortingOrder);

	//오너십 결정
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	//색상 반환
	Color GetColor() const;

	//색상 설정
	void SetColor(const Color color);

	//충돌 확인 요청 함수 (AABB 로직)
	bool TestIntersect(const Actor* const other);

	//객체 삭제시키는 함수
	void Destroy();

	//게임 종료 요청
	void QuitGame();

protected:
	//객체의 위치
	Vector2 actorPosition;
	
	//그릴 텍스트
	char* image = nullptr;

	//문자열 길이
	int width = 0;

	//문자열 높이
	int height = 0;

	//텍스트 색상값
	Color color; 

	//BeginPlay 호출이 되었는지 확인
	bool hasBeganPlay = false;

	//액터 정렬 순서
	unsigned int sortingOrder = 0;

	//액터가 활성 상태
	bool isActive = true;

	//삭제 요청됐는지 알려주는 변수
	bool isExpired = false;

	//객체를 소유한 레벨
	Level* owner = nullptr;

	const int LeftSide = 40;

	//UI면은 맵 크기에 제한 x
	bool IsUI = false;

	bool IsVisible;
};