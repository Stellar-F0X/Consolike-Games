#pragma once

#include"Cell.h"

using namespace std;


class Board
{
		Cell** m_Map;				//맵
		Position* m_MinePos;		//지뢰 위치를 저장하는 배열


		//탐색 방향
		const Position m_ClearDirection[8] =
		{
			{ 1, 0 }, {-1, 0 },
			{ 0,-1 }, { 0, 1 },
			{ 1,-1 }, {-1, 1 },
			{ 1, 1 }, {-1,-1 }
		};
		

		int m_MapHeight = 0;		//맵의 세로 크기
		int m_MapWidth = 0;			//맵의 가로 크기

		int m_MineCount = 0;		//맵에 존재하는 지뢰 수

		bool m_Created = false;		//이미 맵이 생성 됐는지 여부.

	public:

		int GetWidth();

		int GetHeight();

		int GetMineCount();

		Position* GetMinePos();

		Cell* GetCell(const int x, const int y);

	public:

		//생성자
		Board(const int x, const int y, int mineCount);

		//파괴자
		~Board();

		//맵이 메모리에 올라온 후, 맵을 눌렀다면 지뢰의 위치와 빈공간 삭제 등을 담당하는 함수이다.
		//첫번째 클릭시 지뢰에 걸리면 안됨으로 이런 방법을 채택함.
		int SelectCell(const int x, const int y);

		//모든 칸의 타입을 그리는 함수.
		void ShowAnswer();

		//x,y 좌표가 배열의 범위를 넘었는지 확인 하는 함수.
		bool IsOutOfRange(const int x, const int y);

	private:

		//메모리에 맵을 올림.
		void CreateMap();

		//맵을 이루고 있는 각 칸들 중에서 플레이어가 선택한 칸을 제외하고 랜덤으로 타입을 지뢰로 설정함.
		void SetMines(const Position pos);

		//현재 모든 칸들은 지뢰(MINE)과 NONE 으로 설정된 상태이다.
		//NONE 타입 칸들의 명확한 타입을 설정하는 함수.
		void SetCellType();


		//DFS알고리즘을 통해 EMPTY 타입의 칸이 빈 공간으로 출력 될 수 있도록,
		//Select 함수를 호출하여 내부 m_Revealed 변수를 True로 바꿈.
		void EmptyClear(const int x, const int y);

		//EMPTY 타입의 칸과 인접한 SAFETY 타입의 칸이 출력 될 수 있도록 Select 함수를 호출함.
		void OutLineClear(const int x, const int y);

		//매개변수로 전달된 좌표 주변에 몇개의 지뢰가 있는지 찾은 후 개수를 반환함.
		int GetMineCount(const int x, const int y);
};