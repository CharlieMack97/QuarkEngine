#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Component.h"
#include "RendererComp.h"
#include "TransformComp.h"

class GameObject
{
public:
	
	void Start();
	void Update(float dt);
	void Render();
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		auto comp = std::make_unique<T>(std::forward<Args>(args)...);
		comp->setOwner(this);
		T* ptr = comp.get();
		m_Comps.push_back(std::move(comp));
		return ptr;
	}

	template<typename T>
	T* GetComponent()
	{
		for (auto& c : m_Comps)
			if (auto casted = dynamic_cast<T*>(c.get()))
				return casted;
		return nullptr;
	}
private:
	std::vector<std::unique_ptr<Component>> m_Comps;
};