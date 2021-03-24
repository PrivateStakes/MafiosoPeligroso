#pragma once
#include "State.h"

class StateStack;

enum class PauseMenuItems
{
	Resume,
	ReturnToMainMenu
};

enum class MainMenuItems
{
	Play,
	QuitGame
};

class MenuState : public State
{
private:
	const bool pauseMenu; //could be changed to anything to have a more dynamic menu system
					//but I only need 2 menus
	
	const float buttonPressedTimer = 0.7f;
	float buttonPressedTimerElapsed = 0.f;

	const int buttonAmount = 2;	//Just doing this to illustrate that the menu creator is dynamic
	int cursorPos;

public:
	MenuState(const StateID InputStateId, StateStack& stateStack, bool isPauseMenu);
	~MenuState() override;

	int update(const float deltaTime, sf::RenderWindow& window, sf::Event& event) override;
	void render(sf::RenderWindow& window) override;
};

