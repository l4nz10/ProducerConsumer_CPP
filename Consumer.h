#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <string>

#include "QueueHandler.h"

class Consumer : public QueueHandler {
protected:
	virtual bool execute();
public:
	Consumer(std::string name, ConcurrentQueue* queue);
	Consumer(std::string name);
};

#endif /* CONSUMER_H_ */
