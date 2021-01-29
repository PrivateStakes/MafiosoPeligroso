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
	
	Player player;
	NPC npc;
	std::srand((unsigned)time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeSt MaFiA gAmE eVeR!");
	sf::RenderStates defaultRenderState;

	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Texture texture;
	sf::Sprite cursor;
	sf::View camera;

	camera.setCenter(0, 0);
	camera.setSize(1280, 720);
	float temp = 0.f;

	sf::Mouse mouse;

	Bullet* bullets = nullptr;
	//sf::Cursor cursor;
	window.setMouseCursorVisible(false);
	texture.loadFromFile("../images/cursor.png");
	cursor.setTexture(texture);
	cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
	cursor.setScale(2, 2);

	

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

			if (!stateStack->update(timePerFrame.asSeconds(), window))
			{
				window.close();
				gameOn = false;
			}
			player.rotateSprite(cursor.getPosition());
		
			player.move();

			camera.move(player.getInputDirection());
			cursor.move(sf::Vector2f(mouse.getPosition(window)) - (player.getPosition() - 2.f* player.getInputDirection()));

			mouse.setPosition(sf::Vector2i(player.getPosition()), window);
			if (bullets != nullptr)
			{
				bullets->update(timePerFrame.asSeconds());
			}
			/*
			if (!stateStack.get()->update(timePerFrame.asSeconds()))
			{
				window.close();
				gameOn = false;
			}*/
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.ableToShoot())
			{
				bullets = new Bullet(player.shoot((cursor.getPosition() - player.getPosition())));
			}
			if (bullets != nullptr)
			{
				if (npc.gotHit(*bullets))
				{
					npc.loseHealth();
					delete bullets;
					bullets = nullptr;
					if (npc.getHealth() <= 0)
					{
						npc.setPosition(sf::Vector2f(-100, -100));
					}
				}
				
			}
		}

		if (gameOn)
		{
			window.clear();
			stateStack->render(window);
			if (bullets != nullptr)
			{
				window.draw(*bullets);
			}
			window.draw(npc);
			window.draw(player);
			window.draw(cursor);
			window.setView(camera);
			
			
			//stateStack.get()->render(window);
			window.display();
		}
	}
	delete stateStack;
	stateStack = nullptr;

	return 0;
}