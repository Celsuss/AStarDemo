#include "Pathfinder.h"
#include "SFML/System/Clock.hpp"
#include "TextureManager.h"
#include "Cell.h"
#include <iostream>

Pathfinder* Pathfinder::m_Instance = new Pathfinder();

Pathfinder::Pathfinder(){}

Pathfinder::~Pathfinder(){}

Pathfinder* Pathfinder::getInstance(){
	if (!m_Instance)
		m_Instance = new Pathfinder();
	return m_Instance;
}

// Calculates the path to the goal from the AI using the A* algorithm.
// Returns a sf::vector2f vector where all elements represent the
// position of a Cell.
Pathfinder::PositionVector Pathfinder::getPath(sf::Vector2f startPos, sf::Vector2f endPos){
	sf::Clock clock;
	Cell* endCell = GridManager::getInstance()->getCell(endPos);
	GridManager::CellVector openList;
	GridManager::CellVector closedList;
	openList.push_back(GridManager::getInstance()->getCell(startPos));
	sf::Vector2f gridPos(*openList.back()->getGridPosition());

	while ((closedList.empty() || closedList.back() != endCell) && !openList.empty()){
		Cell* currentCell = getCellWithLowestFValue(&openList);
		closedList.push_back(currentCell);

		int cellIndex = closedList.back()->getIndex();
		int index = closedList.back()->getIndex();
		index -= GridManager::getInstance()->getGridSize2f().x + 1;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (indexIsInsideGrid(index)){
					Cell* cell = GridManager::getInstance()->getCell(index);
					if (cell->getIsWalkable() && !vectorContains(&closedList, cell)){
						if (!vectorContains(&openList, cell)){
							cell->setParentCell(closedList.back());
							cell->setGCost(calculateGValue(cell, i, j));
							openList.push_back(cell);
							cell->setSpriteTexture(TextureManager::getInstance()->getTexture("Grid_B"));
						}
						else{
							int gCost = calculateGValue(cell, i, j);
							if (gCost < cell->getGCost()){
								cell->setParentCell(closedList.back());
								cell->setGCost(gCost);
							}
						}
					}
					index++;
				}
			}
			index += GridManager::getInstance()->getGridSize2f().x - 3;
		}
	}

	PositionVector* path = getPath(endCell);

	int ms = clock.getElapsedTime().asMilliseconds();
	std::cout << "Pathfinding took " << ms << "ms" << std::endl;

	GridManager::getInstance()->clearValues();
	return *path;
}

// Calculates the H values of every Cell
void Pathfinder::calculateHValues(Cell* pEndCell){
	GridManager::CellVector* cells = GridManager::getInstance()->getCellVector();
	for (auto it : *cells){
		it->setHCost(calculateHValue(it, pEndCell));
	}
}

// Finds the cell with the lowest F value in the open list and returns the cell
Cell* Pathfinder::getCellWithLowestFValue(GridManager::CellVector* pOpenList){
	Cell* returnCell = *pOpenList->begin();
	float currentFCost = returnCell->getFCost();

	auto save = std::begin(*pOpenList);
	auto it = std::begin(*pOpenList);
	for (; it != std::end(*pOpenList); it++){
		if (currentFCost > (*it)->getFCost()){
			returnCell = (*it);
			currentFCost = returnCell->getFCost();
			save = it;
		}
	}
	it--;

	pOpenList->erase(save);
	return returnCell;
}

// Finds the cell with the lowest F value in the open list and returns the cell iterator
GridManager::CellVector::iterator Pathfinder::getIteratorWithlowestFCost(GridManager::CellVector* pOpenList){
	auto returnIterator = pOpenList->begin();
	float currentFCost = (*returnIterator)->getFCost();

	for (auto it = pOpenList->begin(); *it != pOpenList->back(); it++){
		if (currentFCost > (*it)->getFCost()){
			returnIterator = it;
			currentFCost = (*it)->getFCost();
		}
	}
	return returnIterator;
}

// Returns true if the current cell is in the closed list
bool Pathfinder::vectorContains(GridManager::CellVector* pVector, Cell* pCell){
	if (pVector->empty())
		return false;

	for (auto it : *pVector){
		if (it == pCell)
			return true;
	}
	return false;
}

// Calculates the G value of a cell.
// The G value is the move cost to move to this cell.
float Pathfinder::calculateGValue(Cell* pCell, int i, int j){
	float gCost = 10;
	if (i != 1 && j != 1)
		gCost = 14;

	return gCost + pCell->getParentCell()->getGCost();
}

// Calculates the H value of a cell.
// The H value is the estimated move cost to move to the
// goal cell.
float Pathfinder::calculateHValue(Cell* pCurrentCell, Cell* pEndCell){
	sf::Vector2f neighborGridPos = *pCurrentCell->getGridPosition();
	sf::Vector2f targetGridPos = *pEndCell->getGridPosition();

	float hCost = (std::abs(targetGridPos.x - neighborGridPos.x) + std::abs(targetGridPos.y - neighborGridPos.y))*10;
	return hCost;
}

// Checks if the index inside the grid.
// If it is, return true else return false
bool Pathfinder::indexIsInsideGrid(int index){
	int size = GridManager::getInstance()->getGridSize2f().x * GridManager::getInstance()->getGridSize2f().y;
	if (index >= size || index < 0)
		return false;
	return true;
}

// Returns the PositionVector to the endCells
Pathfinder::PositionVector* Pathfinder::getPath(Cell* pEndCell){
	PositionVector* path = new PositionVector;
	Cell* cell = pEndCell;
	while (cell != nullptr){
		path->push_back(cell->getPosition());
		cell = cell->getParentCell();
	}
	return path;
}