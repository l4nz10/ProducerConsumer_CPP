#include <iostream>

#include "Consumer.h"
#include "ThreadSafeQueue.h"

Consumer::Consumer(std::string name) : QueueHandler(name) {};

Consumer::~Consumer() {
	stop();
	if (hasQueue()) {
		queue->removeConsumer(this);
	}
}

ThreadSafeQueue * Consumer::setQueue(ThreadSafeQueue * q) {
	ThreadSafeQueue * oldQueue = QueueHandler::setQueue(q);
	if (oldQueue != nullptr) {
		oldQueue->removeConsumer(this);
	}
	if (queue != nullptr) {
		queue->addConsumer(this);
	}
	return oldQueue;
}

ThreadSafeQueue * Consumer::unsetQueue() {
	return setQueue(nullptr);
}

ThreadSafeQueue * Consumer::unsetQueueUnsafe() {
	return QueueHandler::unsetQueue();
}

bool Consumer::execute() {
	int elem = queue->get_and_pop();
	return elem != 0;
}
