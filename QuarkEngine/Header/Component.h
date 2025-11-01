#pragma once
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
	virtual void Render() {}
	void setOwner(GameObject* owner) { gameObj = owner; }
private:
};