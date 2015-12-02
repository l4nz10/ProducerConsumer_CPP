#include <iostream>

#include "Consumer.h"
#include "ConcurrentQueue.h"

Consumer::Consumer(std::string name) : QueueHandler(name) {};

ConcurrentQueue * Consumer::setQueue(ConcurrentQueue * q) {
	ConcurrentQueue * oldQueue = QueueHandler::setQueue(q);
	if (oldQueue != nullptr) {
		oldQueue->removeConsumer(this);
	}
	queue->addConsumer(this);
	return oldQueue;
}

ConcurrentQueue * Consumer::safeUnsetQueue() {
	ConcurrentQueue * oldQueue = QueueHandler::unsetQueue();
	if (oldQueue != nullptr) {
		oldQueue->removeConsumer(this);
	}
	return oldQueue;
}

bool Consumer::execute() {
	int elem = queue->get_and_pop();
	if (elem != 0) {
		std::cout << elem << std::endl;
	}
	return elem != 0;
}
