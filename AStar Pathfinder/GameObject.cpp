#include "GameObject.h"

GameObject::GameObject(){}

GameObject::~GameObject(){}

sf::Vector2f* GameObject::getPosition(){
	return &m_Position;
}

GameObject::Type GameObject::getGameObjectType(){
	return m_Type;
}