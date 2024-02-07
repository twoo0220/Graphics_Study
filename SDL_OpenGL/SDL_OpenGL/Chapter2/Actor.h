#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	// 액터의 상태를 추적하는데 사용
	enum State
	{
		EActive,
		EPausem,
		EDead
	};
	Actor(class Game* game);
	virtual ~Actor();

	// Game에서 호출하는 Update 함수
	void Update(float deltaTime);
	// 액터에 부착된 모든 컴포넌트를 업데이트
	void UpdateComponents(float deltaTime);
	// 특정 액터에 특화된 업데이트 코드
	virtual void UpdateActor(float deltaTime);

	// Getters/Setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	class Game* getGame() { return mGame; }

	void AddComponent(class Component* component);
	void RemoveComponenet(class Component* component);

private:
	State mState;									// 액터의 상태
	Vector2 mPosition;								// 액터의 중심점
	float mScale;									// 액터의 배율 (100%의 경우 1.0f)
	float mRotation;								// 회전 각도 (라디안)
	std::vector<class Component*> mComponents;		// 액터가 보유한 컴포넌트
	class Game* mGame;
};
