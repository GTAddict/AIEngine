#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
	: GameObject(Vec2(), Vec2(1.0, 1.0), 0.0)
{
}

GameObject::GameObject(const Vec2& position, const Vec2& scale, double boundingRadius)
	: mPosition(position)
	, mScale(scale)
	, mBoundingRadius(boundingRadius)
	, mID(NextValidId())
{
}

GameObject::~GameObject()
{
}

bool GameObject::HandleMessage(const Message& message)
{
	return false;
}
