#include <iostream>

#include "QueueHandler.h"

QueueHandler::QueueHandler(std::string name) : name(name),
																							 queue(nullptr),
																							 thread(nullptr),
																							 dead(true),
																							 keep_going(true) {}

QueueHandler::~QueueHandler() {
	stop();
}

ThreadSafeQueue * QueueHandler::setQueue(ThreadSafeQueue* q) {
	stop();
	ThreadSafeQueue * oldQueue = queue;
	queue = q;
	return oldQueue;
}

ThreadSafeQueue * QueueHandler::getQueue() {
	return queue;
}

bool QueueHandler::hasQueue() {
	return queue != nullptr;
}

ThreadSafeQueue * QueueHandler::unsetQueue() {
	return QueueHandler::setQueue(nullptr);
}

bool QueueHandler::start() {
	if (dead && hasQueue()) {
		dead = false;
		keep_going = true;
		thread = new std::thread(&QueueHandler::run, this);
		return true;
	} else {
		return false;
	}
}

bool QueueHandler::stop() {
	if (!dead) {
		dead = true;
		cv.notify_one();
		thread->join();
		delete thread;
		thread = nullptr;
		return true;
	} else {
		return false;
	}
}

bool QueueHandler::isRunning() {
	return !dead;
}

void QueueHandler::run() {
	do {
		bool result = execute();
		std::unique_lock<std::mutex> lock(mutex);
		keep_going = result;
		cv.wait(lock, [this](){return dead || keep_going;}); // if it's dead or can keep going, exit from wait
		lock.unlock();
	} while (!dead);
}

void QueueHandler::awake() {
	mutex.lock();
	keep_going = true;
	mutex.unlock();
	cv.notify_one();
}
