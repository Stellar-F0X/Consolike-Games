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
		//�ֺ� 8ĭ�� �����ϴ� ������ ��.
		int m_MineCount = 0;

		//�÷��̾�� ���õǾ� Ÿ���� ���� �ƴ���.
		eREVEALTYPE m_Revealed = PRIVATE;

		//�ش� ĭ�� Ÿ��.
		eCELLTYPE m_CellType = NONE;


	public:
		//������Ƽ
		int GetMineCount();
		eREVEALTYPE GetRevealType();
		eCELLTYPE GetCellType();

	public:
		//Ÿ�԰� ������ ���� ���� ����.
		void Set(eCELLTYPE type, int mineCnt = 0);

		//�÷��̾ �ش� ĭ ����.
		void Select(eREVEALTYPE type = PUBLIC);
};