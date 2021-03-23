#include "GameState.h"
#include "StateStack.h"
#include "CollissionMan.h"
#include "Tile.h"
#include "BulletType.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "EditorState.h"
#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

GameState::GameState(const StateID InputStateId, StateStack& stateStack, std::string* level, std::vector<Soldier*> *soldierHierarchy, int* solderSent) :
	State(InputStateId),
	width(stateStack.windowWidth),
	height(stateStack.windowHeight),
	currentFileName(level),
	soldiers(soldierHierarchy),
	soldierRecieved(solderSent),
	lastMousePos(sf::Vector2f(0,0)),
	counter(0),
	updateTimer(60)
{
	srand(time(NULL));
	camera.setCenter(0, 0);
	//camera.setSize(1280, 720);
	camera.setSize(width, height);
	tempEditor = new EditorState(InputStateId, stateStack, level);
	tileSizeX = tempEditor->getGridSizeX();
	tileSizeY = tempEditor->getGridSizeY();
	bulletTexture.loadFromFile("../Images/Bullet2.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(3,3);

	themeSong.openFromFile("../Sounds/Bestsong.wav");
	themeSong.setVolume(20);
	themeSong.play();
	themeSong.setLoop(true);

	powBuffer.loadFromFile("../Sounds/pow.wav");
	pow.setBuffer(powBuffer);
	kapowBuffer.loadFromFile("../Sounds/kapow.wav");
	kapow.setBuffer(kapowBuffer);
	deathsoundBuffer.loadFromFile("../Sounds/deathsound.wav");
	deathsound.setBuffer(deathsoundBuffer);

	bullets = new std::vector<BulletType*>;

	player = soldiers->at(0);
	float temp = 0.f;
	texture.loadFromFile("../Images/cursor.png");
	cursor.setTexture(texture);
	cursor.setOrigin(cursor.getGlobalBounds().width / 2, cursor.getGlobalBounds().height / 2);
	cursor.setScale(2, 2);

	amountOfBullets = 0;
	amountOfEnemySpawnPoints = 0;
	cap = 32;
	enemySpawnPointArray = new sf::Vector2f*[cap];

	std::ifstream loadStream;
	loadStream.open(currentDirectory + *currentFileName);
	if (!loadStream && loadStream.is_open()) assert(true == true && "No level present on location!");

	//Arms soldiers
	for (int i = 1; i < soldiers->size(); i++)
	{
		soldiers->at(i)->setPosition(sf::Vector2f(200, 200));
		soldiers->at(i)->setWeapon(nullptr);
		soldiers->at(i)->setWeapon(weaponFactory.buildWeapon((GunType)(rand() % 3)));
	}

	player->setWeapon(weaponFactory.buildWeapon((GunType)(playerWeapon)));
	player->setPosition(sf::Vector2f(200, 200));

	//Loads level data
	for (int i = 0; i < tileSizeY; i++)
	{
		std::vector<Tile*> tempGrid;
		tempTiles = new std::vector<Tile*>;
		tempFloor = new std::vector<Tile*>;	
		

		std::string tileRow = "";
		loadStream >> tileRow;
		loadStream.ignore();

		for (int j = 0; j < tileSizeX; j++)
		{
			tempGrid.push_back(new Tile("basic_tile.png"));
			tempGrid.back()->setPosition({
				(tempGrid.back()->getSprite().getGlobalBounds().width / 2) + ((j * tempGrid.back()->getSprite().getGlobalBounds().width)),
				(tempGrid.back()->getSprite().getGlobalBounds().height / 2) + ((i * tempGrid.back()->getSprite().getGlobalBounds().height)) });

			tempTiles->push_back(nullptr);
			tempFloor->push_back(nullptr);
			std::locale loc;
			if (!std::isblank(tileRow[j], loc))
			{
				char saveFileInformation = (char)tileRow[j] - 48;

				if (saveFileInformation != -99 && saveFileInformation != '\0')
				{
					bool addTile = true;
					Tile tempTile = tempEditor->loadTile((TileSorts)(saveFileInformation - 48));

					if (tempTile.getTileType() == 'c')
					{
						addTile = false;
						enemySpawnPointArray[amountOfEnemySpawnPoints++] = new sf::Vector2f(tempGrid[j]->getPosition());	//if the game crashes because of this, change to std::vector
						if (amountOfEnemySpawnPoints == cap)
						{
							addTile = false;

							cap += 3;
							sf::Vector2f** temp = new sf::Vector2f * [cap];
							for (int i = 0; i < amountOfEnemySpawnPoints; i++)
							{
								temp[i] = enemySpawnPointArray[i];
							}

							delete[] enemySpawnPointArray;
							enemySpawnPointArray = temp;

							for (int i = 0; i < amountOfEnemySpawnPoints; i++)
							{
								temp[i] = nullptr;
							}
							temp = nullptr;
						}
					}
					
					if (tempTile.getTileType() == 'e')
					{
						addTile = false;

						tempFloor->at(j) = new Tile(tempTile.getTexturePath());
						tempFloor->at(j)->setTileType(tempTile.getTileType());
						tempFloor->at(j)->setPosition(tempGrid[j]->getPosition());
					}

					if (addTile)
					{
						tempTiles->at(j) = new Tile(tempTile.getTexturePath());
						tempTiles->at(j)->setTileType(tempTile.getTileType());
						tempTiles->at(j)->setPosition(tempGrid[j]->getPosition());
					}
				}
			}
		}
		tiles.push_back(tempTiles);
		holder[i] = tempTiles;
		floor.push_back(tempFloor);
		holder2[i] = tempFloor;

		for (int k = 0; k < tempGrid.size(); k++)
		{
			delete tempGrid[k];
			tempGrid[k] = nullptr;
		}
	}
	loadStream.close();
	enemies = new Soldier*[amountOfEnemySpawnPoints];

	//Generates enemies
	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		int whichTexture = rand() % 2;
		std::string tempTexture;
		if (whichTexture == 1) tempTexture = "evil_character_1.png";
		else tempTexture = "evil_character_2.png";

		enemies[i] = new Soldier(tempTexture, "Joe", 5);
		enemies[i]->setPosition(*enemySpawnPointArray[i]);
		stateStack.setID(stateStack.getID() + 1);
		enemies[i]->setID(stateStack.getID());
		enemies[i]->setWeapon(weaponFactory.buildWeapon((GunType)(rand()%3)));
	}
	enemyAmount = amountOfEnemySpawnPoints;

	gameFont.loadFromFile("../Fonts/PressStart2P-Regular.ttf");
	healthText.setFont(gameFont);
	healthText.setFillColor(sf::Color::Green);
	healthText.setPosition(player->getPosition().x - width / 2 + 10, player->getPosition().y - height / 2 + 10);
	healthText.setString("Health: " + std::to_string(player->getHealth()));

	weaponText.setFont(gameFont);
	weaponText.setFillColor(sf::Color::Green);
	weaponText.setPosition(player->getPosition().x - width / 2 + 10, player->getPosition().y - height / 2 + 45);
	weaponText.setString("Weapon: " + player->getWeaponName());

	for (int i = 0; i < soldiers->size(); i++)
	{
		nameDisplayer.push_back(sf::Text());
		nameDisplayer[i].setFont(gameFont);
		nameDisplayer[i].setFillColor(sf::Color::Green);
		nameDisplayer[i].setPosition(soldiers->at(i)->getPosition());
		nameDisplayer[i].setString(soldiers->at(i)->getName());
		nameDisplayer[i].setOrigin(nameDisplayer[i].getGlobalBounds().width / 2, nameDisplayer[i].getGlobalBounds().height / 2);
	}
}

