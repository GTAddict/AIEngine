#pragma once
#include <map>

class GameObject;

class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();

public:

	GameObjectManager(const GameObjectManager& rhs) = delete;
	GameObjectManager& operator=(const GameObjectManager& rhs) = delete;

	static GameObjectManager* GetInstance();

	void Register(GameObject* obj);
	void Unregister(GameObject* obj);

	GameObject* GetGameObjectFromID(int ID);

private:

	std::map<int, GameObject*> mObjectMap;
};

