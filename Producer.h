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
	Producer(std::string name, ConcurrentQueue* queue);
	Producer(std::string name);
};

#endif /* PRODUCER_H_ */
