#include "GameState.h"
#include "StateStack.h"
#include <iostream>

GameState::GameState(const StateID InputStateId, StateStack& stateStack) :
State(InputStateId)
{
	width = stateStack.windowWidth;
	height = stateStack.windowHeight;

	camera.setCenter(0, 0);
	camera.setSize(1280, 720);
	float temp = 0.f;
	texture.loadFromFile("../Images/cursor.png");
	cursor.setTexture(texture);
	cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
	cursor.setScale(2, 2);
}

GameState::~GameState()
{
	
}

int GameState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) returnMessage = (int)stateEvent::LaunchEditor;

	if (mouseVisability)
	{
		window.setMouseCursorVisible(false);
		mouseVisability = false;
	}
	
	/*if (unpauseTimer < unpauseTimerElapsed)
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			unpauseTimerElapsed = 0.f;
			returnMessage = (int)stateEvent::PauseState;
		}
	}*/

	player.rotateSprite(cursor.getPosition());

	player.move();

	camera.move(player.getInputDirection());
	cursor.move(sf::Vector2f(mouse.getPosition(window)) - (player.getPosition() - 2.f * player.getInputDirection()));

	mouse.setPosition(sf::Vector2i(player.getPosition()), window);
	if (bullets != nullptr)
	{
		bullets->update(deltaTime);
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
			npc.loseHealth(player.getDmg());
			delete bullets;
			bullets = nullptr;
			if (npc.getHealth() <= 0)
			{
				npc.setPosition(sf::Vector2f(-100, -100));
			}
		}

	}

	return returnMessage;
}

void GameState::render(sf::RenderWindow& window)
{
	window.clear();
	if (bullets != nullptr)
	{
		window.draw(*bullets);
	}
	window.draw(npc);
	window.draw(player);
	window.draw(cursor);
	window.setView(camera);

	window.display();
}