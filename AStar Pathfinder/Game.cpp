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

bool Game::m_Debug = false;

Game::Game(){
	m_Restart = false;
}

Game::~Game(){}

void Game::run(){
	update();
}

void Game::update(){
	GraphicManager::getInstance()->initialize();
	GridManager::getInstance()->initialize();
	initializeText();
	initialize();

	while (GraphicManager::getInstance()->getWindow()->isOpen()){
		if (m_Restart){
			initialize();
			m_Restart = false;
		}

		updateDeltaTime();
		handleEvents();
		GridManager::getInstance()->update();
		
		for (auto it : m_GameObjects)
			it->draw();

		GraphicManager::getInstance()->draw(m_DTimerText);
		GraphicManager::getInstance()->draw(m_Text);
		GraphicManager::getInstance()->update();
	}
}

void Game::initialize(){
	std::cout << "Initializing game" << std::endl;
	if (!m_GameObjects.empty())
		deleteGameObjects();
	createWalls();
	GridManager::getInstance()->setNodesIsWalkable(this);
	createAIAndGoal();
	std::cout << "Initializing game done" << std::endl;
}

void Game::initializeText(){
	m_Text.setFont(*GraphicManager::getInstance()->getFont());
	m_Text.setCharacterSize(24);
	m_Text.setColor(sf::Color::White);
	m_Text.setString("Press 'R' to restart, 'D' to show/hide debugging help");

	m_DTimerText.setFont(*GraphicManager::getInstance()->getFont());
	m_DTimerText.setCharacterSize(12);
	m_DTimerText.setColor(sf::Color::White);
	m_DTimerText.setString("0");
}

void Game::deleteGameObjects(){
	for (auto it : m_GameObjects)
		delete it;
	m_GameObjects.clear();
}

Game::GameObjectVector* Game::getGameObjects(){
	return &m_GameObjects;
}

Goal* Game::getGoal(){
	for (auto it : m_GameObjects){;
		if (it->getGameObjectType() == GameObject::Type::Goal){
			return (Goal*)it;
		}
	}
}

bool Game::getDebugging(){
	return m_Debug;
}

void Game::handleEvents(){
	sf::Event event;
	while (GraphicManager::getInstance()->getWindow()->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			GraphicManager::getInstance()->getWindow()->close();
		if (event.type == sf::Event::KeyPressed){
			if (event.key.code == sf::Keyboard::R){
				m_Restart = true;
				std::cout << "Restarting" << std::endl << std::endl;
			}
			if (event.key.code == sf::Keyboard::D){
				m_Debug = !m_Debug;
				std::cout << "Debuging " << m_Debug  << std::endl;
			}
		}
	}
}

void Game::createWalls(){
	createSurrondingWalls();
	//createRandomWalls();
}

void Game::createAIAndGoal(){
	int gridSize = GridManager::getInstance()->getGridSize() - 1;
	GridNode* goalNode = GridManager::getInstance()->getNode(std::rand() % gridSize);
	while (!goalNode->getIsWalkable())
		goalNode = GridManager::getInstance()->getNode(std::rand() % gridSize);

	sf::Vector2f goalPos = *goalNode->getPosition();
	m_GameObjects.push_back(new Goal(goalPos));
	Pathfinder::getInstance()->calculateHValues(goalNode);

	GridNode* aiNode = GridManager::getInstance()->getNode(std::rand() % gridSize);
	sf::Vector2f aiPos = *aiNode->getPosition();
	while (aiPos == goalPos || !aiNode->getIsWalkable()){
		aiNode = GridManager::getInstance()->getNode(std::rand() % gridSize);
		aiPos = *aiNode->getPosition();
	}
	m_GameObjects.push_back(new AI(aiPos, goalPos));
}

void Game::createSurrondingWalls(){
	sf::Vector2f nodeSize = GridManager::getInstance()->getGridNodeSize();
	sf::Vector2f gridSize = GridManager::getInstance()->getGridSize2f();
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
	sf::Vector2f gridSize = GridManager::getInstance()->getGridSize2f();
	sf::Vector2f pxGridSize = sf::Vector2f(gridSize.x * 25, gridSize.y * 25);

	const int maxWallSize = 800;
	int currentWallSize = 0;
	int wallCount = 0;

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

		wallCount++;
		m_GameObjects.push_back(new Wall(pos, width, height));
	}
}

void Game::updateDeltaTime(){
	sf::Time nowTime = m_Clock.getElapsedTime();
	m_DeltaTime = nowTime.asMilliseconds() - m_LastTime.asMilliseconds();
	m_LastTime = nowTime;

	m_DTimerText.setString(std::to_string(m_DeltaTime));
	m_DTimerText.setPosition(GraphicManager::getInstance()->getWindow()->getSize().x - m_DTimerText.getLocalBounds().width, 0);
}