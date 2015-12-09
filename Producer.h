#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <string>

#include "ConcurrentQueueHandler.h"

class Producer : public ConcurrentQueueHandler {
private:
	int counter;
protected:
	virtual bool execute();
public:
	Producer(std::string name);
	virtual Queue * setQueue(Queue * newQueue);
	virtual Queue * unsetQueue();
	virtual Queue * unsetQueueUnsafe();
	virtual ~Producer();
};

#endif /* PRODUCER_H_ */
