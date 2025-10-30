#pragma once
#include "GameObject.h"

//class GameObject;
class Component
{
public:
	
	Component() : m_GameObj(nullptr) {}
	Component(GameObject* gameObj) : m_GameObj{ gameObj } {}
	virtual ~Component() {}
	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

private:
protected:
	GameObject* m_GameObj;
};