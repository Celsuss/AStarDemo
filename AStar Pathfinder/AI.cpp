#include "AI.h"
#include "TextureManager.h"
#include "GraphicManager.h"

AI::AI(sf::Vector2f pos, sf::Vector2f targetPos){
	m_Type = Type::AI;
	m_Position = pos;
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("AI"));
	m_pSprite->setPosition(pos);
	m_Path = Pathfinder::findPath(m_Position, targetPos);
}

AI::~AI(){}

void AI::draw(){
	walk();
	m_pSprite->setPosition(m_Position);
	GraphicManager::draw(*m_pSprite);
}

void AI::walk(){

}