#pragma once
#include "Component.h"
#include "IContactable.h"

class Food : public Component, IContactable
{
public:
	Food(string name, Vector2 position) : Component(name, position)
	{
		
	}

public:
	void OnStart() {}
	void OnDelete() {}
	void OnUpdate(float deltaTime) {}
	void OnRender();
	void OnContact(Component* target);

	Vector2 GetPosition() override
	{
		return this->position;
	}
};
