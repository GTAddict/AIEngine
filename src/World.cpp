#include "stdafx.h"
#include "World.h"
#include "Agent.h"

World::World(int width, int height)
	: mClientWidth(width)
	, mClientHeight(height)
	, mGoal(Vec2(width / 2, height / 2))
{
	Vec2 SpawnPos = Vec2(mClientWidth, mClientHeight / 2);
	Vec2 Target = Vec2(mClientWidth / 4, mClientHeight / 4);
	double Rotation = 2.0;
	double Radius = 5.0;
	Vec2 Scale(10.0, 10.0);
	double Mass = 2.0;
	Vec2 Velocity;
	double MaxSpeed = 10.0;
	double MaxForce = 2.0;
	double MaxTurnRate = 4.0;

	Agent* pAgent = new Agent(this, SpawnPos, Rotation, Radius, Scale, Mass, Velocity, MaxSpeed, MaxForce, MaxTurnRate);
	pAgent->SetTarget(Target);
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
