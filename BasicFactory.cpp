#include <sstream>
#include <iostream>

#include "BasicFactory.h"
#include "ThreadSafeQueue.h"

BasicFactory::BasicFactory() : producerCtr(0), consumerCtr(0), queueCtr(0) {}

Producer * BasicFactory::createProducer() {
	std::ostringstream converter;
	converter << ++producerCtr;
	return new Producer("Producer "+converter.str());
}

Consumer * BasicFactory::createConsumer() {
	std::ostringstream converter;
	converter << ++consumerCtr;
	return new Consumer("Consumer "+converter.str());
}

Queue * BasicFactory::createQueue(unsigned int size) {
	std::ostringstream converter;
	converter << ++queueCtr;
	return new ThreadSafeQueue("Queue "+converter.str(), size);
}

BasicFactory::~BasicFactory() {}
