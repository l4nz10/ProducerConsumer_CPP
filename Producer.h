#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <string>

#include "QueueHandler.h"

class Producer : public QueueHandler {
private:
	int counter;
protected:
	virtual bool execute();
public:
	Producer(std::string name);
	virtual ThreadSafeQueue * setQueue(ThreadSafeQueue * queue);
	virtual ThreadSafeQueue * unsetQueue();
	virtual ThreadSafeQueue * unsetQueueUnsafe();
	virtual ~Producer();
};

#endif /* PRODUCER_H_ */
