#include <conio.h>
#include "Pacman.h"
#include "Constant.h"
#include "Console.h"
#include "Component.h"


void Pacman::OnStart()
{
	_rotationShapes[UP]    = "¨Ü";
	_rotationShapes[RIGHT] = "¨Ü";
	_rotationShapes[DOWN]  = "¨Ü";
	_rotationShapes[LEFT]  = "¨Ü";
}


void Pacman::OnUpdate(float deltaTime)
{
	this->Input();
	this->Move();
	this->Rotate();
}


void Pacman::OnDelete()
{

}


void Pacman::OnRender()
{
	if (_currentShape.empty())
	{
		return;
	}

	Console::ScreenPrint(position.x, position.y, _currentShape.c_str());
}


void Pacman::Move()
{
	Vector2 nextPosition = this->position + _moveDirection * _moveSpeed;
	EBoardTile tile      = _board->GetTile(nextPosition);

	if (tile == EBoardTile::F || tile == EBoardTile::E)
	{
		this->position = nextPosition;
	}
	else
	{
		_canRotationInThisFrame = false;
	}
}


void Pacman::Rotate()
{
	if (_canRotationInThisFrame)
	{
		_currentShape = _rotationShapes[direction];
	}
	else
	{
		_canRotationInThisFrame = true;
	}
}


void Pacman::Input()
{
	if (_kbhit() && _getch() == EDirection::ARROW)
	{
		switch (_getch())
		{
			case 72:
				direction = EDirection::UP;
				_moveDirection.Set(0, -1);
				break;

			case 80:
				direction = EDirection::DOWN;
				_moveDirection.Set(0, 1);
				break;

			case 75:
				direction = EDirection::LEFT;
				_moveDirection.Set(-1, 0);
				break;

			case 77:
				direction = EDirection::RIGHT;
				_moveDirection.Set(1, 0);
				break;
		}
	}
}
