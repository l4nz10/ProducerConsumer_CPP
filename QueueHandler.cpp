#include "QueueHandler.h"

QueueHandler::QueueHandler(std::string name) : name(name), queue(nullptr) {}

Queue * QueueHandler::setQueue(Queue * newQueue) {
  Queue * oldQueue = queue;
  queue = newQueue;
  return oldQueue;
}

Queue * QueueHandler::unsetQueue() {
  return QueueHandler::setQueue(nullptr);
}

const Queue * QueueHandler::getQueue() {
  return queue;
}

bool QueueHandler::hasQueue() {
  return queue != nullptr;
}

QueueHandler::~QueueHandler() {}
