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
	Cell* getRandomCell() const;
	Cell* getRandomWalkableCell() const;
	Cell* getCell(const int index) const;
	Cell* getCell(const sf::Vector2f gridPos) const;
	Cell* getClosestCell(const sf::Vector2f worldPos) const;
	CellVector* getCellVector();
	float getGridSize() const;
	sf::Vector2f getGridSize2f() const;
	sf::Vector2f getCellSize() const;
private:
	GridManager();
	~GridManager();
	static GridManager* m_Instance;

	void draw();

	CellVector m_GridCells;
	sf::Vector2f m_GridSize;
};