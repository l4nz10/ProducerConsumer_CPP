#include <iostream>

#include "Producer.h"
#include "ThreadSafeQueue.h"

Producer::Producer(std::string name) : ConcurrentQueueHandler(name) {
	counter = 1;
}

Producer::~Producer() {
	stop();
	if (hasQueue()) {
		((ThreadSafeQueue *) queue)->removeProducer(this);
	}
}

Queue * Producer::setQueue(Queue * newQueue) {
	Queue * oldQueue = ConcurrentQueueHandler::setQueue(newQueue);
	if (oldQueue != nullptr) {
		((ThreadSafeQueue *) oldQueue)->removeProducer(this);
	}
	if (queue != nullptr) {
		((ThreadSafeQueue *) queue)->addProducer(this);
	}
	return oldQueue;
}

Queue * Producer::unsetQueue() {
	return Producer::setQueue(nullptr);
}

Queue * Producer::unsetQueueUnsafe() {
	return ConcurrentQueueHandler::unsetQueue();
}

bool Producer::execute() {
	bool success = queue->push(counter);
	if (success) {
		counter++;
	}
	return success;
}
