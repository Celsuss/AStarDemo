#include "MazeGenerator.h"
#include "SFML/System/Clock.hpp"
#include "Cell.h"
#include <iostream>
#include <random>
#include <stack>

MazeGenerator* MazeGenerator::m_Instance = new MazeGenerator();

MazeGenerator::MazeGenerator(){}

MazeGenerator::~MazeGenerator(){}

MazeGenerator* MazeGenerator::getInstance(){
	return m_Instance;
}

// Start creating the maze
void MazeGenerator::createMaze(){
	sf::Clock clock;
	GridManager::CellVector& cells = *GridManager::getInstance()->getCellVector();

	for (auto it : cells)
		it->setIsWalkable(false);

	const int sizeX = (int)GridManager::getInstance()->getGridSize2f().x;
	const int sizeY = (int)GridManager::getInstance()->getGridSize2f().y;
	const int posX = std::rand() % sizeX;
	const int posY = std::rand() % (int)GridManager::getInstance()->getGridSize2f().y;
	cells[posX + (posY * sizeX)]->setIsWalkable(true);
	buildMaze(sf::Vector2i(posX, posY), cells);

	const int ms = clock.getElapsedTime().asMilliseconds();
	std::cout << "Pathfinding took " << ms << "ms" << std::endl;
}

// Builds the maze
void MazeGenerator::buildMaze(sf::Vector2i pos, GridManager::CellVector& cells){
	Direction dir = (Direction)(std::rand() % 4);
	DirectionVector cantGo;
	sf::Vector2i size = (sf::Vector2i)GridManager::getInstance()->getGridSize2f();
	int posIndex = pos.x + (pos.y * size.x);

	while (dir != Direction::Invalid){
		switch (dir)
		{
		case MazeGenerator::Up:
			posIndex = pos.x + ((pos.y - 2) * size.x);
			if (pos.y - 2 > 0 && !cells[pos.x + ((pos.y - 2) * size.x)]->getIsWalkable()){
				cells[pos.x + ((pos.y - 1) * size.x)]->setIsWalkable(true);
				cells[pos.x + ((pos.y - 2) * size.x)]->setIsWalkable(true);
				pos.y = pos.y - 2;
				buildMaze(pos, cells);
			}
			else
				cantGo.push_back(dir);
			break;
		case MazeGenerator::Right:
			posIndex = (pos.x + 2) + (pos.y * size.x);
			if (pos.x + 2 < size.x && !cells[pos.x + 2 + (pos.y * size.x)]->getIsWalkable()){
				cells[(pos.x + 1) + (pos.y * size.x)]->setIsWalkable(true);
				cells[(pos.x + 2) + (pos.y * size.x)]->setIsWalkable(true);
				pos.x = pos.x + 2;
				buildMaze(pos, cells);
			}
			else
				cantGo.push_back(dir);
			break;
		case MazeGenerator::Down:
			posIndex = pos.x + ((pos.y + 2) * size.x);
			if (pos.y + 2 < size.y && !cells[pos.x + (pos.y + 2 * size.x)]->getIsWalkable()){
				cells[pos.x + ((pos.y + 1) * size.x)]->setIsWalkable(true);
				cells[pos.x + ((pos.y + 2) * size.x)]->setIsWalkable(true);
				pos.y = pos.y + 2;
				buildMaze(pos, cells);
			}
			else
				cantGo.push_back(dir);
			break;
		case MazeGenerator::Left:
			posIndex = (pos.x - 2) + (pos.y * size.x);
			if (pos.x - 2 > 0 && !cells[pos.x - 2 + (pos.y * size.x)]->getIsWalkable()){
				cells[(pos.x - 1) + (pos.y * size.x)]->setIsWalkable(true);
				cells[(pos.x - 2) + (pos.y * size.x)]->setIsWalkable(true);
				pos.x = pos.x - 2;
				buildMaze(pos, cells);
			}
			else
				cantGo.push_back(dir);
			break;
		}

		if (cantGo.size() == 4){
			dir = Invalid;
		}
		else{
			dir = (Direction)(std::rand() % 4);
			while (vectorContains(dir, cantGo))
				dir = (Direction)(std::rand() % 4);
		}
	}
}

// Returns true if directions contain dir
bool MazeGenerator::vectorContains(const Direction& dir, const DirectionVector& directions) const {
	for (auto it : directions)
		if (it == dir)
			return true;
	return false;
}