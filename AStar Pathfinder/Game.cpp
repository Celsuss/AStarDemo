#include "Game.h"
#include "AI.h"
#include "Wall.h"
#include "Goal.h"
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
	sf::Vector2f pos = sf::Vector2f(25, 25);
	int width = GraphicManager::getWindow()->getSize().x - 50;
	int height = 25;
	m_GameObjects.push_back(new Wall(pos, width, height));

	pos.y = 50;
	width = 25;
	height = GraphicManager::getWindow()->getSize().y - 100;
	m_GameObjects.push_back(new Wall(pos, width, height));

	pos.y = GraphicManager::getWindow()->getSize().y - 50;
	width = GraphicManager::getWindow()->getSize().x - 50;
	height = 25;
	m_GameObjects.push_back(new Wall(pos, width, height));

	pos.x = GraphicManager::getWindow()->getSize().x - 50;
	pos.y = 25;
	width = 25;
	height = GraphicManager::getWindow()->getSize().y - 50;
	m_GameObjects.push_back(new Wall(pos, width, height));

	pos.x = (GraphicManager::getWindow()->getSize().x / 2) - 25;
	pos.y = 100;
	width = 25;
	height = GraphicManager::getWindow()->getSize().y - 200;
	m_GameObjects.push_back(new Wall(pos, width, height));
}