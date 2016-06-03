#include "Game.h"
#include "SFML/System.hpp"
#include "GraphicManager.h"

Game::Game(){}

Game::~Game(){}

void Game::run(){
	update();
}

void Game::update(){
	GraphicManager::initialize();

	while (GraphicManager::getWindow()->isOpen()){
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
		GraphicManager::update();
		//----
	}
}

void Game::handleEvents(){
	sf::Event event;
	while (GraphicManager::getWindow()->pollEvent(event)){
		if (event.type == sf::Event::Closed)
			GraphicManager::getWindow()->close();
	}
}