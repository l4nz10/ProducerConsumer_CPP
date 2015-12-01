#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <string>

#include "QueueHandler.h"

class Consumer : public QueueHandler {
public:
	Consumer(std::string name, BlockingQueue* queue);
	Consumer(std::string name);
	virtual void execute();
};

#endif /* CONSUMER_H_ */
