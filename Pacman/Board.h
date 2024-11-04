#pragma once
#include <map>
#include <vector>
#include "Component.h"
#include "Constant.h"
#include "IContactable.h"
#include "Layer.h"


class Board : public Component
{
public:
	Board(string name) : Component(name, { 0, 0 }) {}
	~Board();

public:
	EBoardTile GetTile(int x, int y) const;
	EBoardTile GetTile(Vector2 position) const;

	void SetTile(const int x, const int y, const EBoardTile tile);
	void RegistryContactable(IContactable* contactable);

	void OnStart();
	void OnUpdate(float deltaTime);
	void OnDelete();
	void OnRender();
	void CheckContactBetweenEntities() const;
	void CheckContactFoods() const;
	bool CanMove(Vector2 position);

private:
	void CheckContact() const;
	bool IsValidRange(int x, int y) const;

private:
	bool _checkCollisions = true;

	vector<Layer*> _layers;
	vector<IContactable*> _contactables;

	EBoardTile _boardMold[32][28] = 
	{
		{ C1,W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	C2,	C1,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	C2  }, //1
		{ W1, F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1	}, //2
		{ W1, F,	C1,	W2,	W2,	C2,	F,	C1,	W2,	W2,	W2,	C2,	F,	W1,	W1,	F,	C1,	W2,	W2,	W2,	C2,	F,	C1,	W2,	W2,	C2,	F,	W1	}, //3
		{ W1, F,	W1,	E,	E,	W1,	F,	W1,	E,	E,	E,	W1,	F,	W1,	W1,	F,	W1,	E,	E,	E,	W1,	F,	W1, E,	E,	W1,	F,	W1	}, //4
		{ W1, F,	C4,	W2,	W2,	C3,	F,	C4,	W2,	W2,	W2,	C3,	F,	C4,	C3,	F,	C4,	W2,	W2,	W2,	C3,	F,	C4,	W2,	W2,	C3,	F,	W1	}, //5
		{ W1, F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1	}, //6
		{ W1, F,	C1,	W2,	W2,	C2,	F,	C1,	C2,	F,	C1,	W2,	W2,	W2,	W2,	W2,	W2,	C2,	F,	C1,	C2,	F,	C1,	W2,	W2,	C2,	F,	W1	}, //7
		{ W1, F,	C4,	W2,	W2,	C3,	F,	W1,	W1,	F,	C4,	W2,	W2,	C2,	C1,	W2,	W2,	C3,	F,	W1,	W1,	F,	C4,	W2,	W2,	C3,	F,	W1	}, //8
		{ W1, F,	F,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	F,	F,	W1	}, //9
		{ C4,W2,	W2,	W2,	W2,	C2,	F,	W1,	C4,	W2,	W2,	C2,	F,	W1,	W1,	F,	C1,	W2,	W2,	C3,	W1,	F,	C1,	W2,	W2,	W2,	W2,	C3,	}, //10
		{ E,	E,	E,	E,  E,	W1,	F,	W1,	C1,	W2,	W2,	C3,	F,	C4,	C3,	F,	C4,	W2,	W2,	C2,	W1,	F,	W1 ,E,	E,	E,	E,  E,	}, //11
		{ E,	E,	E,	E,  E,	W1,	F,	W1,	W1,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1,	W1,	F,	W1 ,E,	E,	E,	E,  E,	}, //12
		{ E,	E,	E,	E,  E,	W1,	F,	W1,	W1,	F,	C1,	W2,	W2,	E,	E,	W2,	W2,	C2,	F,	W1,	W1,	F,	W1 ,E,	E,	E,	E,  E,	}, //13
		{ W2, W2,	W2,	W2,	W2,	C3,	F,	C4,	C3,	F,	W1,	E,	E,	E,	E,	E,	E,	W1,	F,	C4,	C3,	F,	C4,	W2,	W2,	W2,	W2,	W2,	}, //14
		{ F, F,	F,	F,	F,	F,	F,	F,	F,	F,	W1,	E,	E,	E,	E,	E,	E,	W1,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F	}, //15 
		{ W2, W2,	W2,	W2,	W2,	C2,	F,	C1,	C2,	F,	W1,	E,	E,	E,	E,	E,	E,	W1,	F,	C1,	C2,	F,	C1,	W2,	W2,	W2,	W2,	W2,	}, //16 
		{ E,	E,	E,	E,  E,	W1,	F,	W1,	W1 ,F,	C4,	W2,	W2,	W2,	W2,	W2,	W2,	C3,	F,	W1,	W1 ,F,	W1 ,E,	E,	E,	E,  E,	}, //17
		{ E,	E,	E,	E,  E,	W1,	F,	W1,	W1 ,F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1,	W1 ,F,	W1 ,E,	E,	E,	E,  E,	}, //18
		{ E,	E,	E,	E,  E,	W1,	F,	W1,	W1 ,F,	C1,	W2,	W2,	W2,	W2,	W2,	W2,	C2,	F,	W1,	W1 ,F,	W1 ,E,	E,	E,	E,  E,	}, //19
		{ C1,W2,	W2,	W2,	W2,	C3,	F,	C4,	C3,	F,	C4,	W2,	W2,	C2,	C1,	W2,	W2,	C3,	F,	C4,	C3,	F,	C4,	W2,	W2,	W2,	W2,	C2,	}, //20
		{ W1, F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1	}, //21
		{ W1, F,	C1,	W2,	W2,	C2,	F,	C1,	W2,	W2,	W2,	C2,	F,	W1,	W1,	F,	C1,	W2,	W2,	W2,	C2,	F,	C1,	W2,	W2,	C2,	F,	W1	}, //22
		{ W1, F,	C4,	W2,	C2,	W1,	F,	C4,	W2,	W2,	W2,	C3,	F,	C4,	C3,	F,	C4,	W2,	W2,	W2,	C3,	F,	W1,	C1,	W2,	C3,	F,	W1	}, //23
		{ W1, F,	F,	F,	W1,	W1,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	W1	}, //24
		{ C4,W2,	C2,	F,	W1,	W1,	F,	C1,	C2,	F,	C1,	W2,	W2,	W2,	W2,	W2,	W2,	C2,	F,	C1,	C2,	F,	W1,	W1,	F,	C1,	W2,	C3	}, //25
		{ C1,W2,	C3,	F,	C4,	C3,	F,	W1,	W1,	F,	C4,	W2,	W2,	C2,	C1,	W2,	W2,	C3,	F,	W1,	W1,	F,	C4,	C3,	F,	C4,	W2,	C2	}, //26
		{ W1, F,	F,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	W1,	W1,	F,	F,	F,	F,	W1,	W1 ,F,	F,	F,	F,	F,	F,	W1	}, //27
		{ W1, F,	C1,	W2,	W2,	W2,	W2,	C3,	C4,	W2,	W2,	C2,	F,	W1,	W1,	F,	C1,	W2,	W2,	C3,	C4,	W2,	W2,	W2,	W2,	C2,	F,	W1	}, //28
		{ W1, F,	C4,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	C3,	F,	C4,	C3,	F,	C4,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	C3,	F,	W1	}, //29
		{ W1, F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	F,	W1	}, //31
		{ C4,W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	W2,	C3  }, //32
	};
};
