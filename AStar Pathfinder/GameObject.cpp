#include "GameObject.h"

GameObject::GameObject(){}

GameObject::~GameObject(){}

// Returns the position
sf::Vector2f* GameObject::getPosition(){
	return &m_Position;
}

// Returns the type
GameObject::Type GameObject::getGameObjectType() const {
	return m_Type;
}