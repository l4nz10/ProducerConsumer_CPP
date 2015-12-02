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
	mutex.lock();
	if (queue.size() < MAX_SIZE) {
			queue.push(element);
			success = true;
	}
	mutex.unlock();
	if (success) {
		awakeConsumers();
	}
	return success;
}

bool ConcurrentQueue::pop() {
	bool success = false;
	mutex.lock();
	if (queue.size() > 0) {
			queue.pop();
			success = true;
	}
	mutex.unlock();
	if (success) {
		awakeProducers();
	}
	return success;
}


int ConcurrentQueue::get() {
	int elem = 0;
	mutex.lock();
	if (queue.size() > 0) {
		elem = queue.front();
	}
	mutex.unlock();
	return elem;
}

int ConcurrentQueue::get_and_pop() {
	int elem = 0;
	mutex.lock();
	if (queue.size() > 0) {
		elem = queue.front();
		queue.pop();
	}
	mutex.unlock();
	if (elem != 0) {
		awakeProducers();
	}
	return elem;
}

unsigned int ConcurrentQueue::size() {
	std::lock_guard<std::mutex> lock(mutex);
	return queue.size();
}
