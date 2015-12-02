#include <iostream>

#include "ConcurrentQueue.h"

ConcurrentQueue::ConcurrentQueue(unsigned int size) : MAX_SIZE(size) {}

ConcurrentQueue::~ConcurrentQueue() {
	std::cout << "Destroying queue object" << std::endl;
}

bool ConcurrentQueue::push(int element) {
	bool success = false;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (queue.size() < MAX_SIZE) {
				queue.push(element);
				success = true;
		}
	}
	return success;
}

bool ConcurrentQueue::pop() {
	bool success = false;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (queue.size() > 0) {
				queue.pop();
				success = true;
		}
	}
	return success;
}


int ConcurrentQueue::get() {
	int elem = 0;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (queue.size() > 0) {
			elem = queue.front();
		}
	}
	return elem;
}

int ConcurrentQueue::get_and_pop() {
	int elem = 0;
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (queue.size() > 0) {
			elem = queue.front();
			queue.pop();
		}
	}
	return elem;
}

unsigned int ConcurrentQueue::size() {
	std::lock_guard<std::mutex> lock(mutex);
	return queue.size();
}
