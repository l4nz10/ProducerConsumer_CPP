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
	virtual void setQueue(ConcurrentQueue * queue);
	virtual ConcurrentQueue * unsetQueue();
};

#endif /* PRODUCER_H_ */
