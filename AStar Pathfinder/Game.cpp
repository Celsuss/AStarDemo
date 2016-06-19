#include "Game.h"
#include "AI.h"
#include "Wall.h"
#include "Goal.h"
#include "GridNode.h"
#include "GameObject.h"
#include "GridManager.h"
#include "SFML/System.hpp"
#include "GraphicManager.h"

Game::Game(){}

Game::~Game(){}

void Game::run(){
	update();
}

void Game::update(){
	GraphicManager::initialize();
	GridManager::initialize(this);
	createWalls();
	GridManager::setNodesIsWalkable(this);
	m_GameObjects.push_back(new Goal(sf::Vector2f((sf::Vector2f)GraphicManager::getWindow()->getSize() - sf::Vector2f(150, 150))));
	m_GameObjects.push_back(new AI(sf::Vector2f(150, 150), *getGoal()->getPosition()));

	while (GraphicManager::getWindow()->isOpen()){
		handleEvents();
		handleInput();

		//----
		//Debug::clear();
		//Time
		//TimeManager::update();
		//User input
		//InputManager::update();
		//Update game state
		//Render
		//Debug::update();
		GridManager::update();
		
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++){
			(*it)->draw();
		}

		GraphicManager::update();
		//----
	}
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
	while (GraphicManager::getWindow()->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			GraphicManager::getWindow()->close();
	}
}

void Game::handleInput(){

}

void Game::createWalls(){
	createSurrondingWalls();
	createRandomWalls();

	sf::Vector2f pos = sf::Vector2f((GraphicManager::getInstance()->getWindow()->getSize().x / 2) - 25,
									100);
	pos.y = 100;
	int width = 25;
	int height = GraphicManager::getInstance()->getWindow()->getSize().y - 200;
	m_GameObjects.push_back(new Wall(pos, width, height));
}

void Game::createSurrondingWalls(){
	sf::Vector2f nodeSize = GridManager::getGridNodeSize();
	sf::Vector2f gridSize = *GridManager::getGridSize();
	sf::Vector2f node = sf::Vector2f(0, 0);
	sf::Vector2f startPos = *GridManager::getMatrixNode(node)->getPosition();

	sf::Vector2f pos = startPos;
	node = sf::Vector2f(gridSize.x - 1, 0);
	int width = GridManager::getMatrixNode(node)->getPosition()->x;
	int height = nodeSize.y;
	m_GameObjects.push_back(new Wall(pos, width, height));

	node = sf::Vector2f(gridSize.x - 1, 1);
	pos = *GridManager::getMatrixNode(node)->getPosition();
	node = sf::Vector2f(gridSize.x - 1, gridSize.y - 1);
	width = nodeSize.x;
	height = GridManager::getMatrixNode(node)->getPosition()->y - nodeSize.y - startPos.y;
	m_GameObjects.push_back(new Wall(pos, width, height));

	node = sf::Vector2f(0, gridSize.y - 1);
	pos = *GridManager::getMatrixNode(node)->getPosition();
	node = sf::Vector2f(gridSize.x - 1, gridSize.y - 1);
	width = GridManager::getMatrixNode(node)->getPosition()->x;
	height = nodeSize.y;
	m_GameObjects.push_back(new Wall(pos, width, height));

	node = sf::Vector2f(0, 1);
	pos = *GridManager::getMatrixNode(node)->getPosition();
	node = sf::Vector2f(0, gridSize.y - 1);
	width = nodeSize.x;
	height = GridManager::getMatrixNode(node)->getPosition()->y - nodeSize.y - startPos.y;
	m_GameObjects.push_back(new Wall(pos, width, height));
}

void Game::createRandomWalls(){
	sf::Vector2f nodeSize = GridManager::getGridNodeSize();
	sf::Vector2f gridSize = *GridManager::getGridSize();
	sf::Vector2f pxGridSize = sf::Vector2f(gridSize.x * 25, gridSize.y * 25);

	int wallCount = (rand() % 300 + 100) / 100;
	for (int i = 0; i < wallCount; i++){
		sf::Vector2f pos = *GridManager::getRandomNode()->getPosition();
		int width = 0;
		int height = 0;

		if (rand() % 100 < 50){
			width = 25;
			height = rand() % (int)pxGridSize.y;

			if (pos.y + height >= pxGridSize.y)
				height = pxGridSize.y - pos.y;

			int leftOver = height % (int)nodeSize.y;
			height -= height % (int)nodeSize.y;
			if (width % 25 != 0)
				int kalle = 0;
		}
		else{
			width = rand() % (int)pxGridSize.x;
			height = 25;

			if (pos.x + width >= pxGridSize.x)
				width = pxGridSize.x - pos.x;

			int leftOver = width % (int)nodeSize.x;
			width -= width % (int)nodeSize.x;
			if (width % 25 != 0)
				int kalle = 0;
		}

		m_GameObjects.push_back(new Wall(pos, width, height));
	}
}