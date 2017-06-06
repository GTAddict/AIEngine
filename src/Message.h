#pragma once

#include <cmath>

class Message final
{
public:

	static constexpr double SmallestDelay = 0.2;

	Message();

	int		Sender;
	int		Receiver;
	int		Msg;
	double	DispatchTime;
	void*	ExtraInfo;
};

inline bool operator==(const Message& lhs, const Message& rhs)
{
	return lhs.Sender == rhs.Sender
		&& lhs.Receiver == rhs.Receiver
		&& lhs.Msg == rhs.Msg
		&& fabs((rhs.DispatchTime - lhs.DispatchTime) < Message::SmallestDelay);
}

inline bool operator<(const Message& lhs, const Message& rhs)
{
	if (lhs == rhs)
	{
		return false;
	}
	else
	{
		return lhs.DispatchTime < rhs.DispatchTime;
	}
}