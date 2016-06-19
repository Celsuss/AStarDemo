#include "Pathfinder.h"
#include "GridNode.h"
#include <iostream>

Pathfinder* Pathfinder::m_Instance = new Pathfinder();

Pathfinder::Pathfinder(){}

Pathfinder::~Pathfinder(){}

Pathfinder* Pathfinder::getInstance(){
	return m_Instance;
}

Pathfinder::PositionVector Pathfinder::findPath(sf::Vector2f startPos, sf::Vector2f endPos){
	return getInstance()->getPath(startPos, endPos);
}

Pathfinder::PositionVector Pathfinder::getPath(sf::Vector2f startPos, sf::Vector2f endPos){
	GridNode* endNode = GridManager::getNode(endPos);
	GridManager::GridNodeVector openList;
	GridManager::GridNodeVector closedList;
	openList.push_back(GridManager::getNode(startPos));
	sf::Vector2f gridPos(*openList.back()->getGridPosition());

	bool loop = true;
	int loopTurn = 0;

	while (loop){

		closedList.push_back(getNodeWithLowestFCost(&openList));
		auto eraseThis = getIteratorWithlowestFCost(&openList);
		openList.erase(getIteratorWithlowestFCost(&openList));
		gridPos = *closedList.back()->getGridPosition();

		if (closedList.back() == endNode && openList.size() > 0){
			loop = false;
			break;
		}

		int gridWidth = GridManager::getGridSize()->x - 1;
		int gridHeight = GridManager::getGridSize()->y - 1;

		for (int i = -1; i < 2; i++){
			for (int j = -1; j < 2; j++){
				sf::Vector2f neightborGridPos(closedList.back()->getGridPosition()->x + i, closedList.back()->getGridPosition()->y + j);
				if (neightborGridPos.x >= 0 && neightborGridPos.x <= gridWidth && neightborGridPos.y >= 0 && neightborGridPos.y <= gridHeight){
					GridNode* neighborNode = GridManager::getMatrixNode(neightborGridPos);
					if (!(i == 0 && j == 0) && neighborNode->isWalkable()){
						float gCost = calculateGCost(i, j, &closedList);
						float hCost = calculateHCost(neighborNode, endNode);

						if (isInClosedList(&closedList, neighborNode)){
						}
						else if (isInOpenList(&openList, neighborNode)){
							if (gCost < neighborNode->getGCost()){
								neighborNode->setGCost(gCost);
								neighborNode->setParentNode(closedList.back());
							}
						}
						else{
							openList.push_back(neighborNode);
							openList.back()->setGCost(gCost);
							openList.back()->setHCost(hCost);
							openList.back()->setParentNode(closedList.back());
						}
					}
				}
				gridPos.x++;
			}
			gridPos.y++;
		}
		loopTurn++;
	}

	PositionVector returnList;

	GridNode* startNode = GridManager::getNode(startPos);
	GridNode* returnNode = endNode;
	GridNode* prevNode = nullptr;
	loopTurn = 0;
	while (true){
		if (returnNode->getParentNode() != nullptr){
			returnList.push_back(returnNode->getPosition());
			prevNode = returnNode;
			returnNode = returnNode->getParentNode();
		}
		else
			break;
		loopTurn++;
	}

	GridManager::clearValues();
	return returnList;
}

GridNode* Pathfinder::getNodeWithLowestFCost(GridManager::GridNodeVector* openList){
	GridNode* returnNode = *openList->begin();;
	float currentFCost = 10000;

	for (auto i = openList->begin(); *i != openList->back(); i++){
		if (currentFCost > (*i)->getFCost()){
			returnNode = *i;
			currentFCost = returnNode->getFCost();
		}
	}
	return returnNode;
}

GridManager::GridNodeVector::iterator Pathfinder::getIteratorWithlowestFCost(GridManager::GridNodeVector* openList){
	auto returnIterator = openList->begin();
	float currentFCost = 10000;

	for (auto i = openList->begin(); *i != openList->back(); i++){
		if (currentFCost > (*i)->getFCost()){
			returnIterator = i;
			currentFCost = (*i)->getFCost();
		}
	}
	return returnIterator;
}

bool Pathfinder::isInClosedList(GridManager::GridNodeVector* closedList, GridNode* currentNode){
	if (closedList->size() == 0)
		return false;

	for (auto i = closedList->begin(); *i != closedList->back(); i++){
		if ((*i)->getGridPosition() == currentNode->getGridPosition())
			return true;
	}
	return false;
}

bool Pathfinder::isInOpenList(GridManager::GridNodeVector* openList, GridNode* currentNode){
	if (openList->size() == 0)
		return false;

	for (auto i = openList->begin(); *i != openList->back(); i++){
		if ((*i)->getGridPosition() == currentNode->getGridPosition())
			return true;
	}
	return false;
}

float Pathfinder::calculateGCost(int i, int j, GridManager::GridNodeVector* closedList){
	float gCost = 10;
	if ((i == 0 || i == 2) && (j == 0 || j == 2))
		gCost = 14;

	return gCost;
}

float Pathfinder::calculateHCost(GridNode* neighborNode, GridNode* endNode){
	sf::Vector2f neighborGridPos = *neighborNode->getGridPosition();
	sf::Vector2f targetGridPos = *endNode->getGridPosition();

	float hCost = (std::abs(targetGridPos.x - neighborGridPos.x) + std::abs(targetGridPos.y - neighborGridPos.y)) * 10;
	return hCost;
}