GameState::~GameState()
{
	delete tempEditor;
	tempEditor = nullptr;
	currentFileName = nullptr;

	for (int i = 0; i < enemyAmount; i++)
	{
		delete enemies[i];
	}
	delete[] enemies;
	
	for (int i = 0; i < amountOfEnemySpawnPoints; i++)
	{
		delete enemySpawnPointArray[i];
		enemySpawnPointArray[i] = nullptr;
	}
	delete[] enemySpawnPointArray;

	for (int i = 0; i < bullets->size(); i++)
	{
		delete bullets->at(i);
		bullets->at(i) = nullptr;
	}
	bullets->clear();
	delete bullets;

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr)
			{
				delete tiles[i]->at(j);
			}
			tiles[i]->at(j) = nullptr;
		}
		tiles[i]->clear();
	}
	tiles.clear();

	for (int i = 0; i < floor.size(); i++)
	{
		for (int j = 0; j < floor[i]->size(); j++)
		{
			if (floor[i]->at(j) != nullptr && floor[i]->at(j)->getTileType() == 'e')
			{
				delete floor[i]->at(j);
			}
			floor[i]->at(j) = nullptr;
		}
		floor[i]->clear();
	}
	floor.clear();

	soldiers = nullptr;
	player = nullptr;
	
	for (int i = 0; i < tileSizeY; i++)
	{
		if (holder[i] != nullptr)
		{
			delete holder[i];
			holder[i] = nullptr;
		}
	}
	for (int i = 0; i < tileSizeY; i++)
	{
		if (holder2[i] != nullptr)
		{
			delete holder2[i];
			holder2[i] = nullptr;
		}
	}

}

