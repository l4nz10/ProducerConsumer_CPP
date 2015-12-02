#include <iostream>

#include "Producer.h"
#include "ConcurrentQueue.h"

Producer::Producer(std::string name) : QueueHandler(name) {
	counter = 1;
}

void Producer::setQueue(ConcurrentQueue* q) {
	QueueHandler::setQueue(q);
	queue->addProducer(this);
}

ConcurrentQueue * Producer::unsetQueue() {
	ConcurrentQueue * q = QueueHandler::unsetQueue();
	q->removeProducer(this);
	return q;
}

bool Producer::execute() {
	bool success = queue->push(counter);
	if (success) {
		counter++;
	}
	return success;
}
