#include <iostream>

#include "Consumer.h"
#include "ConcurrentQueue.h"

Consumer::Consumer(std::string name) : QueueHandler(name) {};

Consumer::~Consumer() {
	safeUnsetQueue();
}

ConcurrentQueue * Consumer::setQueue(ConcurrentQueue * q) {
	ConcurrentQueue * oldQueue = QueueHandler::setQueue(q);
	if (oldQueue != nullptr) {
		oldQueue->removeConsumer(this);
	}
	if (queue != nullptr) {
		queue->addConsumer(this);
	}
	return oldQueue;
}

ConcurrentQueue * Consumer::safeUnsetQueue() {
	return setQueue(nullptr);
}

bool Consumer::execute() {
	int elem = queue->get_and_pop();
	return elem != 0;
}
