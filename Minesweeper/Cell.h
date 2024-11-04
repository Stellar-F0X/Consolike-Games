#pragma once

enum eCELLTYPE
{
	NONE,
	EMPTY,
	MINE,
	SAFETY,
};

enum eREVEALTYPE 
{
	PRIVATE,
	PUBLIC,
	MARK
};

struct Position { int x; int y; };


class Cell
{
		//주변 8칸에 존재하는 지뢰의 수.
		int m_MineCount = 0;

		//플레이어에게 선택되어 타입이 공개 됐는지.
		eREVEALTYPE m_Revealed = PRIVATE;

		//해당 칸의 타입.
		eCELLTYPE m_CellType = NONE;


	public:
		//프로퍼티
		int GetMineCount();
		eREVEALTYPE GetRevealType();
		eCELLTYPE GetCellType();

	public:
		//타입과 인접한 지뢰 개수 설정.
		void Set(eCELLTYPE type, int mineCnt = 0);

		//플레이어가 해당 칸 선택.
		void Select(eREVEALTYPE type = PUBLIC);
};