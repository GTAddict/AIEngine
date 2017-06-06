#include "stdafx.h"
#include "Message.h"

Message::Message()
	: Sender(-1)
	, Receiver(-1)
	, Msg(-1)
	, DispatchTime(0.0)
	, ExtraInfo(nullptr)
{
}
