#include <SFML/Graphics.hpp>
#include<iostream>
#include "StateStack.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

const int WIDTH = 900;
const int HEIGHT = 600;

/*
animations:
- have even sprite sheet (duh)
- cell size = width/amount of cells
- make an sf::IntRect for you sprite (presumably which part you're showing)
- intRect(0, 0, texture.getSize().x / cell_amountX, texture.getSize().y / cell_amountY)
  ^^^-defines cell size
- sprite.setTextureRect(intRect) <- sets portion of sprite
- for new/specific frame: multiply desired frame pos by base value (nd some modulus shit idk)
intrect.top = which_cell * cell_height, moves which square up/down
intrect.left = which_cell * cell_width, moves which square right/left

stamped image:
sf::image
image.loadFromFile("../..")
image.createMaskFromColour

'procedurell programmering': användandet av funktioner
check what sf::RenderTarget and sf::RenderState (renderTarget.draw(sprite)) does
*/

int main()
{
	

	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DV1594 Muntlig tentamen 2");
	sf::RenderStates defaultRenderState;

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//std::unique_ptr<StateStack> stateStack = std::make_unique<StateStack>(WIDTH, HEIGHT);
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

			if (!stateStack->update(timePerFrame.asSeconds()))
			{
				window.close();
				gameOn = false;
			}/*
			if (!stateStack.get()->update(timePerFrame.asSeconds()))
			{
				window.close();
				gameOn = false;
			}*/
		}

		if (gameOn)
		{
			window.clear();
			stateStack->render(window);
			//stateStack.get()->render(window);
			window.display();
		}
	}
	delete stateStack;
	stateStack = nullptr;

	return 0;
}