int GameState::backendUpdate()	
{
	for (int k = 0; k < enemyAmount; k++)
	{
		int xOrigin = 0;
		int yOrigin = 0;

		int xTarget = 0;
		int yTarget = 0;
		bool hasDetectedPlayer = false;

		for (int i = 0; i < floor.size(); i++)
		{
			for (int j = 0; j < floor[i]->size(); j++)
			{
				if (floor[i]->at(j) != nullptr)
				{
					floor[i]->at(j)->resetPathfindingValues();
					floor[i]->at(j)->setColour(sf::Color::Transparent);

					if (CollissionMan().intersectRectPoint(*floor[i]->at(j), enemies[k]->getPosition()))
					{
						enemies[k]->removeAllNodes();
						enemies[k]->addNode(floor[i]->at(j));
						floor[i]->at(j)->setVisitedByAlgorithm(false);
						floor[i]->at(j)->setTravelDistance(0);

						xOrigin = i;
						yOrigin = j;
					}

					if (CollissionMan().intersectRectPoint(*floor[i]->at(j), player->getPosition()))	//change to soldier loop for rushing NPCs
					{
						xTarget = i;
						yTarget = j;
						hasDetectedPlayer = true;
					}
				}
			}
		}

		if (hasDetectedPlayer)
		{
			floor[xOrigin]->at(yOrigin)->setHueristicDistance(sf::Vector2i(floor[xOrigin]->at(yOrigin)->getPosition()), (sf::Vector2i(floor[xTarget]->at(yTarget)->getPosition())));
			floor[xOrigin]->at(yOrigin)->setWeightDistance(floor[xOrigin]->at(yOrigin)->getHueristicDistance());

			/*
			Consider adding an x and y locally to each tile, making them aware of their own position
			*/

			//if this tanks framerate, change to using the 'backendUpdate' function for looping -- make the below code part of an if-statement
			//Alt. solution: make a timer for each soldier which counts down a random amount of seconds (less than 3?) to when they update their paths <----
			int x = xOrigin;
			int y = yOrigin;
			bool done = false;
			while (!done)
			{
				done = true;

				//currently analysed tile
				//Checks all floor tiles, in order, to find the first one used for analysis

				bool hasPickedElement = false;
				for (int i = 0; i < floor.size(); i++)
				{
					if (!hasPickedElement)
					{
						for (int j = 0; j < floor[i]->size(); j++)
						{
							if (floor[i]->at(j) != nullptr)
							{
								if (floor[i]->at(j)->getVisitedByAlgorithm() == false)	//Will ignore visited nodes, so this defines the open set
								{
									if (!hasPickedElement)
									{
										if (floor[x]->at(y) != nullptr)
										{
											if (floor[i]->at(j)->getWeightDistance() <= floor[x]->at(y)->getWeightDistance()) //is part of the open set and is an improved distance
											{
												done = false;	//Exits once all nodes have been visited, as it won't be set to false
												hasPickedElement = true;

												x = i;
												y = j;
											}
										}
									}

									floor[i]->at(j)->setColour(sf::Color::Cyan);
								}
								else floor[i]->at(j)->setColour(sf::Color::Red);
							}

							if (hasPickedElement) break;
						}
					}
					else break;
				}

				if (floor[x]->at(y) != nullptr)
				{
					floor[x]->at(y)->setVisitedByAlgorithm(true);	//set to closed set

					if (floor[x]->at(y) == floor[xTarget]->at(yTarget))
					{
						//for now -- maybe have a check if the enemy really needs a new set of nodes rn?
						enemies[k]->removeAllNodes();
						done = true;

						Tile* temp = floor[xTarget]->at(yTarget);
						bool allNodesAdded = false;

						int i = 0;
						int timeoutQuantity = 3000;	//increase if floor area ever exceeds 3000 sqr tiles -- will increase loading times for unreachable tiles though
						while (!allNodesAdded)
						{
							if (temp == floor[xOrigin]->at(yOrigin) || i > timeoutQuantity) allNodesAdded = true;
							else
							{
								if (temp->getPreviousNode() != nullptr)
								{
									if (enemies[k]->getNodes().size() > 0) enemies[k]->emplaceNode(enemies[k]->getNodes().size() - i, temp->getPreviousNode());
									else enemies[k]->addNode(temp->getPreviousNode());
									temp->setColour(sf::Color::Black);
									temp = temp->getPreviousNode();
								}
							}

							i++;
						}
						temp = nullptr;

						enemies[k]->getNodes();
					}

					//check neighbouring nodes and decide whether they're to be checked or not
					{
						int tempX;
						int tempY;
						unsigned int shortestDistance = 0 - 1;

						for (int i = 0; i < 4; i++)
						{
							int operator1 = 1;
							int operator2 = 1;

							//Assign operator difference
							switch (i)
							{
								//Each cardinal directions
							case 0:
								operator2 = 0;
								break;
							case 1:
								operator1 *= -1;
								operator2 = 0;
								break;
							case 2:
								operator1 = 0;
								break;
							case 3:
								operator1 = 0;
								operator2 *= -1;
								break;
							}

							tempX = x + operator1;
							tempY = y + operator2;

							//checks each connection for the node with the lowest travel distance
							if ((tempX) < floor.size())
							{
								if ((tempY) < floor[tempX]->size())
								{
									if (floor[tempX]->at(tempY) != nullptr)
									{
										int tempTravelDistance = floor[x]->at(y)->getTravelDistance() + 1;	//used for compárison to current distance before setting

										if (!floor[tempX]->at(tempY)->getVisitedByAlgorithm())	//Is part of open set
										{
											floor[tempX]->at(tempY)->setTravelDistance(floor[x]->at(y)->getTravelDistance() + 1);	//set distance
											if (floor[tempX]->at(tempY)->getTravelDistance() <= shortestDistance)
											{
												floor[tempX]->at(tempY)->setPreviousNode(floor[x]->at(y));
												floor[x]->at(y)->setNextNode(floor[tempX]->at(tempY));			//<--- not sure about this one
											}
										}
										else if (tempTravelDistance < floor[tempX]->at(tempY)->getTravelDistance())	//Is part of closed set and new distance is shorter
										{
											floor[tempX]->at(tempY)->setVisitedByAlgorithm(false);

											floor[tempX]->at(tempY)->setTravelDistance(tempTravelDistance);																				//g
											floor[tempX]->at(tempY)->getNextNode()->setPreviousNode(nullptr);
											floor[tempX]->at(tempY)->getPreviousNode()->setNextNode(nullptr);

											floor[tempX]->at(tempY)->setPreviousNode(floor[x]->at(y));
											floor[tempX]->at(tempY)->setNextNode(nullptr);						//<--- not sure about this one
											floor[x]->at(y)->setNextNode(floor[tempX]->at(tempY));
										}

										if (shortestDistance < floor[tempX]->at(tempY)->getTravelDistance()) shortestDistance = floor[tempX]->at(tempY)->getTravelDistance();

										floor[tempX]->at(tempY)->setHueristicDistance(sf::Vector2i((x + operator1), (tempY)), sf::Vector2i((xTarget), (yTarget)));						//h
										floor[tempX]->at(tempY)->setWeightDistance(floor[tempX]->at(tempY)->getTravelDistance() + floor[tempX]->at(tempY)->getHueristicDistance());	//f
									}
								}
							}
						}
					}
				}
			}

			floor[xOrigin]->at(yOrigin)->setColour(sf::Color::Green);
			floor[xTarget]->at(yTarget)->setColour(sf::Color::Yellow);
		}
	}

	return 0;
}

