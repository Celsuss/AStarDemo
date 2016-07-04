#pragma once
#include "SFML/System/Vector2.hpp"
#include "GridManager.h"
#include <vector>

class MazeGenerator{
public:
	enum Direction{
		Up,
		Right,
		Down,
		Left,
		Invalid
	};
	typedef std::vector<Direction> DirectionVector;

	static MazeGenerator* getInstance();

	void createMaze();
private:
	MazeGenerator();
	~MazeGenerator();
	static MazeGenerator* m_Instance;

	void buildMaze(sf::Vector2i pos, GridManager::CellVector& cells);
	bool vectorContains(const Direction& dir, const DirectionVector& directions);
};

