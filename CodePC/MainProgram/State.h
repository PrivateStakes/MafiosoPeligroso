#pragma once
#include <SFML/Graphics.hpp>
enum class StateID;

class State
{
protected:
	const StateID stateId;
	const float unpauseTimer = 0.4f;
	float unpauseTimerElapsed = 0.f;

public:
	State(const StateID InputStateId);
	virtual ~State();

	const StateID getStateID() const;

	virtual int update(const float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};