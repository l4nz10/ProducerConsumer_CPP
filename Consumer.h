#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <string>

#include "QueueHandler.h"

class Consumer : public QueueHandler {
protected:
	virtual bool execute();
public:
	Consumer(std::string name);
	virtual void setQueue(ConcurrentQueue * queue);
	virtual ConcurrentQueue * unsetQueue();
};

#endif /* CONSUMER_H_ */
