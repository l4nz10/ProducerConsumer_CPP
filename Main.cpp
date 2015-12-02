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

	std::thread * prodThread, * consThread;

	prodThread = new std::thread(&Producer::execute, producer);
	consThread = new std::thread(&Consumer::execute, consumer);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::cout << "> > > > > KILLING." << "\n";

	producer->stop();
	consumer->stop();

	prodThread->join();
	consThread->join();

	delete prodThread;
	delete consThread;

	delete producer;
	delete consumer;
	delete queue;
	delete factory;
}
