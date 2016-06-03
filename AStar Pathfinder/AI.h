#pragma once
#include "GameObject.h"
#include "SFML/Graphics/Sprite.hpp"

class AI : public GameObject{
public:
	AI(sf::Vector2f pos);
	virtual ~AI();
	virtual void draw();
private:
	sf::Sprite* m_pSprite;
};