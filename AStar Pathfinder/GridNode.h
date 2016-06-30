#pragma once
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"

class GridNode{
public:
	GridNode(sf::Vector2f pos, sf::Vector2f gridPos, int index);
	~GridNode();
	void draw();
	sf::Sprite* getSprite();
	sf::Vector2f* getPosition();
	int getIndex();

	GridNode* getParentNode();
	sf::Vector2f* getGridPosition();
	float getGCost();
	float getHCost();
	float getFCost();
	bool getIsWalkable();
	void setSpriteTexture(sf::Texture* texture);
	void setIsWalkable(bool walkable);
	void setGCost(float g);
	void setHCost(float h);
	void setParentNode(GridNode* parent);
	void clearValues();
private:
	sf::Sprite* m_pSprite;
	sf::Vector2f m_Position;
	sf::Text m_IndexText;
	sf::Vector2f m_GridPos;
	GridNode* m_ParentNode;
	bool m_IsWalkable;
	float m_GCost;
	float m_HCost;
	float m_FCost;
	int m_Index;
};