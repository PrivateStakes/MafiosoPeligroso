#include "State.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "StateStack.h"
#include "GameState.h"
#include "MenuState.h"
#include "EditorState.h"
#include "CityMap.h"
#include "Soldier.h"

StateStack::StateStack(const int inputWindowWidth, const int inputWindowHeight) :
	windowWidth(inputWindowWidth),
	windowHeight(inputWindowHeight)
{
	soldiers.push_back(new Soldier());
	soldiers[0]->setIsPlayer(true);
	soldiers[0]->setID(ID++);

	currentLevelIndex = 0;

	states = new State*[statesCapacity];
	stateQuantity = -1; //first object becomes 0
	for (int i = 0; i < statesCapacity; i++)
	{ 
		states[i] = nullptr; 
	}

	std::ifstream loadStream;
	loadStream.open("../Saves/save.txt");
	if (loadStream.is_open())
	{
		int i = 0;
		while (1)
		{
			std::string tileRow = "";
			getline(loadStream, tileRow);
			if (tileRow.size() > 0)
			{
				if (i == 0)
				{
					loadStream >> currentLevelIndex;
					if (currentLevelIndex < 0) currentLevelIndex = 0;
				}
				else
				{
					currentLevel = new std::string(tileRow);
					std::cout << *currentLevel << std::endl;
				}
			}
			else break;
			i++;
		}

		if (currentLevel == nullptr)
		{
			currentLevel = new std::string("level1.txt");
		}
	}
	loadStream.close();

	//push(StateID::MainMenuState);
	push(StateID::CityMapState);
}

StateStack::~StateStack()
{
	for (int i = 0; i < statesCapacity; i++)
	{
		delete states[i];
		states[i] = nullptr;
	}
	delete[] states;

	for (int i = 0; i < soldiers.size(); i++)
	{
		if (soldiers[i] != nullptr)
		{
			//delete soldiers[i];
			soldiers[i] = nullptr;
		}
	}
	soldiers.clear();

	std::ofstream saveStream;
	saveStream.open("../Saves/save.txt", std::ofstream::out | std::ofstream::trunc);
	if (saveStream.is_open())
	{
		saveStream << currentLevelIndex << std::endl;
		saveStream << *currentLevel;
	}
	saveStream.close();
}

State* StateStack::top()
{
	if (stateQuantity + 1 != 0) return states[stateQuantity];
}

void StateStack::push(StateID id)
{
	if (stateQuantity + 1 < statesCapacity)
	{
		switch (id)
		{
		case StateID::GameState:
			stateQuantity++;
			if (stateQuantity != -1) states[stateQuantity] = new GameState(StateID::GameState, *this, currentLevel, soldiers);
			break;
		case StateID::PauseMenuState:
			stateQuantity++;
			if (stateQuantity != -1) states[stateQuantity] = new MenuState(StateID::PauseMenuState, *this, true);
			break;
		case StateID::MainMenuState:
			stateQuantity++;
			if (stateQuantity != -1) states[stateQuantity] = new MenuState(StateID::MainMenuState, *this, false);
			break;

		case StateID::EditorState:

			if (stateQuantity - 1 <= 0 && stateQuantity + 1 != 0)
			{
				if (states[stateQuantity]->getStateID() == StateID::EditorState) pop();
			}

			stateQuantity++;
			if (stateQuantity != -1) states[stateQuantity] = new EditorState(StateID::EditorState, *this, currentLevel);
			break;

		case StateID::CityMapState:
			stateQuantity++;
			if (stateQuantity != -1) states[stateQuantity] = new CityMap(StateID::CityMapState, *this, soldiers);
			break;
		}
	}
	else assert(true == true && "Too many states! Increase 'statesCapacity' to allow for more");
}

void StateStack::pop()
{
	if (stateQuantity + 1!= 0) 
	{
		delete states[stateQuantity];
		states[stateQuantity] = nullptr;
		stateQuantity--;
	}
	else assert(stateQuantity + 1 == 0 && "Can't pop empty stack!");
}

void StateStack::render(sf::RenderWindow& window)
{
	if (stateQuantity + 1 != 0) states[stateQuantity]->render(window);
}

bool StateStack::update(const float deltaTime, sf::RenderWindow& window)
{
	if (stateQuantity + 1 != 0)
	{
		if (states[stateQuantity] != nullptr)
		{
			int tempInt = states[stateQuantity]->update(deltaTime, window);

			switch ((stateEvent)tempInt)
			{
			case stateEvent::ReturnToMainMenu:
				pop();
				pop();
				break;

			case stateEvent::GameState:
				push(StateID::GameState);
				break;

			case stateEvent::PauseState:
				push(StateID::PauseMenuState);
				break;

			case stateEvent::Unpause:
				pop();
				break;

			case stateEvent::ExitGame:
				gameOn = false;
				break;

			case stateEvent::LaunchEditor:
				push(StateID::EditorState);
				break;
			}

		}
	}

	return gameOn;
}

int StateStack::getID()
{
	return ID;
}

void StateStack::setID(int input)
{
	ID = input;
}