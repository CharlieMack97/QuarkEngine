#pragma once

#include "GameObject.h"

class Component
{
public:
	Component() = default;
	Component() : m_GameObj(nullptr) {}
	Component(GameObj* gameObj) : m_GameObj{ gameObj } {}
	virtual ~Component() {}
	virtual void Start() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

private:
protected:
	GameObj* m_GameObj;
};