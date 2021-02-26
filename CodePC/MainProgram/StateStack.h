#pragma once
#include <stack>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

enum class Levels;
enum class stateEvent
{
	ReturnToMainMenu = 1,
	GameState,
	PauseState,
	Unpause,
	ExitGame,
	LaunchEditor
};

enum class StateID
{
	GameState,
	PauseMenuState,
	MainMenuState,
	EditorState,
	CityMapState
};

class State;
class StateStack
{
private:
	int stateQuantity;
	const int statesCapacity = 10;
	State** states;
	

	int currentStateEvent = 0;
	bool gameOn = true;

public:
	std::string* currentLevel;

	//StateStack(const StateStack&) = default;
	StateStack(const int inputWindowWidth, const int inputWindowHeight);
	~StateStack();
	State* top();
	//void add_state(EStateID id, std::unique_ptr<State> state);
	void push(StateID id);
	void pop();
	void render(sf::RenderWindow& window);
	bool update(const float aDeltaTime, sf::RenderWindow& window);
	
	int currentLevelIndex = 1;
	const int windowWidth, windowHeight;
};
