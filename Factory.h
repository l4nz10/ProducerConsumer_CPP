/*
 * Factory.h
 *
 *  Created on: 30 nov 2015
 *      Author: valerio
 */

#ifndef FACTORY_H_
#define FACTORY_H_

#include "Producer.h"
#include "Consumer.h"
#include "ConcurrentQueue.h"

class Factory {
public:
	static Factory* getFactory(int typecode);
	virtual Producer* createProducer() = 0;
	virtual Consumer* createConsumer() = 0;
	virtual ConcurrentQueue* createQueue(int size) = 0;
	virtual ~Factory();
};

#endif /* FACTORY_H_ */
