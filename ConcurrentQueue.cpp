#include <iostream>

#include "ConcurrentQueue.h"

ConcurrentQueue::ConcurrentQueue(unsigned int size) : MAX_SIZE(size) {}

ConcurrentQueue::~ConcurrentQueue() {
	std::cout << "Destroying queue object" << std::endl;
}

void ConcurrentQueue::addProducer(QueueHandler * producer) {
	producers.push_back(producer);
}

void ConcurrentQueue::addConsumer(QueueHandler * consumer) {
	consumers.push_back(consumer);
}

void ConcurrentQueue::removeProducer(QueueHandler * producer) {
	for (std::vector<QueueHandler *>::iterator it = producers.begin(); it != producers.end(); ++it) {
		if (*it == producer) {
			producers.erase(it);
			break;
		}
	}
}

void ConcurrentQueue::removeConsumer(QueueHandler * consumer) {
	for (std::vector<QueueHandler *>::iterator it = consumers.begin(); it != consumers.end(); ++it) {
		if (*it == consumer) {
			consumers.erase(it);
			break;
		}
	}
}

void ConcurrentQueue::awakeProducers() {
	for (int i = 0; i < producers.size(); i++) {
		producers[i]->awake();
	}
}

void ConcurrentQueue::awakeConsumers() {
	for (int i = 0; i < consumers.size(); i++) {
		consumers[i]->awake();
	}
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
