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

// Initialize the grid
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
			m_GridCells.push_back(new Cell(pos, gridPos, index));
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

// Update and call the draw function
void GridManager::update(){
	draw();
}

// Clear the values of all the cells
void GridManager::clearValues(){
	for (auto it : m_GridCells) {
		it->clearValues();
	}
}

// Returns a random cell
Cell* GridManager::getRandomCell() const{
	return m_GridCells[rand() % (m_GridCells.size() - 1)];
}

// Returns a random walkable cell
Cell* GridManager::getRandomWalkableCell() const {
	Cell* cell = m_GridCells[rand() % (m_GridCells.size() - 1)];
	while (!cell->getIsWalkable()){
		cell = m_GridCells[rand() % (m_GridCells.size() - 1)];
	}
	return cell;
}

// Returns the cell at the index
Cell* GridManager::getCell(const int index) const {
	return m_GridCells[index];
}

// Returns the cell at the x,y position in the grid
Cell* GridManager::getCell(const sf::Vector2f gridPos) const {
	return m_GridCells[gridPos.x + (gridPos.y * m_GridSize.x)];
}

// Returns the cell closest to the x,y position in the world
Cell* GridManager::getClosestCell(const sf::Vector2f worldPos) const {
	Cell* nearestCell = nullptr;
	float x0 = worldPos.x;
	float y0 = worldPos.y;
	float distance = 100000;

	for (auto it : m_GridCells){
		const float x1 = it->getPosition()->x;
		const float y1 = it->getPosition()->y;
		
		const float dx = x1 - x0;
		const float dy = y1 - y0;
		const float length = std::sqrt((dx*dx) + (dy*dy));
		if (distance > length){
			distance = length;
			nearestCell = it;
		}
	}

	return nearestCell;
}

// Returns the vector containg the cells
GridManager::CellVector* GridManager::getCellVector() {
	return &m_GridCells;
}

// Returns the number of cells
float GridManager::getGridSize() const {
	return m_GridCells.size();
}

// Returns the width and height of the grid
sf::Vector2f GridManager::getGridSize2f() const {
	return m_GridSize;
}

// Returns the width and height of a cell
sf::Vector2f GridManager::getCellSize() const {
	if (m_GridCells.empty())
		return sf::Vector2f(0, 0);
	return sf::Vector2f(m_GridCells[0]->getSprite()->getLocalBounds().width,
						m_GridCells[0]->getSprite()->getLocalBounds().height);
}

// Draw all the cells
void GridManager::draw(){
	for (auto it : m_GridCells)
		it->draw();
}