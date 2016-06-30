#include "GridManager.h"
#include "GraphicManager.h"
#include "GameObject.h"
#include "GridNode.h"
#include "Game.h"
#include "Wall.h"
#include <iostream>
#include <time.h>

GridManager* GridManager::m_Instance = new GridManager();

GridManager::GridManager(){}

GridManager::~GridManager(){}

GridManager* GridManager::getInstance(){
	return m_Instance;
}

void GridManager::initialize(){
	srand(time(NULL));
	sf::Vector2f startPos = sf::Vector2f(25, 40);
	sf::Vector2f endPos = (sf::Vector2f)GraphicManager::getInstance()->getWindow()->getSize() - sf::Vector2f(25, 10);
	sf::Vector2f gridPos(0, 0);

	GridNode* gridNode = new GridNode(startPos, gridPos, 0);
	int gridNodeRadie = gridNode->getSprite()->getLocalBounds().height;
	int matrixRows = (endPos.y - startPos.y) / gridNodeRadie;
	int matrixColumms = (endPos.x - startPos.x) / gridNodeRadie;
	delete gridNode;

	sf::Vector2f pos = startPos;
	int index = 0;
	for (int i = 0; i < matrixRows; i++){
		gridPos.x = 0;
		for (int j = 0; j < matrixColumms; j++){
			m_GridTiles.push_back(new GridNode(pos, gridPos, index));
			gridPos.x++;
			index++;
			pos.x += gridNodeRadie;
		}
		pos.y += gridNodeRadie;
		pos.x = startPos.x;
		gridPos.y++;
	}

	m_GridSize = sf::Vector2f(gridPos);
}

void GridManager::update(){
	draw();
}

void GridManager::clearValues(){
	for (auto it : m_GridTiles) {
		it->clearValues();
	}
}

GridNode* GridManager::getRandomNode(){
	return m_GridTiles[rand() % (m_GridTiles.size()-1)];
}

GridNode* GridManager::getRandomWalkableNode(){
	GridNode* node = m_GridTiles[rand() % (m_GridTiles.size() - 1)];
	while (!node->getIsWalkable()){
		node = m_GridTiles[rand() % (m_GridTiles.size() - 1)];
	}
	return node;
}

GridNode* GridManager::getNode(int index){
	return m_GridTiles[index];
}

GridNode* GridManager::getNode(sf::Vector2f pos){
	GridNode* nearestNode = nullptr;
	float x0 = pos.x;
	float y0 = pos.y;
	float distance = 100000;

	for (auto it : m_GridTiles){
		float x1 = it->getPosition()->x;
		float y1 = it->getPosition()->y;
		
		float dx = x1 - x0;
		float dy = y1 - y0;
		float length = std::sqrt((dx*dx) + (dy*dy));
		if (distance > length){
			distance = length;
			nearestNode = it;
		}
	}

	return nearestNode;
}

GridNode* GridManager::getMatrixNode(sf::Vector2f gridPos){
	return m_GridTiles[(gridPos.y * m_GridSize.x) + gridPos.x];
}

GridManager::GridNodeVector* GridManager::getNodeVector(){
	return &m_GridTiles;
}

float GridManager::getGridSize(){
	return m_GridTiles.size();
}

sf::Vector2f& GridManager::getGridSize2f(){
	return m_GridSize;
}

sf::Vector2f& GridManager::getGridNodeSize(){
	if (m_GridTiles.empty())
		return sf::Vector2f(0, 0);
	return sf::Vector2f(m_GridTiles[0]->getSprite()->getLocalBounds().width,
						m_GridTiles[0]->getSprite()->getLocalBounds().height);
}

void GridManager::draw(){
	for (auto it : m_GridTiles)
		it->draw();
}

void GridManager::setNodesIsWalkable(Game* pGame){
	int unwalkableNodeCount = 0;
	Game::GameObjectVector* objects = pGame->getGameObjects();

	for (auto it : m_GridTiles){
		it->setIsWalkable(true);
		for (auto it2 : *objects){
			if (it2->getGameObjectType() == GameObject::Type::Wall){
				if (getWallNodeCollision(it, (Wall*)it2)){
					it->setIsWalkable(false);
					unwalkableNodeCount++;
				}
			}
		}
	}
}

bool GridManager::getWallNodeCollision(GridNode* pNode, Wall* pWall){
	int hight1 = pNode->getSprite()->getLocalBounds().height;

	int x1Min = pNode->getPosition()->x;
	int x1Max = x1Min + pNode->getSprite()->getLocalBounds().width;
	int y1Min = pNode->getPosition()->y;
	int y1Max = y1Min + pNode->getSprite()->getLocalBounds().height;

	int wallMinusSize = 5;
	int x2Min = pWall->getPosition()->x + wallMinusSize;
	int x2Max = x2Min + pWall->getShape()->getLocalBounds().width - (wallMinusSize * 2);
	int y2Min = pWall->getPosition()->y + wallMinusSize;
	int y2Max = y2Min + pWall->getShape()->getLocalBounds().height - (wallMinusSize * 2);

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	if (y1Min > 4 * 25 && x1Min == 25 * 25){
		int kalle = 0;
	}

	return true;
}