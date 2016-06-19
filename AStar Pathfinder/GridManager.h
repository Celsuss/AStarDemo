#pragma once
#include "SFML/System/Vector2.hpp"
#include <vector>

class Wall;
class Game;
class GridNode;

class GridManager{
public:
	typedef std::vector<GridNode*>GridNodeVector;
	typedef std::vector<GridNodeVector>GridNodeMatrix;

	static GridManager* getInstance();
	static void initialize(Game* pGame);
	static void update();
	static void clearValues();
	static GridNode* getRandomNode();
	static GridNode* getRandomNodeWithinRange(sf::Vector2f pos, int range);
	static GridNode* getNode(sf::Vector2f pos);
	static GridNode* getMatrixNode(sf::Vector2f gridPos);
	static sf::Vector2f* getGridSize();
	static sf::Vector2f& getGridNodeSize();
	static void setNodesIsWalkable(Game* pGame);
private:
	GridManager();
	~GridManager();
	static GridManager* m_Instance;

	void draw();
	bool getWallNodeCollision(GridNode* pNode, Wall* pWall);

	GridNodeMatrix m_GridTileMatrix;
	sf::Vector2f* m_GridSize;
};