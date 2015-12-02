#include <iostream>

#include "Consumer.h"
#include "ConcurrentQueue.h"

Consumer::Consumer(std::string name) : QueueHandler(name) {};

void Consumer::setQueue(ConcurrentQueue* q) {
	QueueHandler::setQueue(q);
	queue->addConsumer(this);
}

ConcurrentQueue * Consumer::unsetQueue() {
	ConcurrentQueue * q = QueueHandler::unsetQueue();
	q->removeConsumer(this);
	return q;
}

bool Consumer::execute() {
	int elem = queue->get_and_pop();
	if (elem != 0) {
		std::cout << elem << std::endl;
	}
	return elem != 0;
}
