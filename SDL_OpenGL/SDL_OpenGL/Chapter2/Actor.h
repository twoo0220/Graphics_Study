#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
	// ������ ���¸� �����ϴµ� ���
	enum State
	{
		EActive,
		EPausem,
		EDead
	};
	Actor(class Game* game);
	virtual ~Actor();

	// Game���� ȣ���ϴ� Update �Լ�
	void Update(float deltaTime);
	// ���Ϳ� ������ ��� ������Ʈ�� ������Ʈ
	void UpdateComponents(float deltaTime);
	// Ư�� ���Ϳ� Ưȭ�� ������Ʈ �ڵ�
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
	State mState;									// ������ ����
	Vector2 mPosition;								// ������ �߽���
	float mScale;									// ������ ���� (100%�� ��� 1.0f)
	float mRotation;								// ȸ�� ���� (����)
	std::vector<class Component*> mComponents;		// ���Ͱ� ������ ������Ʈ
	class Game* mGame;
};
