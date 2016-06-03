#include "GridNode.h"
#include "GraphicManager.h"
#include "TextureManager.h"

GridNode::GridNode(sf::Vector2f pos, sf::Vector2f gridPos){
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("Grid_G"));
	m_pSprite->setPosition(pos);
	m_Position = sf::Vector2f(pos);

	m_GridPos = sf::Vector2f(gridPos);
	m_ParentNode = nullptr;
	m_IsWalkable = true;
	m_GCost = 0;
	m_HCost = 0;
	m_FCost = 0;
}

GridNode::~GridNode(){}

void GridNode::draw(){
	GraphicManager::draw(*m_pSprite);
}

sf::Sprite* GridNode::getSprite(){
	return m_pSprite;
}

sf::Vector2f* GridNode::getPosition(){
	return &m_Position;
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

bool GridNode::isWalkable(){
	return m_IsWalkable;
}

void GridNode::setIsWalkable(bool walkable){
	m_IsWalkable = walkable;
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