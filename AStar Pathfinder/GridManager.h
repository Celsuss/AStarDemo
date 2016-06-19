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
	void initialize(Game* pGame);
	void update();
	void clearValues();
	GridNode* getRandomNode();
	GridNode* getRandomNodeWithinRange(sf::Vector2f pos, int range);
	GridNode* getNode(sf::Vector2f pos);
	GridNode* getMatrixNode(sf::Vector2f gridPos);
	sf::Vector2f* getGridSize();
	sf::Vector2f& getGridNodeSize();
	void setNodesIsWalkable(Game* pGame);
private:
	GridManager();
	~GridManager();
	static GridManager* m_Instance;

	void draw();
	bool getWallNodeCollision(GridNode* pNode, Wall* pWall);

	GridNodeMatrix m_GridTileMatrix;
	sf::Vector2f* m_GridSize;
};