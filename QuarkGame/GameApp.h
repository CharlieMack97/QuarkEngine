#pragma once
#include "../QuarkEngine/Header/EngineApp.h"
class GameApp : public EngineApp
{
public:
    std::vector<GameObject*> gameObjects;

    void OnStart() override
    {
        std::cout << "Working dir: " << SDL_GetBasePath() << std::endl;
        TextureManager* tex = engine->getTextureManager();
        //tex->loadTexture("../../../../QuarkGame/assets/pngTest.jpg");
        //tex->loadTexture("../../../../QuarkGame/assets/Lava.png");
        tex->loadTexture("assets/pngTest.jpg");
        tex->loadTexture("assets/Lava.png");
        // Create game objects, load assets, etc.
        GameObject* gameObj;
        GameObject* gameObj2;
        //testing obj
        gameObj2 = new GameObject();
        gameObj = new GameObject();
        TransformComp* transform = gameObj->AddComponent<TransformComp>();
        transform->x = 100;
        transform->y = 100;
        transform->scaleX = 100.f;
        transform->scaleY = 100.f;
        transform->rotation = 0;
        RendererComp* renderComp = gameObj->AddComponent<RendererComp>(engine->getTextureManager());
        PhysicsComp* phys = gameObj->AddComponent<PhysicsComp>(engine->getWorldId(),*transform,1,1);
        //renderComp->setTexture("../../../../QuarkGame/assets/pngTest.jpg");
        renderComp->setTexture("assets/pngTest.jpg");
        
        TransformComp* transform2 = gameObj2->AddComponent<TransformComp>();
        transform2->x = 800;
        transform2->y = 900;
        transform2->scaleX = 100.f;
        transform2->scaleY = 100.f;
        transform2->rotation = 0;
        RendererComp* lava = gameObj2->AddComponent<RendererComp>(engine->getTextureManager());
        PhysicsComp* physic2 = gameObj2->AddComponent<PhysicsComp>(engine->getWorldId(), *transform, 1, 1);
        //lava->setTexture("../../../../QuarkGame/assets/Lava.png");
        lava->setTexture("assets/Lava.png");
       
        
        gameObjects.push_back(gameObj);
        gameObjects.push_back(gameObj2);
        for (GameObject* object : gameObjects)
        {
    	    object->Start();
        }
    }

    void OnUpdate(float dt) override
    {
        // Game logic
        if (engine->getMouseInput().IsDown(SDL_BUTTON_LEFT))
        {
            PhysicsComp* phys = gameObjects[0]->GetComponent<PhysicsComp>();
            phys->SetVelocity(-15.f, -10.f);
        }
        if (engine->getMouseInput().IsDown(SDL_BUTTON_RIGHT))
        {
            PhysicsComp* phys = gameObjects[0]->GetComponent<PhysicsComp>();
            phys->SetVelocity(15.f, -10.f);
        }
        if (engine->getMouseInput().IsDown(SDL_BUTTON_MIDDLE))
        {
            PhysicsComp* phys = gameObjects[0]->GetComponent<PhysicsComp>();
            phys->SetImpule(-50.f);
        }
        TransformComp* trans2 = gameObjects[1]->GetComponent<TransformComp>();
        
        
        TransformComp* transform = gameObjects[0]->GetComponent<TransformComp>();

        

        b2Vec2 direction = { (transform->x - trans2->x),(transform->x - trans2->x)};

        PhysicsComp* phsicsLava = gameObjects[1]->GetComponent<PhysicsComp>();

        phsicsLava->SetVelocity(direction.x/250, direction.y/250);

        for (GameObject* object : gameObjects)
        {
            
            PhysicsComp* phys = object->GetComponent<PhysicsComp>();
            TransformComp* trans = object->GetComponent<TransformComp>();

            if (phys && trans)
            {
                phys->SyncTransform(*trans);
            }
            object->Update(dt);
        }
    }

    void OnRender() override
    {
        // Draw your game objects
        for (GameObject* object : gameObjects)
        {
            object->Render();
        }
    }
};


