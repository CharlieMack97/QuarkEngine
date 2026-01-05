#pragma once
#include "Component.h"
#include "TransformComp.h"
#include <../Box2D/include/box2d/box2d.h>
class PhysicsComp : public Component
{
	
public:
	PhysicsComp(b2WorldId world, float x, float y, float width, float height);
	~PhysicsComp();
	b2BodyId GetBody() const { return body; }
	void SyncTransform(TransformComp& transform) const;

	float PPM = 100.0f;
private:
	b2BodyId body;
};
