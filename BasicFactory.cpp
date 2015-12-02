#include <sstream>
#include <iostream>

#include "BasicFactory.h"

BasicFactory::BasicFactory() : producerCtr(0), consumerCtr(0), queueCtr(0) {}

Producer* BasicFactory::createProducer() {
	std::ostringstream converter;
	converter << ++producerCtr;
	return new Producer("Producer "+converter.str());
}

Consumer* BasicFactory::createConsumer() {
	std::ostringstream converter;
	converter << ++consumerCtr;
	return new Consumer("Consumer "+converter.str());
}

ConcurrentQueue* BasicFactory::createQueue(int size) {
	return new ConcurrentQueue(size);
}

BasicFactory::~BasicFactory() {
	std::cout << "Destroying BasicFactory" << std::endl;
}
