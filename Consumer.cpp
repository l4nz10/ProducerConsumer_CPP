#include <iostream>

#include "Consumer.h"
#include "ThreadSafeQueue.h"

Consumer::Consumer(std::string name) : ConcurrentQueueHandler(name) {};

Consumer::~Consumer() {
	stop();
	if (hasQueue()) {
		((ThreadSafeQueue *) queue)->removeConsumer(this);
	}
}

Queue * Consumer::setQueue(Queue * newQueue) {
	Queue * oldQueue = ConcurrentQueueHandler::setQueue(newQueue);
	if (oldQueue != nullptr) {
		((ThreadSafeQueue *) oldQueue)->removeConsumer(this);
	}
	if (queue != nullptr) {
		((ThreadSafeQueue *) queue)->addConsumer(this);
	}
	return oldQueue;
}

Queue * Consumer::unsetQueue() {
	return Consumer::setQueue(nullptr);
}

Queue * Consumer::unsetQueueUnsafe() {
	return ConcurrentQueueHandler::unsetQueue();
}

bool Consumer::execute() {
	int elem = queue->get_and_pop();
	return elem != 0;
}
