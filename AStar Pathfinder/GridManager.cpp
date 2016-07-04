#include "GridManager.h"
#include "GraphicManager.h"
#include "GameObject.h"
#include "Cell.h"
#include "Game.h"
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

	Cell* cell = new Cell(startPos, gridPos, 0);
	int CellRadie = cell->getSprite()->getLocalBounds().height;
	int matrixRows = (endPos.y - startPos.y) / CellRadie;
	int matrixColumms = (endPos.x - startPos.x) / CellRadie;
	delete cell;

	sf::Vector2f pos = startPos;
	int index = 0;
	for (int i = 0; i < matrixRows; i++){
		gridPos.x = 0;
		for (int j = 0; j < matrixColumms; j++){
			m_GridTiles.push_back(new Cell(pos, gridPos, index));
			gridPos.x++;
			index++;
			pos.x += CellRadie;
		}
		pos.y += CellRadie;
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

Cell* GridManager::getRandomCell(){
	return m_GridTiles[rand() % (m_GridTiles.size()-1)];
}

Cell* GridManager::getRandomWalkableCell(){
	Cell* cell = m_GridTiles[rand() % (m_GridTiles.size() - 1)];
	while (!cell->getIsWalkable()){
		cell = m_GridTiles[rand() % (m_GridTiles.size() - 1)];
	}
	return cell;
}

Cell* GridManager::getCell(int index){
	return m_GridTiles[index];
}

Cell* GridManager::getCell(sf::Vector2f pos){
	Cell* nearestCell = nullptr;
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
			nearestCell = it;
		}
	}

	return nearestCell;
}

Cell* GridManager::getMatrixCell(sf::Vector2f gridPos){
	return m_GridTiles[gridPos.x + (gridPos.y * m_GridSize.x)];
}

GridManager::CellVector* GridManager::getCellVector(){
	return &m_GridTiles;
}

float GridManager::getGridSize(){
	return m_GridTiles.size();
}

sf::Vector2f& GridManager::getGridSize2f(){
	return m_GridSize;
}

sf::Vector2f& GridManager::getCellSize(){
	if (m_GridTiles.empty())
		return sf::Vector2f(0, 0);
	return sf::Vector2f(m_GridTiles[0]->getSprite()->getLocalBounds().width,
						m_GridTiles[0]->getSprite()->getLocalBounds().height);
}

void GridManager::draw(){
	for (auto it : m_GridTiles)
		it->draw();
}