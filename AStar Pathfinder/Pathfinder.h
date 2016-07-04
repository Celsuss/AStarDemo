#pragma once
#include "SFML/System/Vector2.hpp"
#include "GridManager.h"

class Pathfinder{
public:
	typedef std::vector<sf::Vector2f*>PositionVector;

	static Pathfinder* getInstance();
	PositionVector getPath(sf::Vector2f startPos, sf::Vector2f endPos);
	void calculateHValues(Cell* pEndCell);
private:
	Pathfinder();
	~Pathfinder();
	static Pathfinder* m_Instance;

	Cell* getCellWithLowestFValue(GridManager::CellVector* pOpenList);
	GridManager::CellVector::iterator getIteratorWithlowestFCost(GridManager::CellVector* pOpenList);
	bool vectorContains(GridManager::CellVector* pVector, Cell* pCell);
	float calculateGValue(Cell* pCell, int i, int j);
	float calculateHValue(Cell* pCurrentCell, Cell* pEndCell);
	bool indexIsInsideGrid(int index);
	PositionVector* getPath(Cell* pEndCell);
};