#pragma once
#include "SFML/System/Vector2.hpp"
#include <vector>

class Wall;
class Game;
class Cell;

class GridManager{
public:
	typedef std::vector<Cell*>CellVector;

	static GridManager* getInstance();
	void initialize();
	void update();
	void clearValues();
	Cell* getRandomCell();
	Cell* getRandomWalkableCell();
	Cell* getCell(int index);
	Cell* getCell(sf::Vector2f gridPos);
	Cell* getClosestCell(sf::Vector2f worldPos);
	CellVector* getCellVector();
	float getGridSize();
	sf::Vector2f& getGridSize2f();
	sf::Vector2f& getCellSize();
private:
	GridManager();
	~GridManager();
	static GridManager* m_Instance;

	void draw();

	CellVector m_GridCells;
	sf::Vector2f m_GridSize;
};