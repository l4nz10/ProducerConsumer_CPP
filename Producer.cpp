#include <iostream>

#include "Producer.h"
#include "ConcurrentQueue.h"

Producer::Producer(std::string name) : QueueHandler(name) {
	counter = 1;
}

Producer::~Producer() {
	safeUnsetQueue();
}

ConcurrentQueue * Producer::setQueue(ConcurrentQueue* q) {
	ConcurrentQueue * oldQueue = QueueHandler::setQueue(q);
	if (oldQueue != nullptr) {
		oldQueue->removeProducer(this);
	}
	if (queue != nullptr) {
		queue->addProducer(this);
	}
	return oldQueue;
}

ConcurrentQueue * Producer::safeUnsetQueue() {
	return setQueue(nullptr);
}

bool Producer::execute() {
	bool success = queue->push(counter);
	if (success) {
		counter++;
	}
	return success;
}
