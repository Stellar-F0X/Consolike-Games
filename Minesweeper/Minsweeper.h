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
	bool m_GameOver;		//�÷��̾ ���ڸ� ����������, ���� ���� ���θ� �����ϴ� ����.

	Board* m_Board;			//�ʰ� �� ���� ����� �ִ� ����.
	Position m_CursorPos;	//�ܼ� Ŀ�� ��ġ�� �����ϴ� ����.

public :
	//�޸𸮿� �ö�� ������ ���� �ϴ� �Լ�.
	void Run();	

	//�� ���� ���� ���ο� �ʱ�ȭ ���� �ô� �Լ�.
	bool Start(const int x, const int y, const int mineCount);

private :	
	//Ű���� �Է��� ����ϴ� �Լ�
	void Input();

	//���� ������ ���� ���� �ʱ�ȭ�ϴ� �Լ�
	void Initialize();

	//���� Ŭ���� ������ Ȯ���ϰ� bool�� ��ȯ�ϴ� �Լ�.
	bool IsGameClear();

	//���� �� �׵θ��� �׸��� �Լ�.
	void DrawUI();

	//���� ĭ�� �׸��� DrawCell �Լ��� ȣ���ϰ� ��ġ�� �����ϴ� �Լ�.
	void DrawBoard();

	//ĭ�� ȣ�� �ϰ�, Ŀ���� ǥ���ϴ� �Լ�.
	void DrawCell(Cell* cell, const int x, const int y);

	//�迭 ������ �ʰ��ߴ��� Ȯ�� �ϴ� �Լ�.
	void RangeLimit(const int key);

	//Space bar�� ������ ���� �ǽ� ĭ�� ��ũ�ϴ� �Լ�.
	void SetMark(const int x, const int y);

	//�ܼ� Ŀ���� �̵� ��Ű�� �Լ�.
	void GotoCursor(const int x, const int y);
};