int GameState::update(const float deltaTime, sf::RenderWindow& window)
{
	int returnMessage = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) returnMessage = (int)stateEvent::ExitGame;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) returnMessage = (int)stateEvent::LaunchEditor;
	if (counter != 0)
	{
		counter = (counter + 1) % updateTimer;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
		{
			playerWeapon = (playerWeapon + 1) % 3;
			delete player->getWeaponAddr();
			player->setWeapon(weaponFactory.buildWeapon((GunType)(playerWeapon)));
			weaponText.setString("Weapon: " + player->getWeaponName());
			counter++;
		}
	}
	
	

	//Update all tiles
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr) tiles[i]->at(j)->update(deltaTime);
		}
	}

	if (mouseVisability)
	{
		window.setMouseCursorVisible(false);
		mouseVisability = false;
	}

	player->rotateSprite(cursor.getPosition());

	for (int i = 0; i < enemyAmount; i++)
	{
		if (enemies[i]->isAbleToShoot() && rand()%5 == 0)
		{
			bool shot = false;
			for (int j = 0; j < *soldierRecieved && shot != true; j++)
			{
				if (abs(enemies[i]->getPosition().x - soldiers->at(j)->getPosition().x) < 300 && abs(enemies[i]->getPosition().y - soldiers->at(j)->getPosition().y) < 300)
				{
					if (enemies[i]->getWeaponName() == "Sniper") kapow.play();
					else pow.play();
					enemies[i]->rotateSprite(soldiers->at(j)->getPosition());
					//bullets.push_back(new Bullet(enemies[i]->shoot((soldiers->at(j)->getPosition() - enemies[i]->getPosition()))));
					bullets->push_back(enemies[i]->shoot(soldiers->at(j)->getPosition() - enemies[i]->getPosition(), weaponFactory));
					shot = true;
				}
			}
			
		}
	}

	collideCheck = false;
	bool deleteBullet = false;

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr)
			{
				for (int k = 0; k < *soldierRecieved; k++)
				{
					if (CollissionMan().intersectCircRect(*soldiers->at(k), *tiles[i]->at(j), 'a'))
					{
						soldiers->at(k)->setColl(true);
					}
				}
				for (int k = 0; k < enemyAmount; k++)
				{
					if (CollissionMan().intersectCircRect(*enemies[k], *tiles[i]->at(j), 'a'))
					{
						enemies[k]->setColl(true);
					}
				}
				collideCheck = false;
			}
		}
	}
	for (int k = 0; k < *soldierRecieved; k++)
	{
		if (!soldiers->at(k)->getColl())
		{
			soldiers->at(k)->update((float)deltaTime);
			if (k == 0)
			{
				currentMousePos = sf::Vector2f(mouse.getPosition(window));
				int x = player->getPosition().x;
				int y = player->getPosition().y;
				if (player->getPosition().x > width)
				{
					x = width;
				}
				if (player->getPosition().y > height)
				{
					y = height;
				}
				cursor.move(currentMousePos - lastMousePos + player->getInputDirection(deltaTime));
				mouse.setPosition(sf::Vector2i(width/2, height/2), window);
			}
		}
		soldiers->at(k)->setColl(false);
	}
	lastMousePos = sf::Vector2f(mouse.getPosition(window));

	for (int k = 0; k < enemyAmount; k++)
	{
		if (!enemies[k]->getColl())
		{
			enemies[k]->update((float)deltaTime);
		}
		enemies[k]->setColl(false);
	}

	
	
	for (int i = 0; i < bullets->size(); i++)
	{
		//if (bullets->at(i) != nullptr) bullets->at(i)->update(deltaTime);
		bullets->at(i)->update(deltaTime);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->isAbleToShoot())
	{
		if (player->getWeaponName() == "Sniper") kapow.play();
		else pow.play();
		bullets->push_back(player->shoot((cursor.getPosition() - player->getPosition()), weaponFactory));
	}

	for (int k = 0; k < bullets->size(); k++)
	{
		bool deleteBullet = false;

		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i]->size(); j++)
			{
				if (tiles[i]->at(j) != nullptr)
				{
					if (CollissionMan().intersectCircRect(*bullets->at(k), *tiles[i]->at(j), 'f'))
					{
						deleteBullet = true;

						if (tiles[i]->at(j)->getTileType() == 'f')
						{
							tiles[i]->at(j)->setHP(bullets->at(k)->getDmg());
							if (tiles[i]->at(j)->getHP() <= 0)
							{
								floor[i]->at(j) = new Tile(tempEditor->loadTile(TileSorts::floor));
								floor[i]->at(j)->setTileType('e');
								floor[i]->at(j)->setPosition(tiles[i]->at(j)->getPosition());
								delete tiles[i]->at(j);
								tiles[i]->at(j) = nullptr;
							}
						}

					}
				}
			}
		}

		for (int j = 0; j < enemyAmount; j++)
		{
			if (bullets->size() > 0 && k < bullets->size())
			{
				if (CollissionMan().intersectCircCirc(*bullets->at(k), *enemies[j]) && bullets->at(k)->getID() != enemies[j]->getID())
				{
					enemies[j]->loseHealth(bullets->at(k)->getDmg());
					deleteBullet = true;
					if (enemies[j]->getHealth() <= 0)
					{
						delete enemies[j];
						if (enemyAmount > 1 && j != enemyAmount - 1)
						{
							enemies[j] = enemies[enemyAmount - 1];
						}
						enemyAmount--;
						if (enemyAmount == 0)
						{
							std::cout << "You have killed every single enemy and won the demo!\n";
							returnMessage = (int)stateEvent::ExitGame;
						}
						deathsound.play();
					}
				}
			}
		}

		if (CollissionMan().intersectCircCirc(*player, *bullets->at(k)) && bullets->at(k)->getID() != player->getID())
		{
			player->loseHealth(bullets->at(k)->getDmg());
			deleteBullet = true;
			healthText.setString("Health: " + std::to_string(player->getHealth()));

			if (player->getHealth() <= 0)
			{
				if (soldiers->size() > 1)	//looks dangerous, if soldiers cause crashes: try popping the stack done proper
				{
					//Deletes player
					delete soldiers->at(0);
					soldiers->at(0) = nullptr;
					player = nullptr;

					//Copies soldier
					soldiers->at(0) = soldiers->at(1);
					soldiers->at(1) = nullptr;

					//Puts another soldier from the hierarchy in the second spot
					if (soldiers->at(1) != soldiers->back())
					{
						soldiers->at(1) = soldiers->back();
						soldiers->back() = nullptr;
					}

					//Sets the soldier in the front as the new player
					soldiers->at(0)->setIsPlayer(true);
					player = soldiers->at(0);

					//Reduces the size of the vector
					soldiers->pop_back();
					if (*soldierRecieved > soldiers->size())
					{
						(*soldierRecieved)--;
					}
					cursor.setPosition(player->getPosition());
					healthText.setString("Health: " + std::to_string(player->getHealth()));
					weaponText.setString("Weapon: " + player->getWeaponName());
					for (int i = 0; i < soldiers->size(); i++)
					{
						nameDisplayer[i].setString(soldiers->at(i)->getName());
						nameDisplayer[i].setOrigin(nameDisplayer[i].getGlobalBounds().width / 2, nameDisplayer[i].getGlobalBounds().height / 2);
					}
					deathsound.play();

				}
				else returnMessage = (int)stateEvent::ExitGame;
			}
		}

		if (deleteBullet)
		{
			if (bullets->at(k) != bullets->back())
			{
				delete bullets->at(k);
				bullets->at(k) = nullptr;
				bullets->at(k) = bullets->at(bullets->size()-1);
				bullets->at(bullets->size() - 1) = nullptr;

			}
			else if (bullets->back() != nullptr)
			{
				delete bullets->back();
				bullets->back() = nullptr;
			}

			bullets->pop_back();
		}
	}
	return returnMessage;
}

