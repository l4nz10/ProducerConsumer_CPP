#include <iostream>
#include <thread>
#include <queue>

#include "Factory.h"

int main() {

	Factory* factory = Factory::getFactory(1);

	ConcurrentQueue* queue = factory->createQueue(100);
	Producer* producer = factory->createProducer();
	Consumer* consumer = factory->createConsumer();

	producer->setQueue(queue);
	consumer->setQueue(queue);

	producer->start();
	consumer->start();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::cout << "> > > > > KILLING." << "\n";

	producer->stop();
	consumer->stop();

	delete producer;
	delete consumer;
	delete queue;
	delete factory;
}
