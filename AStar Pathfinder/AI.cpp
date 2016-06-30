#include "AI.h"
#include "TextureManager.h"
#include "GraphicManager.h"

AI::AI(sf::Vector2f pos, sf::Vector2f targetPos){
	m_Type = Type::AI;
	m_Position = pos;
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("AI"));
	m_pSprite->setPosition(pos);
	m_Speed = 15;
	m_Path = Pathfinder::getInstance()->getPath(m_Position, targetPos);
	m_Path.pop_back();
}

AI::~AI(){
	m_Path.clear();
}

void AI::draw(){
	walk();
	m_pSprite->setPosition(m_Position);
	drawPath();
	GraphicManager::getInstance()->draw(*m_pSprite);
}

void AI::walk(){
	if (m_Path.size() <= 0)
		return;
	
	sf::Vector2f pathPos = *m_Path.back();
	sf::Vector2f deltaP = *m_Path.back() - m_Position;
	if (std::abs(deltaP.x) < 1 && std::abs(deltaP.y) < 1)
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

void AI::drawPath(){
	if (m_Path.size() < 2)
		return;

	sf::Vector2f nodeSize = GridManager::getInstance()->getGridNodeSize();
	
	for (int i = 0; i < m_Path.size() - 1; i++){
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(m_Path[i]->x + (nodeSize.x / 2), m_Path[i]->y + (nodeSize.y / 2))),
			sf::Vertex(sf::Vector2f(m_Path[i + 1]->x + (nodeSize.x / 2), m_Path[i + 1]->y + (nodeSize.y / 2)))
		};
		line[0].color = sf::Color::Yellow;
		line[1].color = sf::Color::Yellow;
		GraphicManager::getInstance()->getWindow()->draw(line, 2, sf::Lines);
	}
}