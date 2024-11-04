#include "Game.h"
#include "Console.h"
#include "Board.h"
#include "Ghost.h"
#include "Pacman.h"

vector<Component*> Game::_objects;


void Game::Play(int frameRate)
{
	this->Init();

	_frameRate = frameRate;
	_updateInterval = 1 / static_cast<double>(frameRate);

	while (true)
	{
		int currentTick = GetTickCount64();
		float deltaTime = (currentTick - _lastTick) * 0.001f;

		if (_updateInterval < deltaTime)
		{
			_lastTick = currentTick;

			this->Update(deltaTime);
			this->Render();
		}
	}

	this->Exit();
}


void Game::Init()
{
	Console::ScreenInitialization();
	Console::ScreenClear(WIDTH, HEIGHT);

	Board* board = new Board("board");

	_objects.push_back(board);
	_objects.push_back(new Pacman("pacman", { 1,1 },   board));
	_objects.push_back(new Ghost("ghost1",  { 12,15 }, board));
	_objects.push_back(new Ghost("ghost2",  { 13,15 }, board));
	_objects.push_back(new Ghost("ghost3",  { 14,15 }, board));
	_objects.push_back(new Ghost("ghost4",  { 15,15 }, board));

	for (auto& object : _objects)
	{
		object->OnStart();
	}
}


void Game::Update(float deltaTime)
{
	for (auto& object : _objects)
	{
		if (object->enable)
		{
			object->OnUpdate(deltaTime);
		}
	}
}


void Game::Render()
{
	for (auto& object : _objects)
	{
		if (object->render && object->enable)
		{
			object->OnRender();
		}
	}

	Console::ScreenFlipping();
}


void Game::Exit()
{

}


Component* Game::Find(string name)
{
	for (auto& object : _objects)
	{
		if (object->enable && object->name == name)
		{
			return object;
		}
	}

	return nullptr;
}


Game::Game()
{

}


Game::~Game()
{
	for (auto& object : _objects)
	{
		if (object == nullptr)
		{
			continue;
		}

		delete object;
		object = nullptr;
	}
}