#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include <assert.h>


GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::GetInstance()
{
	static GameObjectManager gameObjectManager;
	return &gameObjectManager;
}

void GameObjectManager::Register(GameObject* obj)
{
	assert(mObjectMap.find(obj->ID()) == mObjectMap.end());
	mObjectMap[obj->ID()] = obj;
}

void GameObjectManager::Unregister(GameObject* obj)
{
	assert(mObjectMap.find(obj->ID()) != mObjectMap.end());
	mObjectMap.erase(obj->ID());
}

GameObject* GameObjectManager::GetGameObjectFromID(int ID)
{
	return mObjectMap[ID];
}
