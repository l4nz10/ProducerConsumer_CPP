#include <iostream>

#include "QueueHandler.h"

QueueHandler::QueueHandler(std::string name, BlockingQueue* queue) : name(name), queue(queue), active(false) {}

QueueHandler::~QueueHandler() {
	kill();
}

void QueueHandler::setQueue(BlockingQueue* queue) {
	this->queue = queue;
}

BlockingQueue* QueueHandler::getQueue() {
	return queue;
}

BlockingQueue* QueueHandler::unsetQueue() {
	BlockingQueue* q = queue;
	queue = nullptr;
	return q;
}

void QueueHandler::start() {
	active = true;
	thread = new std::thread(&QueueHandler::execute, this);
}

void QueueHandler::kill() {
	active = false;
	std::cout << "["+name+"]: Killing...";
	thread->join();
	delete thread;
	std::cout << "done." << std::endl;
}
