#pragma once
#include "Component.h"

class IContactable
{
public:
	virtual Vector2 GetPosition() = 0;

	virtual void OnContact(Component* target) = 0;

public:
	bool canCollision = true;
};

