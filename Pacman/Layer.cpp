#include "Console.h"
#include "Layer.h"

void Layer::AddTile(Vector2 position, char* sprite)
{
	_tileInfo.insert(make_pair(position, sprite));
}


void Layer::RemoveTile(Vector2 removePos)
{
	if (_tileInfo.find(removePos) != _tileInfo.end()) 
	{
		_tileInfo.erase(removePos);
	}
}


void Layer::OnRender()
{
	for (const auto & tile_info : _tileInfo)
	{
		Vector2 pos = tile_info.first;
		char* sprite = tile_info.second;

		Console::ScreenPrint(pos.x, pos.y, sprite);
	}
}