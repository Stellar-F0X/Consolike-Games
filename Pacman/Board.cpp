#include <cassert>
#include "Board.h"
#include "Console.h"
#include "Food.h"


void Board::OnStart()
{

}


void Board::OnUpdate(float deltaTime)
{
	if (_checkCollisions)
	{
		this->CheckContactBetweenEntities();
	}
}


void Board::OnDelete()
{

}


void Board::SetTile(const int x, const int y, const EBoardTile tile)
{
	assert(this->IsValidRange(x, y), "{SetTile} 범위 초과");

	_boardMold[y][x] = tile;
}


void Board::RegistryContactable(IContactable* contactable)
{
	_contactables.push_back(contactable);
}


bool Board::IsValidRange(int x, int y) const
{
	bool validXRange = x >= 0 && WIDTH > x;
	bool validYRange = y >= 0 && HEIGHT > y;

	return validXRange && validYRange;
}


Board::~Board()
{
	for (auto& contactable : _contactables)
	{
		if (contactable == nullptr)
		{
			continue;
		}

		delete contactable;
		contactable = nullptr;
	}
}


EBoardTile Board::GetTile(int x, int y) const
{
	if (this->IsValidRange(x, y))
	{
		return _boardMold[y][x];
	}

	return NONE;
}


EBoardTile Board::GetTile(Vector2 position) const
{
	return this->GetTile(position.x, position.y);
}


void Board::OnRender()
{
	for (int col = 0; col < HEIGHT; ++col) {
		for (int row = 0; row < WIDTH; ++row) {

			switch (_boardMold[col][row])
			{
				case E:  Console::ScreenPrint(row, col, "  "); break;
				case F:  Console::ScreenPrint(row, col, "ㆍ"); break;
				case W1: Console::ScreenPrint(row, col, "┃");  break;
				case W2: Console::ScreenPrint(row, col, "━");  break;
				case C1: Console::ScreenPrint(row, col, "┏");  break;
				case C2: Console::ScreenPrint(row, col, "┓");  break;
				case C3: Console::ScreenPrint(row, col, "┛");  break;
				case C4: Console::ScreenPrint(row, col, "┗");  break;
			}
		}
	}
}


void Board::CheckContactBetweenEntities() const
{
	int size = _contactables.size();

	for (int col = 0; col < size - 1; ++col) {
		for (int row = col + 1; row < size; ++row) {

			if (!_contactables[col]->canCollision || !_contactables[row]->canCollision)
			{
				continue;
			}

			Vector2 pointA = _contactables[col]->GetPosition();
			Vector2 pointB = _contactables[row]->GetPosition();

			if (pointA.x == pointB.x && pointA.y == pointB.y)
			{
				_contactables[col]->OnContact(reinterpret_cast<Component*>(_contactables[row]));
				_contactables[row]->OnContact(reinterpret_cast<Component*>(_contactables[col]));
			}
		}
	}
}


void Board::CheckContactFoods() const
{
	
}


bool Board::CanMove(Vector2 position)
{
	return false;
}