#include <SFML/Graphics.hpp>
#include<iostream>
#include "StateStack.h"
#include "Player.h"
#include "NPC.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

const int WIDTH = 1680;
const int HEIGHT = 1050;

int main()
{
	
	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeSt MaFiA gAmE eVeR!");
	sf::RenderStates defaultRenderState;

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	StateStack* stateStack = new StateStack(WIDTH, HEIGHT);

	bool gameOn = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		elapsedTimeSinceLastUpdate += clock.restart();
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;
			gameOn = stateStack->update(timePerFrame.asSeconds(), window);
		}

		if (gameOn)
		{
			window.clear();
			stateStack->render(window);
			window.display();
		}
		else window.close();
	}
	delete stateStack;
	stateStack = nullptr;

	return 0;
}