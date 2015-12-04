#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <string>

#include "QueueHandler.h"

class Consumer : public QueueHandler {
protected:
	virtual bool execute();
public:
	Consumer(std::string name);
	virtual ConcurrentQueue * setQueue(ConcurrentQueue * queue);
	virtual ConcurrentQueue * safeUnsetQueue();
	virtual ~Consumer();
};

#endif /* CONSUMER_H_ */
