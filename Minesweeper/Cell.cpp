#include "Cell.h"



int Cell::GetMineCount() 
{
	return m_MineCount; 
}


eREVEALTYPE Cell::GetRevealType()
{
	return m_Revealed; 
}


eCELLTYPE Cell::GetCellType() 
{
	return m_CellType; 
}


void Cell::Set(eCELLTYPE type, int mineCnt)
{
	m_CellType = type;
	m_MineCount = mineCnt;
}


void Cell::Select(eREVEALTYPE type)
{
	m_Revealed = type;
}