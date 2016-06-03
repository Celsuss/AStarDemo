#include "AI.h"
#include "TextureManager.h"
#include "GraphicManager.h"

AI::AI(sf::Vector2f pos){
	m_Type = Type::AI;
	m_Position = pos;
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("AI"));
	m_pSprite->setPosition(pos);
}

AI::~AI(){}

void AI::draw(){
	m_pSprite->setPosition(m_Position);
	GraphicManager::draw(*m_pSprite);
}