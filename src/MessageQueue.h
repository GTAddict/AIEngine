#pragma once
#include <set>

class Message;

class MessageQueue
{
private:
	MessageQueue();
	~MessageQueue();

public:

	MessageQueue(const MessageQueue& rhs) = delete;
	MessageQueue& operator=(const MessageQueue& rhs) = delete;

	static MessageQueue* GetInstance();

	void Update();

	void SendMessage(const Message& message);

private:

	void Send(const Message& message);

	std::set<Message> mPendingMessages;
};

