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
	virtual ConcurrentQueue * setQueue(ConcurrentQueue * queue);
	virtual ConcurrentQueue * safeUnsetQueue();
	virtual ~Producer();
};

#endif /* PRODUCER_H_ */
