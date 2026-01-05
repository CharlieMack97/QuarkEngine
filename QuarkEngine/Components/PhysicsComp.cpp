#include "PhysicsComp.h"
#include "GameObject.h" 
#include "TransformComp.h"
PhysicsComp::PhysicsComp(b2WorldId world, TransformComp& transform, float width, float height)
{
    // Body definition
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = 
    {
        transform.x / PPM,
        transform.y / PPM
    };

    body = b2CreateBody(world, &bodyDef);

    // Box shape (half extents!)
    b2Polygon box = b2MakeBox(width * 0.5f, height * 0.5f);

    // Shape definition
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;


    // Attach shape to body
    b2CreatePolygonShape(body, &shapeDef, &box);
}

PhysicsComp::~PhysicsComp()
{


}
void PhysicsComp::Update(float dt)
{
    if (!gameObj) return;

    TransformComp* transform = gameObj->GetComponent<TransformComp>();
    if (transform)
    {
        SyncTransform(*transform);
    }
    if (!b2Body_IsValid(body))
    {
        return;
    }
    b2Vec2 vel = b2Body_GetLinearVelocity(body);
    //printf("P pos in transform: %f\n", transform->x);

}

void PhysicsComp::SyncTransform(TransformComp& transform) const
{
    b2Vec2 pos = b2Body_GetPosition(body);

    transform.x = pos.x * PPM;
    transform.y = pos.y + PPM;

    b2Rot rotation = b2Body_GetRotation(body);
    transform.rotation = atan2(rotation.c, rotation.s);

}

void PhysicsComp::SetLocation(int posX, int posY)
{
    TransformComp* trans = this->gameObj->GetComponent<TransformComp>();
    trans->x = posX;
    trans->y = posY;
    SyncTransform(*trans);
}
void PhysicsComp::SetVelocity(float vel, float velY)
{
    b2Vec2 velocity = { vel,velY };
    b2Body_ApplyForce(body, velocity, b2Body_GetWorldCenterOfMass(body), true);
}
void PhysicsComp::SetImpule(float impulseY)
{
    b2Vec2 velocity = { 0,impulseY };
    b2Body_ApplyLinearImpulse(body, velocity, b2Body_GetWorldCenterOfMass(body), true);
}