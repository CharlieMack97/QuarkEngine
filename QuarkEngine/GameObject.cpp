#include "GameObject.h"


void GameObject::Start()
{
	for (auto const& c : m_Comps)
	{
		c->Start();
	}
}

void GameObject::Update(float dt)
{
	for (auto const& c : m_Comps)
	{
		c->Update(dt);
	}
}

void GameObject::Render()
{
	for (auto const& c : m_Comps)
		c->Render();  // only renderer components will do something
}
