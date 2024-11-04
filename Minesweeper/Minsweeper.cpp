#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Board.h"
#include "Minsweeper.h"

using namespace std;


void Minsweeper::Initialize()
{
	m_GameOver = false;

	m_CursorPos.x = 3;
	m_CursorPos.y = 3;

	system("cls");
	srand(time(0));

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}





void Minsweeper::GotoCursor(const int x, const int y)
{
	COORD pos = { x,y };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(handle, pos);
}





bool Minsweeper::Start(const int x, const int y, const int mineCount)
{
	if (x * y <= mineCount) {

		printf("지뢰가 보드판의 칸 수 보다 많습니다.");
		return false;
	}

	if (x == 0 || y == 0) {

		printf("보드판의 칸 수는 0 보다 커야됩니다.");
		return false;
	}
	m_Board = new Board(x, y, mineCount);
	Minsweeper::Initialize();
	return true;
}



//현재 설정된 깃발 개수가 지뢰 수와 같고,
//남아 있는 Safety 칸이 없다면 끝난다.

bool Minsweeper::IsGameClear()
{
	int mineCnt = 0;
	int safetyCnt = 0;
	int existMineCnt = m_Board->GetMineCount();

	for (int col = 0; col < m_Board->GetHeight(); ++col) {
		for (int row = 0; row < m_Board->GetWidth(); ++row) {

			Cell* cell = m_Board->GetCell(row, col);

			switch (cell->GetCellType()) {

				case MINE:    if (cell->GetRevealType() == MARK)    ++mineCnt;
				case SAFETY:  if (cell->GetRevealType() == PRIVATE) ++safetyCnt;
			}

			if (safetyCnt == 0 && mineCnt == existMineCnt) return true;
		}
	}
	return false;
}





void Minsweeper::RangeLimit(const int key)
{
	int width = m_Board->GetWidth() - 1;
	int height = m_Board->GetHeight() - 1;

	switch (key) {

		case KEY_LEFT:  if (m_CursorPos.x - 1 >= 0)      --m_CursorPos.x; break;
		case KEY_RIGHT: if (m_CursorPos.x + 1 <= width)  ++m_CursorPos.x; break;
		case KEY_UP:    if (m_CursorPos.y - 1 >= 0)      --m_CursorPos.y; break;
		case KEY_DOWN:  if (m_CursorPos.y + 1 <= height) ++m_CursorPos.y; break;
	}
}





void Minsweeper::Input()
{
	if (_kbhit())
	{
		int inputKey = _getch();

		if (inputKey == KEY_ARROW) {

			inputKey = _getch();
			RangeLimit(inputKey);
		}
		else switch (inputKey) {

		case KEY_SPACE:
			SetMark(m_CursorPos.x, m_CursorPos.y);
			break;

		case KEY_ENTER:
			m_GameOver = (m_Board->SelectCell(m_CursorPos.x, m_CursorPos.y) == MINE);
			break;
		}
	}
}





void Minsweeper::DrawUI()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	int width = m_Board->GetWidth();
	int height = m_Board->GetHeight();

	for (int row = 1; row <= width; ++row) {

		int rowValue = row * 3 + 1;
		GotoCursor(rowValue, 0);		  printf("%2d ", row);
		GotoCursor(rowValue, 1);		  printf("---");
		GotoCursor(rowValue, height + 2); printf("---");
	}

	for (int col = 1; col <= height; ++col) {

		int colValue = col + 1;
		GotoCursor(0, colValue);			 printf("%2d ", col);
		GotoCursor(3, colValue);			 printf("|");
		GotoCursor(width * 3 + 4, colValue); printf("|");
	}

	GotoCursor(3, 1);					   putchar('+');
	GotoCursor(3, height + 2);			   putchar('+');
	GotoCursor(width * 3 + 4, 1);		   putchar('+');
	GotoCursor(width * 3 + 4, height + 2); putchar('+');
}





void Minsweeper::DrawCell(Cell* cell, const int x, const int y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (m_CursorPos.x == x && m_CursorPos.y == y) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	}

	if (!m_GameOver) switch (cell->GetRevealType())
	{
		case MARK: printf("[=]"); return;
		case PRIVATE: printf("[?]"); return;
		case PUBLIC: break;
	}

	switch (cell->GetCellType()) {

		case EMPTY:		printf("   "); break;
		case MINE:		printf("[M]"); break;
		case SAFETY:	printf(" %d ", cell->GetMineCount()); break;
	}
}





void Minsweeper::DrawBoard()
{
	int width = m_Board->GetWidth();
	int height = m_Board->GetHeight();

	for (int col = 0; col < height; ++col) {
		for (int row = 0; row < width; ++row) {

			Cell* cell = m_Board->GetCell(row, col);

			GotoCursor(row * 3 + 4, col + 2);
			DrawCell(cell, row, col);
		}
		putchar('\n');
	}
}





void Minsweeper::SetMark(const int x, const int y)
{
	Cell* cell = m_Board->GetCell(x, y);

	switch (cell->GetRevealType())
	{
		case MARK: cell->Select(PRIVATE);  break;
		case PRIVATE: cell->Select(MARK);  break;
	}
}





void Minsweeper::Run()
{
	while (true) {

		DrawUI();
		DrawBoard();

		Input();

		if (m_GameOver) {

			DrawBoard();
			GotoCursor(0, m_Board->GetHeight() + 3);
			printf("Game Over\n");
			break;
		}

		if (IsGameClear()) {

			DrawBoard();
			GotoCursor(0, m_Board->GetHeight() + 3);
			printf("Game Clear !\n");
			break;
		}
	}

	delete m_Board;
}