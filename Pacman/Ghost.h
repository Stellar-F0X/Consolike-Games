#pragma once
#include "Board.h"
#include "Entity.h"

class Ghost : public Entity
{
public:
	Ghost(string name, Vector2 position, Board* board) : Entity(name, position, board) { }

public:
	void OnStart() {}
	void OnUpdate(float deltaTime) {}
	void OnDelete() {}
	void OnRender() {}
};