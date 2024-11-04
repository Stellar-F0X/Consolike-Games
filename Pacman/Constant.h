#pragma once

#define WIDTH 28
#define HEIGHT 32


enum EDirection {
	UP	  = 0,
	DOWN  = 1,
	LEFT  = 2,
	RIGHT = 3,
	ARROW = 224
};


enum EBoardTile
{
	NONE = 0 << 0,	 //none
	E	 = 1 << 0,	 //empty
	F	 = 1 << 1,	 //Food
	SF	 = 1 << 2,	 //Super Food
	W1	 = 1 << 3,   //wall1 : ¦­
	W2	 = 1 << 4,   //wall2 : ¦¬
	C1	 = 1 << 5,   //corner: ¦®
	C2	 = 1 << 6,   //corner: ¦¯
	C3	 = 1 << 7,   //corner: ¦°
	C4	 = 1 << 8,   //corner: ¦±
};