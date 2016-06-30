#include "GridNode.h"
#include "TextureManager.h"
#include "GraphicManager.h"
#include "Game.h"

GridNode::GridNode(sf::Vector2f pos, sf::Vector2f gridPos, int index){
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("Grid_G"));
	m_pSprite->setPosition(pos);
	m_Position = sf::Vector2f(pos);

	m_GridPos = sf::Vector2f(gridPos);
	m_ParentNode = nullptr;
	m_IsWalkable = true;
	m_GCost = 0;
	m_HCost = 0;
	m_FCost = 0;
	m_Index = index;

	m_IndexText.setFont(*GraphicManager::getInstance()->getFont());
	m_IndexText.setCharacterSize(12);
	m_IndexText.setColor(sf::Color::White);
	m_IndexText.setString(std::to_string(m_Index));
	m_IndexText.setPosition(m_Position);
}

GridNode::~GridNode(){}

void GridNode::draw(){
	if (Game::getDebugging()){
		GraphicManager::getInstance()->draw(*m_pSprite);
		GraphicManager::getInstance()->draw(m_IndexText);
	}
}

sf::Sprite* GridNode::getSprite(){
	return m_pSprite;
}

sf::Vector2f* GridNode::getPosition(){
	return &m_Position;
}

int GridNode::getIndex(){
	return m_Index;
}

GridNode* GridNode::getParentNode(){
	return m_ParentNode;
}

sf::Vector2f* GridNode::getGridPosition(){
	return &m_GridPos;
}

float GridNode::getGCost(){
	return m_GCost;
}

float GridNode::getHCost(){
	return m_HCost;
}

float GridNode::getFCost(){
	m_FCost = m_GCost + m_HCost;
	return m_FCost;
}

bool GridNode::getIsWalkable(){
	if (!m_IsWalkable)
		int kalle = 0;
	return m_IsWalkable;
}

void GridNode::setSpriteTexture(sf::Texture* texture){
	m_pSprite->setTexture(*texture);
}

void GridNode::setIsWalkable(bool walkable){
	m_IsWalkable = walkable;
	if (!walkable)
		m_pSprite->setTexture(*TextureManager::getInstance()->getTexture("Grid_R"));
	else
		m_pSprite->setTexture(*TextureManager::getInstance()->getTexture("Grid_G"));
}

void GridNode::setGCost(float g){
	m_GCost = g;
	m_FCost = m_GCost + m_HCost;
}

void GridNode::setHCost(float h){
	m_HCost = h;
	m_FCost = m_GCost + m_HCost;
}

void GridNode::setParentNode(GridNode* parent){
	m_ParentNode = parent;
}

void GridNode::clearValues(){
	m_GCost = 0;
	m_HCost = 0;
	m_FCost = 0;
	m_ParentNode = nullptr;
}