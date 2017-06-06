#include "stdafx.h"
#include "MessageQueue.h"
#include "Message.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include <assert.h>


MessageQueue::MessageQueue()
{
}


MessageQueue::~MessageQueue()
{
}

MessageQueue* MessageQueue::GetInstance()
{
	static MessageQueue messageQueue;
	return &messageQueue;
}

void MessageQueue::SendMessage(const Message& message)
{
	if (message.DispatchTime == 0)
	{
		Send(message);
	}
	else
	{
		// Delayed sending not supported yet.
		assert(false);
	}
}

void MessageQueue::Send(const Message& message)
{
	GameObjectManager::GetInstance()->GetGameObjectFromID(message.Receiver)->HandleMessage(message);
}
