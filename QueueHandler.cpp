#include <iostream>

#include "QueueHandler.h"

QueueHandler::QueueHandler(std::string name, ConcurrentQueue* queue) : name(name),
																																			 queue(queue),
																																			 thread(nullptr),
																																			 running(false),
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
	mutex.lock();
	if (!running) {
		running = true;
		keep_going = true;
		mutex.unlock();
		thread = new std::thread(&QueueHandler::run, this);
		return;
	}
	mutex.unlock();
}

void QueueHandler::kill() {
	mutex.lock();
	if (running) {
		running = false;
		mutex.unlock();
		cv.notify_one();
		thread->join();
		delete thread;
		thread = nullptr;
		return;
	}
	mutex.unlock();
}

void QueueHandler::run() {
	std::unique_lock<std::mutex> lock(mutex);
	while (running) {
		cv.wait(lock, [this](){return running && !keep_going;});
		keep_going = execute();
		lock.unlock();
	}
}

void QueueHandler::stop() {
	mutex.lock();
	if (running) {
		running = false;
		mutex.unlock();
		cv.notify_one();
		return;
	}
	mutex.unlock();
}

void QueueHandler::awake() {
	mutex.lock();
	keep_going = true;
	mutex.unlock();
	cv.notify_one();
}
