#include "AI.h"
#include "TextureManager.h"
#include "GraphicManager.h"

AI::AI(sf::Vector2f pos, sf::Vector2f targetPos){
	m_Type = Type::AI;
	m_Position = pos;
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("AI"));
	m_pSprite->setPosition(pos);
	m_Speed = 10;
	m_Path = Pathfinder::findPath(m_Position, targetPos);
}

AI::~AI(){}

void AI::draw(){
	walk();
	m_pSprite->setPosition(m_Position);
	GraphicManager::draw(*m_pSprite);
}

void AI::walk(){
	if (m_Path.size() <= 0)
		return;

	sf::Vector2f deltaP = *m_Path.back() - m_Position;
	if (deltaP.x < 1 && deltaP.y < 1)
		m_Path.pop_back();
	normalizeVector2f(deltaP);
	m_Position += deltaP;
}

void AI::normalizeVector2f(sf::Vector2f& vec){
	float length = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (length != 0){
		vec.x /= length;
		vec.y /= length;
	}
}