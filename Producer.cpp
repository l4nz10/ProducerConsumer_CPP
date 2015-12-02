#include <iostream>

#include "Producer.h"
#include "ConcurrentQueue.h"

Producer::Producer(std::string name) : QueueHandler(name) {
	counter = 1;
}

ConcurrentQueue * Producer::setQueue(ConcurrentQueue* q) {
	ConcurrentQueue * oldQueue = QueueHandler::setQueue(q);
	if (oldQueue != nullptr) {
			oldQueue->removeProducer(this);
	}
	queue->addProducer(this);
	return oldQueue;
}

ConcurrentQueue * Producer::safeUnsetQueue() {
	ConcurrentQueue * oldQueue = QueueHandler::unsetQueue();
	if (oldQueue != nullptr) {
			oldQueue->removeProducer(this);
	}
	return oldQueue;
}

bool Producer::execute() {
	bool success = queue->push(counter);
	if (success) {
		counter++;
	}
	return success;
}
