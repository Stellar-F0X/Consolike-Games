#pragma once
#include "Board.h"

#define KEY_LEFT	75
#define KEY_RIGHT	77
#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_SPACE   32
#define KEY_ENTER   13
#define KEY_ARROW   224

class Minsweeper 
{
	bool m_GameOver;		//플레이어가 지뢰를 눌렀을때만, 게임 종료 여부를 저장하는 변수.

	Board* m_Board;			//맵과 맵 관련 기능이 있는 변수.
	Position m_CursorPos;	//콘솔 커서 위치를 저장하는 변수.

public :
	//메모리에 올라온 게임을 실행 하는 함수.
	void Run();	

	//맵 생성 가능 여부와 초기화 등을 맡는 함수.
	bool Start(const int x, const int y, const int mineCount);

private :	
	//키보드 입력을 담당하는 함수
	void Input();

	//여러 변수나 설정 등을 초기화하는 함수
	void Initialize();

	//게임 클리어 조건을 확인하고 bool로 반환하는 함수.
	bool IsGameClear();

	//지뢰 맵 테두리를 그리는 함수.
	void DrawUI();

	//게임 칸을 그리는 DrawCell 함수를 호출하고 위치를 보정하는 함수.
	void DrawBoard();

	//칸을 호출 하고, 커서를 표현하는 함수.
	void DrawCell(Cell* cell, const int x, const int y);

	//배열 범위를 초과했는지 확인 하는 함수.
	void RangeLimit(const int key);

	//Space bar를 눌러서 지뢰 의심 칸을 마크하는 함수.
	void SetMark(const int x, const int y);

	//콘솔 커서를 이동 시키는 함수.
	void GotoCursor(const int x, const int y);
};