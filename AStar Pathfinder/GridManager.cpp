#include "GridManager.h"
#include "GraphicManager.h"
#include "GameObject.h"
#include "GridNode.h"
#include "Game.h"
#include "Wall.h"
#include <time.h>

GridManager* GridManager::m_Instance = new GridManager();

GridManager::GridManager(){}

GridManager::~GridManager(){}

GridManager* GridManager::getInstance(){
	return m_Instance;
}

void GridManager::initialize(Game* pGame){
	srand(time(NULL));
	sf::Vector2f startPos = sf::Vector2f(25, 25);
	sf::Vector2f endPos = (sf::Vector2f)GraphicManager::getWindow()->getSize() - sf::Vector2f(25, 25);
	sf::Vector2f gridPos(0, 0);

	GridNode* gridNode = new GridNode(startPos, gridPos);
	int gridNodeRadie = gridNode->getSprite()->getLocalBounds().height;
	int matrixRows = (endPos.y - startPos.y) / gridNodeRadie;
	int matrixColumms = (endPos.x - startPos.x) / gridNodeRadie;
	delete gridNode;

	getInstance()->m_GridTileMatrix.resize(matrixRows);

	sf::Vector2f pos = startPos;
	for (int i = 0; i < getInstance()->m_GridTileMatrix.size(); i++){
		gridPos.x = 0;
		for (int j = 0; j < matrixColumms; j++){
			getInstance()->m_GridTileMatrix[i].push_back(new GridNode(pos, gridPos));
			gridPos.x++;
			pos.x += gridNodeRadie;
		}
		pos.y += gridNodeRadie;
		pos.x = startPos.x;
		gridPos.y++;
	}

	getInstance()->m_GridSize = new sf::Vector2f(gridPos);
	getInstance()->setNodesIsWalkable(pGame);
}

void GridManager::update(){
	getInstance()->draw();
}

void GridManager::clearValues(){
	for (int i = 0; i < getInstance()->m_GridTileMatrix.size(); i++){
		for (int j = 0; j < getInstance()->m_GridTileMatrix[i].size(); j++){
			getInstance()->m_GridTileMatrix[i][j]->clearValues();
		}
	}
}

GridNode* GridManager::getRandomNode(){
	int matrixHeight = getInstance()->m_GridTileMatrix.size()-1;
	int matrixWidth = getInstance()->m_GridTileMatrix.back().size()-1;
	int r1 = rand() % (100 * matrixHeight);
	int r2 = rand() % (100 * matrixWidth);
	r1 /= 100;
	r2 /= 100;
	
	return getInstance()->m_GridTileMatrix[r1][r2];
}

GridNode* GridManager::getRandomNodeWithinRange(sf::Vector2f pos, int range){
	GridNode* nearestNode = getNode(pos);
	int matrixHeight = getInstance()->m_GridTileMatrix.size() - 1;
	int matrixWidth = getInstance()->m_GridTileMatrix.back().size() - 1;

	int rangeTop = nearestNode->getGridPosition()->y - (range / 2);
	int rangeBottom = nearestNode->getGridPosition()->y + (range / 2);
	int rangeLeft = nearestNode->getGridPosition()->x - (range / 2);
	int rangeRight = nearestNode->getGridPosition()->x + (range / 2);

	int gridTop = getInstance()->m_GridTileMatrix[rangeTop > 0 ? rangeTop : 0].back()->getGridPosition()->y;
	int gridBottom = getInstance()->m_GridTileMatrix[rangeBottom < matrixHeight ? rangeBottom : matrixHeight].back()->getGridPosition()->y;
	int gridLeft = getInstance()->m_GridTileMatrix.back()[rangeLeft > 0 ? rangeLeft : 0]->getGridPosition()->x;
	int gridRight = getInstance()->m_GridTileMatrix.back()[rangeRight < matrixWidth ? rangeRight : matrixWidth]->getGridPosition()->x;

	int r1 = rand() % (100 * range) / 100;
	int r2 = rand() % (100 * range) / 100;

	return getInstance()->m_GridTileMatrix[gridTop + r1][gridLeft + r2];
}

GridNode* GridManager::getNode(sf::Vector2f pos){
	GridNode* nearestNode = nullptr;
	float x0 = pos.x;
	float y0 = pos.y;
	float distance = 100000;

	for (int i = 0; i < getInstance()->m_GridTileMatrix.size(); i++){
		for (auto j = getInstance()->m_GridTileMatrix[i].begin(); j != getInstance()->m_GridTileMatrix[i].end(); j++){
			float x1 = (*j)->getPosition()->x;
			float y1 = (*j)->getPosition()->y;
			
			float dx = x1 - x0;
			float dy = y1 - y0;
			float length = std::sqrt((dx*dx) + (dy*dy));
			if (distance > length){
				distance = length;
				nearestNode = (*j);
			}
		}
	}

	return nearestNode;
}

GridNode* GridManager::getMatrixNode(sf::Vector2f gridPos){
	return getInstance()->m_GridTileMatrix[gridPos.y][gridPos.x];
}

sf::Vector2f* GridManager::getGridSize(){
	return getInstance()->m_GridSize;
}

void GridManager::draw(){
	for (int i = 0; i < m_GridTileMatrix.size(); i++){
		for (int j = 0; j < m_GridTileMatrix[i].size(); j++){
			m_GridTileMatrix[i][j]->draw();
		}
	}
}

void GridManager::setNodesIsWalkable(Game* pGame){
	Game::GameObjectVector* objects = pGame->getGameObjects();;
	for (int i = 0; i < getInstance()->m_GridTileMatrix.size(); i++){
		for (int j = 0; j < getInstance()->m_GridTileMatrix[i].size(); j++){
			if (j == getInstance()->m_GridTileMatrix[i].size() - 1){
				if (i == 2)
					int kalle = 0;
			}

			for (auto it = objects->begin(); it != objects->end(); it++){
				if ((*it)->getGameObjectType() == GameObject::Type::Wall){
					if (getInstance()->getWallNodeCollision(getInstance()->m_GridTileMatrix[i][j], (Wall*)*it)){
						getInstance()->m_GridTileMatrix[i][j]->setIsWalkable(false);
					}
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
	int x2Max = x2Min + pWall->getShape()->getLocalBounds().width - (wallMinusSize*2);
	int y2Min = pWall->getPosition()->y + wallMinusSize;
	int y2Max = y2Min + pWall->getShape()->getLocalBounds().height - (wallMinusSize*2);

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	if (y1Min > 4 * 25 && x1Min == 25 * 25){
		int kalle = 0;
	}

	return true;
}