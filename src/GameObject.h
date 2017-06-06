#pragma once

class Message;

class GameObject
{
public:

	GameObject(int ID);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual bool HandleMessage(const Message& message) = 0;

	inline int ID() const { return mID; };

private:

	int mID;
};

