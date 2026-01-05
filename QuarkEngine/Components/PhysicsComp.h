#pragma once
#include "Component.h"
#include "TransformComp.h"
#include <../Box2D/include/box2d/box2d.h>
class PhysicsComp : public Component
{
	
public:
	PhysicsComp(b2WorldId world, TransformComp& transform, float width, float height);
	~PhysicsComp();
	void Update(float dt) override;
	b2BodyId GetBody() const { return body; }
	void SyncTransform(TransformComp& transform) const;
	void SetLocation(int posX, int posY);
	void SetVelocity(float velX, float velY);
	void SetImpule(float impulseY);
	float PPM = 100.0f;
private:
	b2BodyId body;
};
