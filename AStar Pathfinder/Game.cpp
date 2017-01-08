#include "Game.h"
#include "AI.h"
#include "Goal.h"
#include "Cell.h"
#include "GameObject.h"
#include "GridManager.h"
#include "SFML/System.hpp"
#include "MazeGenerator.h"
#include "GraphicManager.h"
#include <iostream>

bool Game::m_Debug = false;

Game::Game(){
	m_Restart = false;
}

Game::~Game(){}

// Start the game
void Game::run(){
	update();
}

// Updates the program and all game objects
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

// Initialize the program
void Game::initialize(){
	std::cout << "Initializing game" << std::endl;
	if (!m_GameObjects.empty())
		deleteGameObjects();
	MazeGenerator::getInstance()->createMaze();
	createAIAndGoal();
	std::cout << "Initializing game done" << std::endl;
}

// Initialize the text and delta timer text
void Game::initializeText(){
	m_Text.setFont(*GraphicManager::getInstance()->getFont());
	m_Text.setCharacterSize(24);
	m_Text.setFillColor(sf::Color::White);
	m_Text.setString("Press 'R' to restart, 'D' to show/hide debugging help");

	m_DTimerText.setFont(*GraphicManager::getInstance()->getFont());
	m_DTimerText.setCharacterSize(12);
	m_DTimerText.setFillColor(sf::Color::White);
	m_DTimerText.setString("0");
}

// Delete all the GameObjects
void Game::deleteGameObjects(){
	for (auto it : m_GameObjects)
		delete it;
	m_GameObjects.clear();
}

// Returns a pointer to the GameObject vector
Game::GameObjectVector* Game::getGameObjects(){
	return &m_GameObjects;
}

// Returns the Goal object
Goal* Game::getGoal() const {
	for (auto it : m_GameObjects){;
		if (it->getGameObjectType() == GameObject::Type::Goal){
			return (Goal*)it;
		}
	}
	return nullptr;
}

// Returns true if debugging is true else return false
bool Game::getDebugging(){
	return m_Debug;
}

// Handel events
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

// Create the AI and the Goal
void Game::createAIAndGoal(){
	int gridSize = GridManager::getInstance()->getGridSize() - 1;
	Cell* goalCell = GridManager::getInstance()->getCell(std::rand() % gridSize);
	while (!goalCell->getIsWalkable())
		goalCell = GridManager::getInstance()->getCell(std::rand() % gridSize);

	sf::Vector2f goalPos = *goalCell->getPosition();
	m_GameObjects.push_back(new Goal(goalPos));
	Pathfinder::getInstance()->calculateHValues(goalCell);

	Cell* aiCell = GridManager::getInstance()->getCell(std::rand() % gridSize);
	sf::Vector2f aiPos = *aiCell->getPosition();
	while (aiPos == goalPos || !aiCell->getIsWalkable()){
		aiCell = GridManager::getInstance()->getCell(std::rand() % gridSize);
		aiPos = *aiCell->getPosition();
	}
	m_GameObjects.push_back(new AI(aiPos, goalPos));
}

// Updates the delta time
void Game::updateDeltaTime(){
	sf::Time nowTime = m_Clock.getElapsedTime();
	m_DeltaTime = nowTime.asMilliseconds() - m_LastTime.asMilliseconds();
	m_LastTime = nowTime;

	m_DTimerText.setString(std::to_string(m_DeltaTime));
	m_DTimerText.setPosition(GraphicManager::getInstance()->getWindow()->getSize().x - m_DTimerText.getLocalBounds().width, 0);
}