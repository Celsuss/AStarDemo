#pragma once
#include "SFML/System/Vector2.hpp"
#include "GridManager.h"

class Pathfinder{
public:
	typedef std::vector<sf::Vector2f*>PositionVector;

	static Pathfinder* getInstance();
	PositionVector getPath(sf::Vector2f startPos, sf::Vector2f endPos);
	void calculateHValues(GridNode* endNode);
private:
	Pathfinder();
	~Pathfinder();
	static Pathfinder* m_Instance;

	GridNode* getNodeWithLowestFValue(GridManager::GridNodeVector* openList);
	GridManager::GridNodeVector::iterator getIteratorWithlowestFCost(GridManager::GridNodeVector* openList);
	bool vectorContains(GridManager::GridNodeVector* vector, GridNode* node);
	float calculateGValue(GridNode* node, int i, int j);
	float calculateHValue(GridNode* currentNode, GridNode* endNode);
	bool indexIsInsideGrid(int index);
	PositionVector* getPath(GridNode* endNode);
};