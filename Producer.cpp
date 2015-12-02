#include <iostream>

#include "Producer.h"
#include "ConcurrentQueue.h"

Producer::Producer(std::string name, ConcurrentQueue* queue) : QueueHandler(name, queue) {
	counter = 1;
}

Producer::Producer(std::string name) : Producer(name, nullptr) {}

bool Producer::execute() {
	bool success = queue->push(counter);
	if (success) {
		counter++;
	}
	return success;
}
