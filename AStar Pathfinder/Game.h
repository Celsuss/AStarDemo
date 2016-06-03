#pragma once
#include <vector>

class GameObject;

class Game{
public:
	typedef std::vector<GameObject*>GameObjectVector;

	Game();
	~Game();
	void run();
private:
	void update();
	void handleEvents();
	void createWalls();

	GameObjectVector m_GameObjects;
};