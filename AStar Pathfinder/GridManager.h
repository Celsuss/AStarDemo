#pragma once
#include "SFML/System/Vector2.hpp"
#include <vector>

class GridNode;
class Level;

class GridManager{
public:
	typedef std::vector<GridNode*>GridNodeVector;
	typedef std::vector<GridNodeVector>GridNodeMatrix;

	static GridManager* getInstance();
	static void initialize();
	static void update();
	static void clearValues();
	static GridNode* getRandomNode();
	static GridNode* getRandomNodeWithinRange(sf::Vector2f pos, int range);
	static GridNode* getNode(sf::Vector2f pos);
	static GridNode* getMatrixNode(sf::Vector2f gridPos);
	static sf::Vector2f* getGridSize();
private:
	GridManager();
	~GridManager();
	static GridManager* m_Instance;

	void draw();
	void setNodesIsWalkable(Level* level);

	GridNodeMatrix m_GridTileMatrix;
	sf::Vector2f* m_GridSize;
};