#include "stdafx.h"
#include "World.h"
#include "Agent.h"

World::World(int width, int height)
	: mClientWidth(width)
	, mClientHeight(height)
	, mGoal(Vec2(width / 2, height / 2))
{
	Vec2 SpawnPos = Vec2(mClientWidth / 2, mClientHeight / 2);

	Agent* pAgent = new Agent(this, SpawnPos, 0.0, 2.0, Vec2(1.0, 1.0), 2.0, Vec2(), 10.0, 2.0, 4.0);
	mAgents.push_back(pAgent);
}

World::~World()
{
	for (auto pAgent : mAgents)
	{
		delete pAgent;
	}
}

void World::Update(double deltaTime)
{
	for (auto pAgent : mAgents)
	{
		pAgent->Update(deltaTime);
	}
}

void World::Render()
{
	// Render goal
	//
	////

	// Render agents
	for (auto pAgent : mAgents)
	{
		pAgent->Render();
	}
}
