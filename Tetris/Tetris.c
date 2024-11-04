#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define KEY_UP	  72
#define KEY_DOWN  80
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_ARROW 224

#define GAME_SPEED 150

#define BOARD_HEIGHT 24
#define BOARD_WIDTH	 12
#define BOARD_OFFSET 4


typedef struct __brick {
	int block;		 //블럭 바이너리
	int type;		 //종류
	int rotation;	 //회전량
	POINT pos;		 //위치
} BRICK;

const char blockName[7] = {
	'I', 'T', 'O', 'L', 'J', 'Z', 'S'
};

const int tableMold[BOARD_HEIGHT] = {
	0x801, 0x801, 0x801, 0x801, 0x801, 0x801,
	0x801, 0x801, 0x801, 0x801, 0x801, 0x801,
	0x801, 0x801, 0x801, 0x801, 0x801, 0x801,
	0x801, 0x801, 0x801, 0x801, 0x801, 0xfff
};

const int bricks[7][4] = {
	{ 0x8888, 0xf0,  0x8888, 0xf0  }, //I 0
	{ 0xe4,   0x4c4, 0x4e0,  0x464 }, //T 1
	{ 0xcc,   0xcc,  0xcc,   0xcc, }, //O 2
	{ 0x88c,  0xe80, 0xc44,  0x2e0 }, //L 3 
	{ 0x44c,  0x8e0, 0xc88,  0xe20 }, //J 4
	{ 0xc6,   0x4c8, 0xc6,   0x4c8 }, //Z 5
	{ 0x6c,   0x8c4, 0x6c,   0x8c4 }  //S 6
};

const POINT spawnPoint = { 5, 0 };

int table[BOARD_HEIGHT];

int score = 0;
int gameOver = FALSE;
int inputable = TRUE;
DWORD gameSpeed = GAME_SPEED;
HANDLE cHandle;

BRICK currBrick; //현재 벽돌
BRICK nextBrick; //다음 벽돌


BRICK CreateBrick(int t)
{
	return (BRICK) { bricks[t][0], t, 0, spawnPoint };
}

void SetCursorPosition(int x, int y)
{
	SetConsoleCursorPosition(cHandle, (COORD) { x * 2, y });
}

void Setup()
{
	CONSOLE_CURSOR_INFO cInfo;
	cInfo.bVisible = FALSE;
	cInfo.dwSize = 1;

	cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(cHandle, &cInfo);
	srand(time(0));

	currBrick = CreateBrick(rand() % 7);
	nextBrick = CreateBrick(rand() % 7);

	memcpy(table, tableMold, sizeof(tableMold));
}

void Draw()
{
	for (int col = BOARD_OFFSET; col < BOARD_HEIGHT; ++col) {
		for (int row = 0; row < BOARD_WIDTH; ++row) {
			SetCursorPosition(row, col - BOARD_OFFSET);
			printf(table[col] & (0x800 >> row) ? "■" : "  ");
		}
	}

	for (int col = 0; col < 4; ++col) {
		int brick4Bit = (currBrick.block >> 4 * (3 - col)) & 0xf;

		for (int row = 0; row < 4; ++row) {
			int x = currBrick.pos.x + row;
			int y = currBrick.pos.y + col - BOARD_OFFSET;

			if (y >= 0)
			{
				SetCursorPosition(x, y);
				printf(brick4Bit & (0x8 >> row) ? "□" : "");
			}
		}
	}

	SetCursorPosition(13, 2); printf("next  : %c", blockName[nextBrick.type]);
	SetCursorPosition(13, 4); printf("score : %d", score);
}

int TryRotate()
{
	int tempBlock = bricks[currBrick.type][(currBrick.rotation + 1) % 4];
	int canRotate = CheckPlace(currBrick.pos.x, currBrick.pos.y, tempBlock);

	return (canRotate ? (currBrick.rotation + 1) % 4 : currBrick.rotation);
}

POINT Input()
{
	if (_kbhit() && inputable == TRUE)
	{
		int inputKey = _getch();
		POINT moveVector = (POINT){ 0, 0 };

		if (inputKey == KEY_ARROW)
		{
			switch (_getch())
			{
			case KEY_LEFT:	 moveVector.x--; break;
			case KEY_RIGHT:  moveVector.x++; break;
			case KEY_DOWN:	 moveVector.y++; break;
			case KEY_UP:	 currBrick.rotation = TryRotate(); break;
			}
			return moveVector;
		}
		else if (inputKey == KEY_SPACE)
		{
			gameSpeed = 1;
			inputable = FALSE;
		}
	}
	return (POINT) { 0, 0 };
}

void ClearLine()
{
	int tempTable[BOARD_HEIGHT];
	int tempTableCount = BOARD_HEIGHT - 2;

	memcpy(tempTable, tableMold, sizeof(tableMold));

	for (int i = BOARD_HEIGHT - 2; i > BOARD_OFFSET; --i) {

		if (table[i] == 0xfff) continue;
		tempTable[tempTableCount--] = table[i];
	}
	memcpy(table, tempTable, sizeof(tempTable));
}

int CheckPlace(const int x, const int y, const int block)
{
	for (int i = 0; i < 4; ++i) {
		int brick4Bit = (block >> 4 * (3 - i)) & 0xf;
		brick4Bit = (brick4Bit << 8) >> x;

		if (table[y + i] & brick4Bit) return FALSE;
	}
	return TRUE;
}

void Logic()
{
	POINT inputPoint = Input();
	POINT mP = (POINT){ //move Point
		currBrick.pos.x + inputPoint.x,
		currBrick.pos.y + inputPoint.y
	};

	currBrick.pos = (CheckPlace(mP.x, mP.y, currBrick.block) ? mP : currBrick.pos);
	currBrick.block = bricks[currBrick.type][currBrick.rotation];

	if (CheckPlace(currBrick.pos.x, currBrick.pos.y + 1, currBrick.block))
	{
		currBrick.pos.y++;
	}
	else
	{
		int clearLineNums = 0;

		for (int i = 0; i < 4; ++i) {
			if (currBrick.pos.y + i + 1 == BOARD_HEIGHT) break;
			int brick4Bit = (currBrick.block >> 4 * (3 - i)) & 0xf;
			table[currBrick.pos.y + i] |= ((brick4Bit << 8) >> currBrick.pos.x);
			clearLineNums += (table[currBrick.pos.y + i] == 0xfff ? 1 : 0);
		}
		if (clearLineNums > 0)
		{
			ClearLine();
			score += clearLineNums * 1000;
		}
		currBrick = nextBrick;
		nextBrick = CreateBrick(rand() % 7);

		inputable = TRUE;
		gameSpeed = GAME_SPEED;
		gameOver = table[spawnPoint.y + BOARD_OFFSET] & 0x7FE;
	}
}

int main()
{
	Setup();

	while (!gameOver)
	{
		Sleep(gameSpeed);
		Logic();
		Draw();
	}
	system("cls");
	printf("score : %d\n", score);
	CloseHandle(cHandle);
}