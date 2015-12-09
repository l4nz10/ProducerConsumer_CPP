#include <iostream>

#include "ConcurrentQueueHandler.h"

ConcurrentQueueHandler::ConcurrentQueueHandler(std::string name) : QueueHandler(name),
																																	 thread(nullptr),
																																	 dead(true),
																																	 keep_going(true) {}

ConcurrentQueueHandler::~ConcurrentQueueHandler() {
	stop();
}

Queue * ConcurrentQueueHandler::setQueue(Queue* newQueue) {
	stop();
	return QueueHandler::setQueue(newQueue);
}

Queue * ConcurrentQueueHandler::unsetQueue() {
	return ConcurrentQueueHandler::setQueue(nullptr);
}

bool ConcurrentQueueHandler::start() {
	if (dead && hasQueue()) {
		dead = false;
		keep_going = true;
		thread = new std::thread(&ConcurrentQueueHandler::run, this);
		return true;
	} else {
		return false;
	}
}

bool ConcurrentQueueHandler::stop() {
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

bool ConcurrentQueueHandler::isRunning() {
	return !dead;
}

void ConcurrentQueueHandler::run() {
	do {
		bool result = execute();
		std::unique_lock<std::mutex> lock(mutex);
		keep_going = result;
		cv.wait(lock, [this](){return dead || keep_going;}); // if it's dead or can keep going, exit from wait
		lock.unlock();
	} while (!dead);
}

void ConcurrentQueueHandler::awake() {
	mutex.lock();
	keep_going = true;
	mutex.unlock();
	cv.notify_one();
}
