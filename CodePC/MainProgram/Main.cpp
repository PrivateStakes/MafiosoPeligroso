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
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Brutalshot: Throne of Guns");
	sf::RenderStates defaultRenderState;
	window.setKeyRepeatEnabled(false);

	sf::Event event;

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	StateStack* stateStack = new StateStack(WIDTH, HEIGHT);

	bool gameOn = true;

	while (window.isOpen())
	{
		/*while (window.pollEvent(event)) //DON'T REENABLE THIS, WILL BREAK CITYMAP
 		{
			if (event.type == sf::Event::Closed) window.close(); 
		}*/

		stateStack->backendUpdate();
		elapsedTimeSinceLastUpdate += clock.restart();
		while (elapsedTimeSinceLastUpdate > timePerFrame)
		{
			elapsedTimeSinceLastUpdate -= timePerFrame;
			gameOn = stateStack->update(timePerFrame.asSeconds(), window, event);
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