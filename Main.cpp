#include <iostream>
#include <thread>
#include <queue>

#include "Factory.h"
#include "CommandPrompt.h"

int main() {

	CommandPrompt commandPrompt;

	// Factory * factory = Factory::getFactory(1);
	//
	// Producer * producer = factory->createProducer();
	// Consumer * consumer = factory->createConsumer();
	// ConcurrentQueue * queue = factory->createQueue(1000);
	//
	// producer->setQueue(queue);
	// consumer->setQueue(queue);
	//
	// producer->start();
	// consumer->start();
	//
	// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//
	// std::cout << "> > > > > KILLING." << "\n";
	//
	// producer->stop();
	// consumer->stop();
	//
	// delete queue;
	// delete producer;
	// delete consumer;
	// delete factory;
}
