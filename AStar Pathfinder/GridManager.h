#pragma once
#include "SFML/System/Vector2.hpp"
#include <vector>

class Wall;
class Game;
class GridNode;

class GridManager{
public:
	typedef std::vector<GridNode*>GridNodeVector;

	static GridManager* getInstance();
	void initialize();
	void update();
	void clearValues();
	GridNode* getRandomNode();
	GridNode* getRandomWalkableNode();
	GridNode* getNode(int index);
	GridNode* getNode(sf::Vector2f pos);
	GridNode* getMatrixNode(sf::Vector2f gridPos);
	GridNodeVector* getNodeVector();
	float getGridSize();
	sf::Vector2f& getGridSize2f();
	sf::Vector2f& getGridNodeSize();
	void setNodesIsWalkable(Game* pGame);
private:
	GridManager();
	~GridManager();
	static GridManager* m_Instance;

	void draw();
	bool getWallNodeCollision(GridNode* pNode, Wall* pWall);

	GridNodeVector m_GridTiles;
	sf::Vector2f m_GridSize;
};