#pragma once

#include<iostream>
#include"Board.h"

using namespace std;


Board::Board(const int x, const int y, const int mineCount)
{
	m_MapWidth = x;
	m_MapHeight = y;
	m_MineCount = mineCount;

	CreateMap();
}


Board::~Board()
{
	for (int i = 0; i < m_MapHeight; ++i) {
		delete m_Map[i];
	}

	delete m_MinePos;
	delete m_Map;
}


int Board::GetWidth() 
{
	return m_MapWidth;
}


int Board::GetHeight()
{
	return m_MapHeight;
}

int Board::GetMineCount() 
{
	return m_MineCount;
}

Position* Board::GetMinePos() 
{
	return m_MinePos;
}

Cell* Board::GetCell(const int x, const int y)
{
	return &m_Map[y][x];
}



int Board::SelectCell(const int x, const int y)
{
	if (!m_Created) {

		SetMines({ x,y });
		SetCellType();

		m_Created = true;
	}
	EmptyClear(x, y);

	m_Map[y][x].Select();
	return m_Map[y][x].GetCellType();
}


void Board::CreateMap()
{
	m_Map = new Cell * [m_MapHeight];

	for (int i = 0; i < m_MapHeight; ++i) {

		m_Map[i] = new Cell[m_MapWidth]();
	}
}


void Board::SetMines(const Position pos)
{
	int x, y;
	bool isSamePos, isSameType;

	m_MinePos = new Position[m_MineCount];

	for (int i = 0; i < m_MineCount; ++i) {

		do {

			m_MinePos[i].x = x = (rand() % m_MapWidth);
			m_MinePos[i].y = y = (rand() % m_MapHeight);

			isSamePos = (x == pos.x && y == pos.y);
			isSameType = (m_Map[y][x].GetCellType() == MINE);
		} 
		while (isSameType || isSamePos);

		m_Map[y][x].Set(MINE);
	}
}


void Board::SetCellType()
{
	for (int col = 0; col < m_MapHeight; ++col) {
		for (int row = 0; row < m_MapWidth; ++row) {

			if (m_Map[col][row].GetCellType() == MINE) continue;

			int aroundMineCnt = GetMineCount(row, col);

			eCELLTYPE type = (aroundMineCnt > 0 ? SAFETY : EMPTY);
			m_Map[col][row].Set(type, aroundMineCnt);
		}
	}
}


bool Board::IsOutOfRange(const int x, const int y)
{
	bool xLimit = (x >= 0 && x < m_MapWidth);
	bool yLimit = (y >= 0 && y < m_MapHeight);

	return (xLimit && yLimit);
}


void Board::EmptyClear(const int x, const int y)
{
	for (int i = 0; i < 8; ++i) {

		int pX = x + m_ClearDirection[i].x;
		int pY = y + m_ClearDirection[i].y;

		if (IsOutOfRange(pX, pY) && m_Map[pY][pX].GetCellType() == EMPTY) {

			if (m_Map[pY][pX].GetRevealType() == PUBLIC) continue;

			m_Map[pY][pX].Select();
			OutLineClear(pX, pY);
			EmptyClear(pX, pY);
		}
	}
}


//공백인 칸을 중심으로 주변 8칸을 조사하기 때문에 내가 걱정했던 
//[?]로 표시 돼야 했던 부분까지 표시 된다는 문제는 일어나지 않는다.
void Board::OutLineClear(const int x, const int y)
{
	for (int i = 0; i < 8; ++i) {

		int pX = x + m_ClearDirection[i].x;
		int pY = y + m_ClearDirection[i].y;

		if (!IsOutOfRange(pX, pY)) continue;

		if (m_Map[pY][pX].GetCellType() == SAFETY) {
			m_Map[pY][pX].Select();
		}
	}
}


int Board::GetMineCount(const int x, const int y)
{
	int count = 0;

	for (int col = max(y - 1, 0); col <= min(y + 1, m_MapHeight - 1); ++col) {
		for (int row = max(x - 1, 0); row <= min(x + 1, m_MapWidth - 1); ++row) {

			if (x == row && y == col) continue;
			if (m_Map[col][row].GetCellType() == MINE) ++count;
		}
	}
	return count;
}