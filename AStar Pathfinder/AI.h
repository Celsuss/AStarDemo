#pragma once
#include "GameObject.h"
#include "Pathfinder.h"
#include "SFML/Graphics/Sprite.hpp"

class AI : public GameObject{
public:
	AI(sf::Vector2f pos, sf::Vector2f targetPos);
	virtual ~AI();
	virtual void draw();
private:
	void walk();

	sf::Sprite* m_pSprite;
	Pathfinder::PositionVector m_Path;
};