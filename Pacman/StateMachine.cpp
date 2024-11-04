#include "StateMachine.h"

template <typename T>
void StateMachine<T>::AddState(T key, State* state)
{
	this->_stateMap.insert(key, state);
}


template <typename T>
void StateMachine<T>::ChangeState(T key)
{
	if (this->_stateMap.find(key) != nullptr)
	{
		if (key == _currentState)
		{
			return;
		}

		_stateMap[_currentState]->OnExit();
		_stateMap[key]->OnEnter();
		_currentState = key;
	}
}
