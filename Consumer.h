#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "ConcurrentQueueHandler.h"

class Consumer : public ConcurrentQueueHandler {
protected:
	virtual bool execute();
public:
	Consumer(std::string name);
	virtual Queue * setQueue(Queue * queue);
	virtual Queue * unsetQueue();
	virtual Queue * unsetQueueUnsafe();
	virtual ~Consumer();
};

#endif /* CONSUMER_H_ */
