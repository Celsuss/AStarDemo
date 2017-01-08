#pragma once
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Cell{
public:
	Cell(const sf::Vector2f pos, const sf::Vector2f gridPos, const int index);
	~Cell();
	void draw();
	sf::Sprite* getSprite() const;
	sf::Vector2f* getPosition();
	int getIndex() const;

	Cell* getParentCell() const;
	sf::Vector2f* getGridPosition();
	float getGCost() const;
	float getHCost() const;
	float getFCost();
	bool getIsWalkable() const;
	void setSpriteTexture(const sf::Texture* pTexture);
	void setIsWalkable(const bool walkable);
	void setGCost(const float g);
	void setHCost(const float h);
	void setParentCell(Cell* pParent);
	void clearValues();
private:
	void createWallShape();

	sf::Sprite* m_pSprite;
	sf::RectangleShape* m_pWallShape;
	sf::Vector2f m_Position;
	sf::Text m_IndexText;
	sf::Vector2f m_GridPos;
	Cell* m_ParentCell;
	bool m_IsWalkable;
	float m_GCost;
	float m_HCost;
	float m_FCost;
	int m_Index;
};