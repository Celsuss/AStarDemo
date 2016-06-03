#pragma once
#include "GameObject.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Wall : public GameObject{
public:
	Wall(sf::Vector2f pos, int width, int height);
	virtual ~Wall();

	//virtual void addCollision(GameObject* obj);
	void draw();
private:
	sf::RectangleShape m_Rectangle;
};