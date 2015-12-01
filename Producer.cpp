#include <iostream>

#include "Producer.h"

Producer::Producer(std::string name, BlockingQueue* queue) : QueueHandler(name, queue) {
	counter = 0;
}

Producer::Producer(std::string name) : Producer(name, nullptr) {}

void Producer::execute() {
	while (active) {
		if (queue == nullptr) {
			std::cout << "[Producer "+name+"]: No assigned queue. Quitting." << "\n";
			return;
		}
		queue->push(++counter);
		std::cout << "[Producer "+name+"]: Produced " << counter << ".\n";
	}
}
