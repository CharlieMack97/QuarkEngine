#include "GameObject.h"


void GameObj::Start()
{
	for (auto const& c : m_Comps)
	{
		c->Start();
	}
}

void GameObj::Update(float dt)
{
	for (auto const& c : m_Comps)
	{
		c->Update(dt);
	}
}

void GameObj::Render()
{
	for (auto const& c : m_Comps)
		c->Render();  // only renderer components will do something
}
