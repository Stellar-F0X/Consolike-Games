#pragma once
#include "Component.h"
#include "IContactable.h"
#include "Board.h"

class Entity : public Component, IContactable
{
public:
	Entity(string name, Vector2 position, Board* board) : Component(name, position), _board(board)
	{
		_board->RegistryContactable(this);
	}

public:
	void OnStart() {}
	void OnUpdate(float deltaTime) {}
	void OnDelete() {}
	void OnRender() {}
	void OnContact(Component* target) {}

	Vector2 GetPosition() override
	{
		return this->position;
	}

public :
	EDirection direction;

protected:
	Board* _board;
};