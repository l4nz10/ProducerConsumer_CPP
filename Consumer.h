#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <string>

#include "QueueHandler.h"

class Consumer : public QueueHandler {
protected:
	virtual bool execute();
public:
	Consumer(std::string name);
	virtual ThreadSafeQueue * setQueue(ThreadSafeQueue * queue);
	virtual ThreadSafeQueue * unsetQueue();
	virtual ThreadSafeQueue * unsetQueueUnsafe();
	virtual ~Consumer();
};

#endif /* CONSUMER_H_ */
