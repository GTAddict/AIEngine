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
	inline void SetGoalPosition(const Vec2& position)	{ mGoal = position; for (Agent* agent : mAgents) agent->SetTarget(position); }

	inline void EnableSeek()							{ for (Agent* agent : mAgents) agent->SeekTo(mGoal); }
	inline void EnableArrive()							{ for (Agent* agent : mAgents) agent->ArriveAt(mGoal); }
	inline void EnableFlee()							{ for (Agent* agent : mAgents) agent->FleeFrom(mGoal); }

	inline void DisableSeek()							{ for (Agent* agent : mAgents) agent->StopSeek(); }
	inline void DisableArrive()							{ for (Agent* agent : mAgents) agent->StopArrive(); }
	inline void DisableFlee()							{ for (Agent* agent : mAgents) agent->StopFlee(); }

	inline int GetClientWidth()					{ return mClientWidth; }
	inline int GetClientHeight()				{ return mClientHeight; }

private:

	std::vector<Agent*> mAgents;
	int mClientWidth;
	int mClientHeight;

	Vec2 mGoal;
};

