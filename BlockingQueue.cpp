/*
 * BlockingQueue.cpp
 *
 *  Created on: 30 nov 2015
 *      Author: valerio
 */

#include <iostream>

#include "BlockingQueue.h"

BlockingQueue::BlockingQueue(unsigned int size) : MAX_SIZE(size) {}

BlockingQueue::~BlockingQueue() {
	std::cout << "Destroying queue object" << std::endl;
}

bool BlockingQueue::push(int element) {
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this](){return queue.size() < MAX_SIZE;});
	queue.push(element);
	lock.unlock();
	cv.notify_all();
	return true;
}

bool BlockingQueue::pop() {
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this](){return queue.size() > 0;});
	queue.pop();
	lock.unlock();
	cv.notify_all();
	return true;
}


int BlockingQueue::front() {
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this](){return queue.size() > 0;});
	int elem = queue.front();
	lock.unlock();
	cv.notify_all();
	return elem;
}

int BlockingQueue::back() {
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this](){return queue.size() > 0;});
	int elem = queue.back();
	lock.unlock();
	cv.notify_all();
	return elem;
}

int BlockingQueue::frontPop() {
	std::unique_lock<std::mutex> lock(mutex);
	cv.wait(lock, [this](){return queue.size() > 0;});
	int elem = queue.front();
	queue.pop();
	lock.unlock();
	cv.notify_all();
	return elem;
}

unsigned int BlockingQueue::size() {
	std::lock_guard<std::mutex> lock(mutex);
	return queue.size();
}
