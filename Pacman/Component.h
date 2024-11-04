#pragma once
#include <string>
#include "Struct.h"

using namespace std;

class Component
{
public:
	virtual void OnStart() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnDelete() = 0;
	virtual void OnRender() = 0;

public:
	string GetName()
	{
		return name;
	}

	void SetName(string name)
	{
		this->name = name;
	}

	Vector2 GetPosition()
	{
		return this->position;
	}

	void SetPosition(Vector2 position)
	{
		this->position = position;
	}

public:
	Component(string name, Vector2 position)
	{
		this->name = name;
		this->position = position;
	}

public :
	string name;
	Vector2 position;
	bool render = true;
	bool enable = true;
};