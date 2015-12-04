#include <iostream>

#include "Producer.h"
#include "ThreadSafeQueue.h"

Producer::Producer(std::string name) : QueueHandler(name) {
	counter = 1;
}

Producer::~Producer() {
	stop();
	if (hasQueue()) {
		queue->removeProducer(this);
	}
}

ThreadSafeQueue * Producer::setQueue(ThreadSafeQueue* q) {
	ThreadSafeQueue * oldQueue = QueueHandler::setQueue(q);
	if (oldQueue != nullptr) {
		oldQueue->removeProducer(this);
	}
	if (queue != nullptr) {
		queue->addProducer(this);
	}
	return oldQueue;
}

ThreadSafeQueue * Producer::unsetQueue() {
	return setQueue(nullptr);
}

ThreadSafeQueue * Producer::unsetQueueUnsafe() {
	return QueueHandler::unsetQueue();
}

bool Producer::execute() {
	bool success = queue->push(counter);
	if (success) {
		counter++;
	}
	return success;
}
