#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define MAPSIZE 30
#define HEAD 0
#define UP 72 
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77 

enum eTILETYPE { EMPTY, WALL, FOOD, SNAKE };

typedef struct __point
{
	int x, y;
} Point;

int tailSize = 3;
int headDir = UP;
int keyMap[] = { UP, LEFT, DOWN, RIGHT };
Point snake[899];

const int width = 30;
const int height = 30;

Point foodLoco;
int foodCount = 0;

int score = 0;
int gameover = 0;

HANDLE hScreen[2];
int screenIndex;
int board[MAPSIZE][MAPSIZE] = { 0 };


void ScreenPrint(int y, int x, char* s)
{
	SetConsoleCursorPosition(hScreen[screenIndex], (COORD) { x, y });
	WriteFile(hScreen[screenIndex], s, strlen(s), NULL, NULL);
}

void Setup()
{
	hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ |
		GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ |
		GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CONSOLE_CURSOR_INFO cInfo;
	cInfo.dwSize = 1;
	cInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hScreen[0], &cInfo);
	SetConsoleCursorInfo(hScreen[1], &cInfo);
	srand(time(NULL));

	for (int i = 0; i < MAPSIZE; ++i) {
		board[0][i] = board[MAPSIZE - 1][i] = WALL; //양 옆 새로 벽
		board[i][0] = board[i][MAPSIZE - 1] = WALL; //위 아래 가로 벽
	}

	snake[HEAD] =	  (Point){ 15, 15 };
	snake[HEAD + 1] = (Point){ 15, 16 };

	foodLoco = (Point) { 
		(rand() % (width - 2)) + 1,
		(rand() % (height - 2)) + 1 
	};
	board[foodLoco.y][foodLoco.x] = FOOD;
}

void Print()
{
	for (int col = 0; col < MAPSIZE; ++col) {
		for (int row = 0; row < MAPSIZE; ++row) {
			switch (board[col][row]) {
				case WALL:	ScreenPrint(col, row * 2, "■");  break;
				case FOOD:	ScreenPrint(col, row * 2, "◎"); break;
				case EMPTY:	ScreenPrint(col, row * 2, "  "); break;
			}
		}
	}
	for (int i = 0; i < tailSize; ++i) {
		ScreenPrint(snake[i].y, snake[i].x * 2, "□");
	}
	SetConsoleActiveScreenBuffer(hScreen[screenIndex]);
	screenIndex = !screenIndex;
}

void Input()
{
	if (_kbhit() && _getch() == 224) 
	{
		int key = _getch(), opposeDir = key + headDir;
		if (opposeDir == UP + DOWN || opposeDir == LEFT + RIGHT) 
		{
			return;
		}
		headDir = key;
	}
}

void Logic()
{
	for (int i = tailSize; i > 0; --i)
	{
		snake[i] = snake[i - 1];
	}
	switch (headDir)
	{
		case UP:	snake[HEAD].y--; break;
		case DOWN:	snake[HEAD].y++; break;
		case LEFT:	snake[HEAD].x--; break;
		case RIGHT: snake[HEAD].x++; break;
	}

	Point t = { snake[HEAD].x, snake[HEAD].y };
	for (int i = 1; i <= tailSize; ++i)
	{
		if (t.x == snake[i].x && t.y == snake[i].y)
		{
			gameover = 1;
			return;
		}
	}
	if (board[t.y][t.x] == WALL)
	{
		gameover = 1;
	}
	else if (board[t.y][t.x] == FOOD)
	{
		snake[tailSize + 1] = snake[tailSize++];
		board[foodLoco.y][foodLoco.x] = EMPTY;
		foodLoco = (Point){
			(rand() % (width - 2)) + 1,
			(rand() % (height - 2)) + 1
		};
		board[foodLoco.y][foodLoco.x] = FOOD;
		score++;
	}
}

int main()
{
	Setup();
	while (!gameover)
	{
		Sleep(20);
		Input();
		Logic();
		Print();
	}

	printf("Score : %d", score * 100);
	CloseHandle(hScreen[0]);
	CloseHandle(hScreen[1]);
}
