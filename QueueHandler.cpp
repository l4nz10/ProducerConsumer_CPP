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

ConcurrentQueue * QueueHandler::setQueue(ConcurrentQueue* q) {
	stop();
	ConcurrentQueue * oldQueue = queue;
	queue = q;
	return oldQueue;
}

ConcurrentQueue * QueueHandler::getQueue() {
	return queue;
}

ConcurrentQueue * QueueHandler::unsetQueue() {
	stop();
	ConcurrentQueue * oldQueue;
	queue = nullptr;
	return oldQueue;
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
		cv.notify_one();
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
	cv.notify_one();
}
