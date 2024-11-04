#pragma once
#include <map>
#include "Struct.h"

using namespace std;

class Layer
{
public:
	void AddTile(Vector2 position, char* sprite);
	void RemoveTile(Vector2 removePos);
	void OnRender();

protected:
	map<Vector2, char*> _tileInfo;
};