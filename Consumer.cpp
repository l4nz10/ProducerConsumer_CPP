#include <iostream>

#include "Consumer.h"

Consumer::Consumer(std::string name, BlockingQueue* queue) : QueueHandler(name, queue) {}

Consumer::Consumer(std::string name) : Consumer(name, nullptr) {};

void Consumer::execute() {
	while (active) {
		if (queue == nullptr) {
			std::cout << "[Consumer "+name+"]: No assigned queue. Quitting." << "\n";
			return;
		}
		std::cout << "[Consumer "+name+"]: Consumed " << queue->frontPop() << ".\n";
	}
}
