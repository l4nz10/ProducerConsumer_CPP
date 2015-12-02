#include <iostream>

#include "Producer.h"

Producer::Producer(std::string name, ConcurrentQueue* queue) : QueueHandler(name, queue) {
	counter = 1;
}

Producer::Producer(std::string name) : Producer(name, nullptr) {}

void Producer::execute() {
	while (active) {
		if (queue == nullptr) {
			std::cout << "["+name+"]: No assigned queue." << "\n";
			break;
		}
		if (queue->push(counter)) {
			counter++;
		}
	}
	std::cout << "["+name+"] Quitting..." << std::endl;
}
