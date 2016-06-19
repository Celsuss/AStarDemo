#include "Wall.h"
#include "GraphicManager.h"
#include "SFML/Graphics/Rect.hpp"

Wall::Wall(sf::Vector2f pos, int width, int height){
	m_Type = Type::Wall;
	m_Rectangle.setPosition(pos);
	m_Rectangle.setSize(sf::Vector2f(width, height));
	m_Rectangle.setOutlineThickness(0);
	m_Rectangle.setFillColor(sf::Color::Red);
	m_Position = pos;
	//sf::Vector2f normal = sf::Vector2f(m_VertexArray[1].position.y * -1, m_VertexArray[1].position.x);
}

Wall::~Wall(){}

void Wall::draw(){
	GraphicManager::draw(m_Rectangle);
}

sf::RectangleShape* Wall::getShape(){
	return &m_Rectangle;
}