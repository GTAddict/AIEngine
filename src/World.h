#pragma once

#include <vector>
#include "Agent.h"

class World
{
public:
	World(int width, int height);
	~World();

	void Update(double deltaTime);
	void Render();

	inline const std::vector<Agent*>& Agents()			{ return mAgents; }
	inline const Vec2& GetGoalPosition()				{ return mGoal; }
	inline void SetGoalPosition(const Vec2& position)	{ mGoal = position; }

	inline int GetClientWidth()					{ return mClientWidth; }
	inline int GetClientHeight()				{ return mClientHeight; }

private:

	std::vector<Agent*> mAgents;
	int mClientWidth;
	int mClientHeight;

	Vec2 mGoal;
};

