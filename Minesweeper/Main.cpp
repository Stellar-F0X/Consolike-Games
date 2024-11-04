#include<iostream>
#include "Minsweeper.h"

using namespace std;


//프로세스.

//1. 메모리에 맵을 올림. 아직, 각 셀의 타입이 정해지지 않은 상태.
//2. 플레이어가 첫번째로 입력할때, 지뢰의 위치와 안전한 셀 위치가 정해짐.
//3. 첫번째 입력된 위치와 인접하며, 타입이 정해지지 않은 셀들을 빈 타입으로 바꿈.
//4. 선택한 셀의 타입을 반환함.
//5. 반환 받은 타입이 지뢰(Mine)이면 게임이 종료됨.


int main()
{
	Minsweeper* minsweeper = new Minsweeper;

	int width;
	int height;
	int mineCnt;

	do 
	{
		cout << "판의 가로 넓이 : "; cin >> width;
		cout << "판의 세로 넓이 : "; cin >> height;
		cout << "생성 지뢰 개수 : "; cin >> mineCnt;
	} 
	while (!minsweeper->Start(width, height, mineCnt));

	minsweeper->Run();

	delete minsweeper;
}