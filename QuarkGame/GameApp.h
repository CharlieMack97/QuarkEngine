#pragma once
#include "../QuarkEngine/Header/EngineApp.h"
#include <imgui.h>
#include <PathUtils.h>
class GameApp : public EngineApp
{
    struct Brick
    {
        GameObject* obj;
        bool alive = true;
    };
public:
    GameObject* paddle = nullptr;
    GameObject* ball = nullptr;
    std::vector<Brick> bricks;

    float ballVelX = 250.f;
    float ballVelY = -250.f;
    float paddleSpeed = 400.f;

    
    int screenW = 1600;
    int screenH = 900;

    int score = 0;
    bool gameOver = false;
    bool gameWon = false;

    float Left(TransformComp* t) { return t->x - t->scaleX / 2.f; }
    float Right(TransformComp* t) { return t->x + t->scaleX / 2.f; }
    float Top(TransformComp* t) { return t->y - t->scaleY / 2.f; }
    float Bottom(TransformComp* t) { return t->y + t->scaleY / 2.f; }

    void OnStart() override
    {
        TextureManager* tex = engine->getTextureManager();
        tex->loadTexture(AssetPath("pngTest.jpg").c_str());
        tex->loadTexture(AssetPath("Lava.png").c_str());
        tex->loadTexture(AssetPath("brick.jpg").c_str());

        //paddle
        paddle = new GameObject();
        TransformComp* paddleTrans = paddle->AddComponent<TransformComp>();
        paddleTrans->x = screenW / 2.f;
        paddleTrans->y = screenH - 60.f - paddleTrans->scaleY / 2.f;
        paddleTrans->scaleX = 100.f;
        paddleTrans->scaleY = 20.f;
        paddleTrans->rotation = 0;
        RendererComp* ppaddleRend = paddle->AddComponent<RendererComp>(tex);
        ppaddleRend->setTexture(AssetPath("pngTest.jpg").c_str());
        paddle->Start();

        //ball
        ball = new GameObject();
        TransformComp* ballTrans = ball->AddComponent<TransformComp>();
        ballTrans->x = screenW / 2.f;
        ballTrans->y = screenH - 100.f;
        ballTrans->scaleX = 20.f;
        ballTrans->scaleY = 20.f;
        ballTrans->rotation = 0;
        RendererComp* ballRend = ball->AddComponent<RendererComp>(tex);
        ballRend->setTexture(AssetPath("Lava.png").c_str());
        ball->Start();

        //8x4 bricks
        const int cols = 8;
        const int rows = 4;
        const float padding = 10.f;
        const float startY = 40.f;

        
        const float totalPaddingX = padding * (cols + 1);
        const float brickW = (screenW - totalPaddingX) / cols;
        const float brickH = 30.f;

        uint32_t rowColors[rows] = {
            0xff0000ff, //red    
            0xff0080ff, //orange
            0xff00ffff, //yellow
            0xff00ff00, //green
        };
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                GameObject* brickObj = new GameObject();
                TransformComp* t = brickObj->AddComponent<TransformComp>();
                float topLeftX = padding + col * (brickW + padding);
                float topLeftY = startY + row * (brickH + padding);
                t->x = topLeftX + brickW / 2.f;
                t->y = topLeftY + brickH / 2.f;
                t->scaleX = brickW;
                t->scaleY = brickH;
                t->rotation = 0;
                RendererComp* r = brickObj->AddComponent<RendererComp>(tex);
                r->setTexture(AssetPath("brick.jpg").c_str());
                
                brickObj->Start();
                r->SetColor(rowColors[row]);
                bricks.push_back({ brickObj, true });
            }
        }
    }

	//AABB collision detection
    bool Overlaps(TransformComp* a, TransformComp* b)
    {
        return Left(a) < Right(b) &&
            Right(a) > Left(b) &&
            Top(a) < Bottom(b) &&
            Bottom(a) > Top(b);
    }

    void OnUpdate(float dt) override
    {
        if (gameOver || gameWon)
            return;

        //paddle
        const bool* keys = SDL_GetKeyboardState(nullptr);
        TransformComp* paddleTrans = paddle->GetComponent<TransformComp>();
        if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
            paddleTrans->x -= paddleSpeed * dt;
        if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
            paddleTrans->x += paddleSpeed * dt;

        if (Left(paddleTrans) < 0) paddleTrans->x = paddleTrans->scaleX / 2.f;
        if (Right(paddleTrans) > screenW) paddleTrans->x = screenW - paddleTrans->scaleX / 2.f;

		//ball movement
        TransformComp* ballTrans = ball->GetComponent<TransformComp>();
        ballTrans->x += ballVelX * dt;
        ballTrans->y += ballVelY * dt;

        // wall bounce
        if (Left(ballTrans) <= 0) { ballTrans->x = ballTrans->scaleX / 2.f; ballVelX = -ballVelX; }
        if (Right(ballTrans) >= screenW) { ballTrans->x = screenW - ballTrans->scaleX / 2.f; ballVelX = -ballVelX; }
        if (Top(ballTrans) <= 0) { ballTrans->y = ballTrans->scaleY / 2.f; ballVelY = -ballVelY; }

        // fell off bottom -> lose
        if (ballTrans->y > screenH)
        {
            gameOver = true;
            return;
        }

        // paddle bounce
        if (Overlaps(ballTrans, paddleTrans) && ballVelY > 0)
        {
            ballVelY = -ballVelY;
            float paddleCenter = paddleTrans->x + paddleTrans->scaleX * 0.5f;
            float ballCenter = ballTrans->x + ballTrans->scaleX * 0.5f;
            float offset = (ballCenter - paddleCenter) / (paddleTrans->scaleX * 0.5f); // -1..1
            ballVelX = offset * 300.f;
        }
        bool anyAlive = false;
        for (auto& brick : bricks)
        {
            if (!brick.alive) continue;
            anyAlive = true;

            TransformComp* brickTrans = brick.obj->GetComponent<TransformComp>();
            if (Overlaps(ballTrans, brickTrans))
            {
                brick.alive = false;
                score += 10;

                float overlapLeft = (ballTrans->x + ballTrans->scaleX) - brickTrans->x;
                float overlapRight = (brickTrans->x + brickTrans->scaleX) - ballTrans->x;
                float overlapTop = (ballTrans->y + ballTrans->scaleY) - brickTrans->y;
                float overlapBottom = (brickTrans->y + brickTrans->scaleY) - ballTrans->y;

                float minOverlapX = std::min(overlapLeft, overlapRight);
                float minOverlapY = std::min(overlapTop, overlapBottom);

                if (minOverlapX < minOverlapY)
                {
                    ballVelX = -ballVelX;
                }
                else 
                {
                    ballVelY = -ballVelY;
                }
                    

                break;
            }
        }

        if (!anyAlive)
            gameWon = true;
    }
    void Restart()
    {
        //reset ball
        TransformComp* ballTrans = ball->GetComponent<TransformComp>();
        ballTrans->x = screenW / 2.f;
        ballTrans->y = screenH - 100.f;
        ballVelX = 250.f;
        ballVelY = -250.f;

        //reset paddle
        TransformComp* paddleTrans = paddle->GetComponent<TransformComp>();
        paddleTrans->x = screenW / 2.f;
        paddleTrans->y = screenH - 60.f - paddleTrans->scaleY / 2.f;

        //revive all bricks
        for (auto& brick : bricks)
            brick.alive = true;

        score = 0;
        gameOver = false;
        gameWon = false;
    }
    void OnImGuiRender() override
    {
        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_AlwaysAutoResize;


        ImGui::SetNextWindowPos(ImVec2(20, 850), ImGuiCond_Always, ImVec2(0.0f, 1.0f));
        ImGui::Begin("Brick Breaker", nullptr, flags);
        ImGui::SetWindowFontScale(2.f);
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Score: %d", score);

        if (gameOver)
        {
            ImGui::SetWindowFontScale(2.0f);
            ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "GAME OVER");
        }
        if (gameWon)
        {
            ImGui::SetWindowFontScale(2.0f);
            ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "YOU WIN!");
        }

        if (gameOver || gameWon)
        {
            ImGui::SetWindowFontScale(1.0f);
            if (ImGui::Button("Restart"))
                Restart();
        }

        ImGui::SetWindowFontScale(1.0f);
        ImGui::End();
    }

    void OnRender() override
    {
        paddle->Render();
        ball->Render();
        for (auto& brick : bricks)
        {
            if (brick.alive)
                brick.obj->Render();
        }
    }
};



