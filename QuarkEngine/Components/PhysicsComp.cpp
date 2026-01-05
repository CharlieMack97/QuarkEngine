#include "PhysicsComp.h"

PhysicsComp::PhysicsComp(b2WorldId world, float x, float y, float width, float height)
{
    // Body definition
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { x, y };

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

void PhysicsComp::SyncTransform(TransformComp& transform) const
{
    b2Vec2 pos = b2Body_GetPosition(body);

    transform.x = pos.x * PPM;
    transform.y = pos.y * PPM;

    b2Rot rotation = b2Body_GetRotation(body);
    transform.rotation = atan2(rotation.c, rotation.s);

}
