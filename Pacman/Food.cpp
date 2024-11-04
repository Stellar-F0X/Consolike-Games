#include "Food.h"

#include "Console.h"

void Food::OnRender()
{
	Console::ScreenPrint(position.x, position.y, "ㆍ");
}

void Food::OnContact(Component* target)
{

}