void GameState::render(sf::RenderWindow& window)
{
	camera.setCenter(player->getPosition() + 2.f * player->getInputDirection(1 / 60));
	window.setView(camera);
	for (int i = 0; i < floor.size(); i++)
	{
		for (int j = 0; j < floor[i]->size(); j++)
		{
			if (floor[i]->at(j) != nullptr)
			{
				if (floor[i]->at(j)->getTileType() == 'e') floor[i]->at(j)->draw(window);
				else if (floor[i]->at(j)->getTileType() == 'c') floor[i]->at(j)->draw(window);
				else if (floor[i]->at(j)->getTileType() == 'd') floor[i]->at(j)->draw(window);
			}
		}
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i]->size(); j++)
		{
			if (tiles[i]->at(j) != nullptr) tiles[i]->at(j)->draw(window);
		}
	}

	for (int i = 0; i < bullets->size(); i++)
	{
		bulletSprite.setPosition(bullets->at(i)->getPosition());
		bulletSprite.setRotation(bullets->at(i)->getRotation());
		window.draw(bulletSprite);
	}

	for (int i = 0; i < *soldierRecieved; i++)
	{
		if (soldiers->at(i) != nullptr)
		{
			window.draw(*soldiers->at(i));
		}
		
	}

	for (int i = 0; i < enemyAmount; i++)
	{
		window.draw(*enemies[i]);
	}
	healthText.setPosition(player->getPosition().x - width / 2 + 10, player->getPosition().y - height / 2 + 10);
	weaponText.setPosition(player->getPosition().x - width / 2 + 10, player->getPosition().y - height / 2 + 45);
	window.draw(healthText);
	window.draw(weaponText);
	for (int i = 0; i < *soldierRecieved; i++)
	{
		nameDisplayer[i].setPosition(soldiers->at(i)->getPosition().x, soldiers->at(i)->getPosition().y - 55);
		window.draw(nameDisplayer[i]);
	}

	window.draw(cursor);
}