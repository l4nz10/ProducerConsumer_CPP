#include <iostream>

#include "Consumer.h"
#include "ConcurrentQueue.h"

Consumer::Consumer(std::string name, ConcurrentQueue* queue) : QueueHandler(name, queue) {}

Consumer::Consumer(std::string name) : Consumer(name, nullptr) {};

bool Consumer::execute() {
	int elem = queue->get_and_pop();
	if (elem != 0) {
		std::cout << elem << std::endl;
	}
	return elem != 0;
}
