#include "Pathfinder.h"
#include "SFML/System/Clock.hpp"
#include "TextureManager.h"
#include "GridNode.h"
#include <iostream>

Pathfinder* Pathfinder::m_Instance = new Pathfinder();

Pathfinder::Pathfinder(){}

Pathfinder::~Pathfinder(){}

Pathfinder* Pathfinder::getInstance(){
	return m_Instance;
}

// Calculates the path to the goal from the AI using the A* algorithm.
// Returns a sf::vector2f vector where all elements represent the
// position of a GridNode.
Pathfinder::PositionVector Pathfinder::getPath(sf::Vector2f startPos, sf::Vector2f endPos){
	sf::Clock clock;
	GridNode* endNode = GridManager::getInstance()->getNode(endPos);
	GridManager::GridNodeVector openList;
	GridManager::GridNodeVector closedList;
	openList.push_back(GridManager::getInstance()->getNode(startPos));
	sf::Vector2f gridPos(*openList.back()->getGridPosition());

	while ((closedList.empty() || closedList.back() != endNode) && !openList.empty()){
		GridNode* currentNode = getNodeWithLowestFValue(&openList);
		closedList.push_back(currentNode);

		int nodeIndex = closedList.back()->getIndex();
		int index = closedList.back()->getIndex();
		index -= GridManager::getInstance()->getGridSize2f().x + 1;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (indexIsInsideGrid(index)){
					GridNode* node = GridManager::getInstance()->getNode(index);
					if (node->getIsWalkable() && !vectorContains(&closedList, node)){
						if (!vectorContains(&openList, node)){
							node->setParentNode(closedList.back());
							node->setGCost(calculateGValue(node, i, j));
							openList.push_back(node);
							node->setSpriteTexture(TextureManager::getInstance()->getTexture("Grid_B"));
						}
						else{
							int gCost = calculateGValue(node, i, j);
							if (gCost < node->getGCost()){
								node->setParentNode(closedList.back());
								node->setGCost(gCost);
							}
						}
					}
					index++;
				}
			}
			index += GridManager::getInstance()->getGridSize2f().x - 3;
		}
	}

	PositionVector* path = getPath(endNode);

	int ms = clock.getElapsedTime().asMilliseconds();
	std::cout << "Pathfinding took " << ms << "ms" << std::endl;

	GridManager::getInstance()->clearValues();
	return *path;
}

// Calculates the H values of every GridNode
void Pathfinder::calculateHValues(GridNode* endNode){
	GridManager::GridNodeVector* nodes = GridManager::getInstance()->getNodeVector();
	for (auto it : *nodes){
		it->setHCost(calculateHValue(it, endNode));
	}
}

// Finds the node with the lowest F value in the open list and returns the node
GridNode* Pathfinder::getNodeWithLowestFValue(GridManager::GridNodeVector* openList){
	GridNode* returnNode = *openList->begin();
	float currentFCost = returnNode->getFCost();

	auto save = std::begin(*openList);
	auto it = std::begin(*openList);
	for (; it != std::end(*openList); it++){
		if (currentFCost > (*it)->getFCost()){
			returnNode = (*it);
			currentFCost = returnNode->getFCost();
			save = it;
		}
	}
	it--;

	openList->erase(save);
	return returnNode;
}

// Finds the node with the lowest F value in the open list and returns the node iterator
GridManager::GridNodeVector::iterator Pathfinder::getIteratorWithlowestFCost(GridManager::GridNodeVector* openList){
	auto returnIterator = openList->begin();
	float currentFCost = (*returnIterator)->getFCost();

	for (auto it = openList->begin(); *it != openList->back(); it++){
		if (currentFCost > (*it)->getFCost()){
			returnIterator = it;
			currentFCost = (*it)->getFCost();
		}
	}
	return returnIterator;
}

// Returns true if the current node is in the closed list
bool Pathfinder::vectorContains(GridManager::GridNodeVector* vector, GridNode* node){
	if (vector->empty())
		return false;

	for (auto it : *vector){
		/*if (it->getGridPosition() == node->getGridPosition())
			return true;*/
		if (it == node)
			return true;
	}
	return false;
}

// Calculates the G value of a node.
// The G value is the move cost to move to this node.
float Pathfinder::calculateGValue(GridNode* node, int i, int j){
	float gCost = 10;
	if (i != 1 && j != 1)
		gCost = 14;

	return gCost + node->getParentNode()->getGCost();
}

// Calculates the H value of a node.
// The H value is the estimated move cost to move to the
// goal node.
float Pathfinder::calculateHValue(GridNode* currentNode, GridNode* endNode){
	sf::Vector2f neighborGridPos = *currentNode->getGridPosition();
	sf::Vector2f targetGridPos = *endNode->getGridPosition();

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

// Returns the PositionVector to the endNodes
Pathfinder::PositionVector* Pathfinder::getPath(GridNode* endNode){
	PositionVector* path = new PositionVector;
	GridNode* node = endNode;
	while (node != nullptr){
		path->push_back(node->getPosition());
		node = node->getParentNode();
	}
	return path;
}