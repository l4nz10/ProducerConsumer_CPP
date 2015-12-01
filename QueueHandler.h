#ifndef QUEUEHANDLER_H_
#define QUEUEHANDLER_H_

#include <string>
#include <thread>

#include "BlockingQueue.h"

class QueueHandler {
protected:
	std::string name;
	std::thread* thread;
	BlockingQueue* queue;
	bool active;
	QueueHandler(std::string name, BlockingQueue* queue);
public:
	virtual void setQueue(BlockingQueue* queue);
	virtual BlockingQueue* getQueue();
	virtual BlockingQueue* unsetQueue();
	virtual ~QueueHandler();
	virtual void start();
	virtual void kill();
	virtual void execute() = 0;
};

#endif /* QUEUEHANDLER_H_ */
