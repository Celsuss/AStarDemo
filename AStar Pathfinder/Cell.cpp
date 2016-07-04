#include "Cell.h"
#include "TextureManager.h"
#include "GraphicManager.h"
#include "Game.h"

Cell::Cell(sf::Vector2f pos, sf::Vector2f gridPos, int index){
	m_pWallShape = nullptr;
	m_pSprite = new sf::Sprite(*TextureManager::getInstance()->getTexture("Grid_G"));
	m_pSprite->setPosition(pos);
	m_Position = sf::Vector2f(pos);

	m_GridPos = sf::Vector2f(gridPos);
	m_ParentCell = nullptr;
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

Cell::~Cell(){}

void Cell::draw(){
	if (Game::getDebugging()){
		GraphicManager::getInstance()->draw(*m_pSprite);
		GraphicManager::getInstance()->draw(m_IndexText);
	}
	else if (m_pWallShape)
		GraphicManager::getInstance()->draw(*m_pWallShape);
}

sf::Sprite* Cell::getSprite(){
	return m_pSprite;
}

sf::Vector2f* Cell::getPosition(){
	return &m_Position;
}

int Cell::getIndex(){
	return m_Index;
}

Cell* Cell::getParentCell(){
	return m_ParentCell;
}

sf::Vector2f* Cell::getGridPosition(){
	return &m_GridPos;
}

float Cell::getGCost(){
	return m_GCost;
}

float Cell::getHCost(){
	return m_HCost;
}

float Cell::getFCost(){
	m_FCost = m_GCost + m_HCost;
	return m_FCost;
}

bool Cell::getIsWalkable(){
	if (!m_IsWalkable)
		int kalle = 0;
	return m_IsWalkable;
}

void Cell::setSpriteTexture(sf::Texture* texture){
	m_pSprite->setTexture(*texture);
}

void Cell::setIsWalkable(bool walkable){
	m_IsWalkable = walkable;
	if (walkable){
		m_pSprite->setTexture(*TextureManager::getInstance()->getTexture("Grid_G"));
		createWallShape();
	}
	else{
		m_pSprite->setTexture(*TextureManager::getInstance()->getTexture("Grid_R"));
		delete m_pWallShape;
		m_pWallShape = nullptr;
	}
}

void Cell::setGCost(float g){
	m_GCost = g;
	m_FCost = m_GCost + m_HCost;
}

void Cell::setHCost(float h){
	m_HCost = h;
	m_FCost = m_GCost + m_HCost;
}

void Cell::setParentCell(Cell* parent){
	m_ParentCell = parent;
}

void Cell::clearValues(){
	m_GCost = 0;
	m_HCost = 0;
	m_FCost = 0;
	m_ParentCell = nullptr;
}

void Cell::createWallShape(){
	m_pWallShape = new sf::RectangleShape(sf::Vector2f(m_pSprite->getLocalBounds().width, m_pSprite->getLocalBounds().height));
	m_pWallShape->setPosition(m_pSprite->getPosition());
}