#include "Game.h"
#include "AI.h"
#include "Wall.h"
#include "Goal.h"
#include "GridNode.h"
#include "GameObject.h"
#include "GridManager.h"
#include "SFML/System.hpp"
#include "GraphicManager.h"
#include <iostream>

Game::Game(){
	if (!m_Font.loadFromFile("Assets/arial.ttf"))
		std::cout << "Failed to load font" << std::endl;
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(24);
	m_Text.setColor(sf::Color::White);
	m_Text.setString("Press 'R' to restart");

	m_DTimerText.setFont(m_Font);
	m_DTimerText.setCharacterSize(12);
	m_DTimerText.setColor(sf::Color::White);
	m_DTimerText.setString("0");
}

Game::~Game(){}

void Game::run(){
	update();
}

void Game::update(){
	GraphicManager::getInstance()->initialize();
	GridManager::getInstance()->initialize(this);
	initialize();

	while (GraphicManager::getInstance()->getWindow()->isOpen()){
		updateDeltaTime();
		handleEvents();

		//----
		//Debug::clear();
		//Time
		//TimeManager::update();
		//User input
		//InputManager::update();
		//Update game state
		//Render
		//Debug::update();
		GridManager::getInstance()->update();
		
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++){
			(*it)->draw();
		}

		GraphicManager::getInstance()->draw(m_DTimerText);
		GraphicManager::getInstance()->draw(m_Text);
		GraphicManager::getInstance()->update();
		//----
	}
}

void Game::initialize(){
	std::cout << "Initialize game" << std::endl << "Initialize GridManager" << std::endl;
	GridManager::getInstance()->initialize(this);
	std::cout << "GridManager initialized" << std::endl << "Creating Walls" << std::endl;
	createWalls();
	std::cout << "Walls created" << std::endl << "Seting is nodes walkable" << std::endl;
	GridManager::getInstance()->setNodesIsWalkable(this);
	std::cout << "Setting nodes done" << std::endl << "Creating Goal and AI" << std::endl;
	m_GameObjects.push_back(new Goal(sf::Vector2f((sf::Vector2f)GraphicManager::getInstance()->getWindow()->getSize() - sf::Vector2f(150, 150))));
	m_GameObjects.push_back(new AI(sf::Vector2f(150, 150), *getGoal()->getPosition()));
	std::cout << "Goal and AI created" << std::endl << "Game initialized" << std::endl;
}

Game::GameObjectVector* Game::getGameObjects(){
	return &m_GameObjects;
}

Goal* Game::getGoal(){
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++){
		if ((*it)->getGameObjectType() == GameObject::Type::Goal){
			return (Goal*)*it;
		}
	}
}

void Game::handleEvents(){
	sf::Event event;
	while (GraphicManager::getInstance()->getWindow()->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			GraphicManager::getInstance()->getWindow()->close();
		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::R)
				int kalle = 0;
		}
	}
}

void Game::createWalls(){
	createSurrondingWalls();
	createRandomWalls();
}

void Game::createSurrondingWalls(){
	sf::Vector2f nodeSize = GridManager::getInstance()->getGridNodeSize();
	sf::Vector2f gridSize = *GridManager::getInstance()->getGridSize();
	sf::Vector2f node = sf::Vector2f(0, 0);
	sf::Vector2f startPos = *GridManager::getInstance()->getMatrixNode(node)->getPosition();

	sf::Vector2f pos = startPos;
	node = sf::Vector2f(gridSize.x - 1, 0);
	int width = GridManager::getInstance()->getMatrixNode(node)->getPosition()->x;
	int height = nodeSize.y;
	m_GameObjects.push_back(new Wall(pos, width, height));

	node = sf::Vector2f(gridSize.x - 1, 1);
	pos = *GridManager::getInstance()->getMatrixNode(node)->getPosition();
	node = sf::Vector2f(gridSize.x - 1, gridSize.y - 1);
	width = nodeSize.x;
	height = GridManager::getInstance()->getMatrixNode(node)->getPosition()->y - nodeSize.y - startPos.y;
	m_GameObjects.push_back(new Wall(pos, width, height));

	node = sf::Vector2f(0, gridSize.y - 1);
	pos = *GridManager::getInstance()->getMatrixNode(node)->getPosition();
	node = sf::Vector2f(gridSize.x - 1, gridSize.y - 1);
	width = GridManager::getInstance()->getMatrixNode(node)->getPosition()->x;
	height = nodeSize.y;
	m_GameObjects.push_back(new Wall(pos, width, height));

	node = sf::Vector2f(0, 1);
	pos = *GridManager::getInstance()->getMatrixNode(node)->getPosition();
	node = sf::Vector2f(0, gridSize.y - 1);
	width = nodeSize.x;
	height = GridManager::getInstance()->getMatrixNode(node)->getPosition()->y - nodeSize.y - startPos.y;
	m_GameObjects.push_back(new Wall(pos, width, height));
}

void Game::createRandomWalls(){
	sf::Vector2f nodeSize = GridManager::getInstance()->getGridNodeSize();
	sf::Vector2f gridSize = *GridManager::getInstance()->getGridSize();
	sf::Vector2f pxGridSize = sf::Vector2f(gridSize.x * 25, gridSize.y * 25);

	const int maxWallSize = 800;
	int currentWallSize = 0;

	while (currentWallSize < maxWallSize){
		GridNode* node = GridManager::getInstance()->getRandomNode();
		sf::Vector2f pos = *node->getPosition();
		int width = 25;
		int height = rand() % (int)pxGridSize.y;
		height -= height % (int)nodeSize.y;

		//50% chance to switch width and height
		if (rand() % 100 < 50){
			int oldwidth = width;
			width = height;
			height = oldwidth;
			if (pos.x + width >= pxGridSize.x)
				width = pxGridSize.x - pos.x;
			currentWallSize += width;
		}
		else{
			if (pos.y + height >= pxGridSize.y)
				height = pxGridSize.y - pos.y;
			currentWallSize += height;
		}

		m_GameObjects.push_back(new Wall(pos, width, height));
	}
}

void Game::updateDeltaTime(){
	sf::Time nowTime = m_Clock.getElapsedTime();
	m_DeltaTime = nowTime.asMilliseconds() - m_LastTime.asMilliseconds();
	m_LastTime = nowTime;

	m_DTimerText.setString(std::to_string(m_DeltaTime));

	int size = GraphicManager::getInstance()->getWindow()->getSize().x;
	int width = m_DTimerText.getLocalBounds().width;
	int x = size - width;

	m_DTimerText.setPosition(GraphicManager::getInstance()->getWindow()->getSize().x - m_DTimerText.getLocalBounds().width, 0);
}