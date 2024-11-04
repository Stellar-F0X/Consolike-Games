#pragma once
#include <vector>
#include "Component.h"

using namespace std;

class Game
{
public:
	void Play(int frameRate = 60);
	void Init();
	void Update(float deltaTime);
	void Render();
	void Exit();

	static Component* Find(string name);

public:
	Game();
	virtual ~Game();

private:
	int _lastTick;
	int _frameRate;
	float _updateInterval;

	static vector<Component*> _objects;
};