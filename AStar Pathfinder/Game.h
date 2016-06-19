#pragma once
#include <vector>

class Goal;
class GameObject;

class Game{
public:
	typedef std::vector<GameObject*>GameObjectVector;

	Game();
	~Game();
	void run();

	GameObjectVector* getGameObjects();
	Goal* getGoal();
private:
	void update();
	void handleEvents();
	void handleInput();
	void createWalls();

	//bool m_
	GameObjectVector m_GameObjects;
};