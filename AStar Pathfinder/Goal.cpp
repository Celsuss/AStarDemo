#include "Goal.h"
#include "TextureManager.h"
#include "GraphicManager.h"

Goal::Goal(sf::Vector2f pos){
	m_Type = Type::Goal;
	m_Position = pos;
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("Flag"));
	m_pSprite->setPosition(pos);
}

Goal::~Goal(){}

void Goal::draw(){
	GraphicManager::getInstance()->draw(*m_pSprite);
}