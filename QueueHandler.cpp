#include <iostream>

#include "QueueHandler.h"

QueueHandler::QueueHandler(std::string name, ConcurrentQueue* queue) : name(name),
																																			 queue(queue),
																																			 thread(nullptr),
																																			 alive(false),
																																			 keep_going(true) {}

QueueHandler::~QueueHandler() {
	kill();
}

void QueueHandler::setQueue(ConcurrentQueue* q) {
	queue = q;
}

ConcurrentQueue* QueueHandler::getQueue() {
	return queue;
}

ConcurrentQueue* QueueHandler::unsetQueue() {
	ConcurrentQueue* q = queue;
	queue = nullptr;
	return q;
}

void QueueHandler::start() {
	if (!alive) {
		alive = true;
		keep_going = true;
		thread = new std::thread(&QueueHandler::run, this);
	}
}

void QueueHandler::kill() {
	mutex.lock();
	if (alive) {
		alive = false;
		mutex.unlock();
		cv.notify_one();
		thread->join();
		delete thread;
		thread = nullptr;
	}
	mutex.unlock();
}

void QueueHandler::run() {
	std::unique_lock<std::mutex> lock(mutex);
	while (alive) {
		cv.wait(lock, [this](){return alive && !keep_going;});
		keep_going = execute();
		lock.unlock();
	}
}

void QueueHandler::stop() {
	std::lock_guard<std::mutex> lock(mutex);
	if (alive) {
		alive = false;
		cv.notify_one();
	}
}

void QueueHandler::notify() {
	std::lock_guard<std::mutex> lock(mutex);
	keep_going = true;
	cv.notify_one();
}
