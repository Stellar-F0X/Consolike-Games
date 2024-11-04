#pragma once
#include "Board.h"
#include "Entity.h"


class Pacman : public Entity
{
private:
	void Move();
	void Rotate();
	void Input();

public:
	void OnStart();
	void OnUpdate(float deltaTime);
	void OnDelete();
	void OnRender();

public:
	Pacman(string name, Vector2 position, Board* board) : Entity(name, position, board) { }

private:
	float _moveSpeed = 0.4f;
	bool _canRotationInThisFrame;

	string _currentShape;
	string _rotationShapes[4];
	Vector2 _nextPosition = NULL;
	Vector2 _moveDirection = NULL;
};