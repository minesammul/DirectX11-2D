#pragma once
#include <Script.h>
#include <queue>

enum class EVENTQUEUE_TYPE
{
	ATTACK,
	HITED,
	PLAYER_DATA,
	END
};

struct EVENT_PACKET
{
	EVENTQUEUE_TYPE eventType;
	int eventSendTargetID;

	vector<int> value;
};

class CEventQueueScript : public CScript
{
private:
	queue<EVENT_PACKET> eventQueue;


public:
	CEventQueueScript();
	~CEventQueueScript();

public:
	virtual void start();
	virtual void update();

	static CEventQueueScript* GetInstance()
	{
		static CEventQueueScript instance;
		return &instance;
	}

	queue<EVENT_PACKET> GetEventQueue() 
	{ 
		return eventQueue;
	}

	void SetEventQueue(queue<EVENT_PACKET> queue)
	{
		this->eventQueue = queue;
	}

	void EnqueueEvent(EVENT_PACKET data)
	{
		eventQueue.push(data);
	}
};

