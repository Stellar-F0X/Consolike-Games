#pragma once
#include <map>
#include "State.h"

using namespace std;

template<typename T>
class StateMachine
{
public:
	void AddState(T key, State* state);
	void ChangeState(T key);

private:
	T _currentState;
	map<T, State*> _stateMap;
};