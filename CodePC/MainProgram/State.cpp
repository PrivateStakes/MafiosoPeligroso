#include "State.h"
#include "StateStack.h"

State::State(const StateID InputStateId) : stateId(InputStateId) {}
State::~State() {}

const StateID State::getStateID() const
{
	return stateId;
}