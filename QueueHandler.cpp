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

void QueueHandler::setQueue(ConcurrentQueue* q) {
	queue = q;
}

ConcurrentQueue * QueueHandler::getQueue() {
	return queue;
}

ConcurrentQueue * QueueHandler::unsetQueue() {
	ConcurrentQueue* q = queue;
	queue = nullptr;
	return q;
}

void QueueHandler::start() {
	if (dead) {
		dead = false;
		keep_going = true;
		thread = new std::thread(&QueueHandler::run, this);
		return;
	}
}

void QueueHandler::stop() {
	if (!dead) {
		dead = true;
		cv.notify_all();
		thread->join();
		delete thread;
		thread = nullptr;
		return;
	}
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
	cv.notify_all();
}
