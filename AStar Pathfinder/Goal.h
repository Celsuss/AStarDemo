#pragma once
#include "GameObject.h"
#include "SFML/Graphics/Sprite.hpp"

class Goal : public GameObject{
public:
	Goal(sf::Vector2f pos);
	virtual ~Goal();
	virtual void draw();
private:
	sf::Sprite* m_pSprite;
};