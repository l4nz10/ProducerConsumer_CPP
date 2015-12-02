/*
 * Producer.h
 *
 *  Created on: 27 nov 2015
 *      Author: valerio
 */

#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <string>

#include "QueueHandler.h"

class Producer : public QueueHandler {
private:
	int counter;
public:
	Producer(std::string name, ConcurrentQueue* queue);
	Producer(std::string name);
	virtual void execute();
};

#endif /* PRODUCER_H_ */
