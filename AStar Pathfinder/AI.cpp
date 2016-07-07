#include "AI.h"
#include "Game.h"
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

AI::~AI(){}

// Calls the walk function and updates the sprites position
// Calls drawPath() if debugging is true
// Draws the AI sprite
void AI::draw(){
	walk();
	m_pSprite->setPosition(m_Position);
	if (Game::getDebugging())
		drawPath();
	GraphicManager::getInstance()->draw(*m_pSprite);
}

// Walks toward the next position in the path vector.
// Pop back the path vector when it has reached the position
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

// Normalize a Vector2f
void AI::normalizeVector2f(sf::Vector2f& vec){
	float length = std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (length != 0){
		vec.x /= length;
		vec.y /= length;
	}
}

// Draw a line that shows the path to walk
void AI::drawPath(){
	if (m_Path.size() < 2)
		return;

	sf::Vector2f cellSize = GridManager::getInstance()->getCellSize();
	
	for (int i = 0; i < m_Path.size() - 1; i++){
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(m_Path[i]->x + (cellSize.x / 2), m_Path[i]->y + (cellSize.y / 2))),
			sf::Vertex(sf::Vector2f(m_Path[i + 1]->x + (cellSize.x / 2), m_Path[i + 1]->y + (cellSize.y / 2)))
		};
		line[0].color = sf::Color::Yellow;
		line[1].color = sf::Color::Yellow;
		GraphicManager::getInstance()->getWindow()->draw(line, 2, sf::Lines);
	}
}