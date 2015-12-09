#include <iostream>

#include "ThreadSafeQueue.h"
#include "Producer.h"
#include "Consumer.h"

ThreadSafeQueue::ThreadSafeQueue(std::string name, unsigned int size) : Queue(name, size) {}

ThreadSafeQueue::~ThreadSafeQueue() {
	for (unsigned int i = 0; i < producers.size(); i++) {
		((Producer *) producers[i])->unsetQueueUnsafe();
	}
	for (unsigned int i = 0; i < consumers.size(); i++) {
		((Consumer *) consumers[i])->unsetQueueUnsafe();
	}
}

void ThreadSafeQueue::addProducer(ConcurrentQueueHandler * producer) {
	producers.push_back(producer);
}

void ThreadSafeQueue::addConsumer(ConcurrentQueueHandler * consumer) {
	consumers.push_back(consumer);
}

void ThreadSafeQueue::removeProducer(ConcurrentQueueHandler * producer) {
	for (std::vector<ConcurrentQueueHandler *>::iterator it = producers.begin(); it != producers.end(); ++it) {
		if (*it == producer) {
			producers.erase(it);
			break;
		}
	}
}

void ThreadSafeQueue::removeConsumer(ConcurrentQueueHandler * consumer) {
	for (std::vector<ConcurrentQueueHandler *>::iterator it = consumers.begin(); it != consumers.end(); ++it) {
		if (*it == consumer) {
			consumers.erase(it);
			break;
		}
	}
}

void ThreadSafeQueue::awakeProducers() {
	for (int i = 0; i < producers.size(); i++) {
		producers[i]->awake();
	}
}

void ThreadSafeQueue::awakeConsumers() {
	for (int i = 0; i < consumers.size(); i++) {
		consumers[i]->awake();
	}
}


bool ThreadSafeQueue::push(int element) {
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

bool ThreadSafeQueue::pop() {
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


int ThreadSafeQueue::get() {
	int elem = 0;
	mutex.lock();
	if (queue.size() > 0) {
		elem = queue.front();
	}
	mutex.unlock();
	return elem;
}

int ThreadSafeQueue::get_and_pop() {
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

unsigned int ThreadSafeQueue::size() {
	std::lock_guard<std::mutex> lock(mutex);
	return queue.size();
}
