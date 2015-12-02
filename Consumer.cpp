#include <iostream>

#include "Consumer.h"

Consumer::Consumer(std::string name, ConcurrentQueue* queue) : QueueHandler(name, queue) {}

Consumer::Consumer(std::string name) : Consumer(name, nullptr) {};

void Consumer::execute() {
	while (active) {
		if (queue == nullptr) {
			std::cout << "["+name+"]: No assigned queue." << "\n";
			break;
		}
		int elem = queue->get_and_pop();
		if (elem != 0) {
			std::cout << "["+name+"]: " << elem << std::endl;
		}
	}
	std::cout << "["+name+"] Quitting..." << std::endl;
}
