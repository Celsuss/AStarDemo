#pragma once
#include "SFML/System/Vector2.hpp"
#include "GridManager.h"

class Pathfinder{
public:
	typedef std::vector<sf::Vector2f*>PositionVector;

	static Pathfinder* getInstance();
	//PositionVector findPath(sf::Vector2f startPos, sf::Vector2f endPos);
	PositionVector getPath(sf::Vector2f startPos, sf::Vector2f endPos);
private:
	Pathfinder();
	~Pathfinder();
	static Pathfinder* m_Instance;

	GridNode* getNodeWithLowestFCost(GridManager::GridNodeVector* openList);
	GridManager::GridNodeVector::iterator getIteratorWithlowestFCost(GridManager::GridNodeVector* openList);
	bool isInClosedList(GridManager::GridNodeVector* closedList, GridNode* currentNode);
	bool isInOpenList(GridManager::GridNodeVector* openList, GridNode* currentNode);
	float calculateGCost(int i, int j, GridManager::GridNodeVector* closedList);
	float calculateHCost(GridNode* neighborNode, GridNode* endNode);
};