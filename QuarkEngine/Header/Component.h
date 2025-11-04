#pragma once
#include <cstdint>
class GameObject;
class Component
{
public:
	GameObject* gameObj = nullptr;
	Component() : gameObj(nullptr) {}
	Component(GameObject* object) : gameObj{ object } {}
	virtual ~Component() {}
	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Render(uint32_t screenWidth, uint32_t screenHeight) {}
	void setOwner(GameObject* owner) { gameObj = owner; }
private:
};