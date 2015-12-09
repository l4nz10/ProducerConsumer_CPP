#include <string>
#include <queue>

#include "Queue.h"


Queue::Queue(std::string name, unsigned int size) : name(name), MAX_SIZE(size) {}

bool Queue::push(int element) {
	if (queue.size() < MAX_SIZE) {
		queue.push(element);
		return true;
	}
	return false;
}

bool Queue::pop() {
	if (queue.size() > 0) {
		queue.pop();
		return true;
	}
	return false;
}


int Queue::get() {
	if (queue.size() > 0) {
		return queue.front();
	}
	return 0;
}

int Queue::get_and_pop() {
	if (queue.size() > 0) {
		int elem = queue.front();
		queue.pop();
    return elem;
	}
	return 0;
}

unsigned int Queue::size() {
	return queue.size();
}

Queue::~Queue() {}
