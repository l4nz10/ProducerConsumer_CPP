/*
 * BasicFactory.h
 *
 *  Created on: 30 nov 2015
 *      Author: valerio
 */

#ifndef BASICFACTORY_H_
#define BASICFACTORY_H_

#include "Factory.h"

class BasicFactory: public Factory {
private:
	int producerCtr, consumerCtr, queueCtr;
public:
	BasicFactory();
	virtual Producer* createProducer();
	virtual Consumer* createConsumer();
	virtual ConcurrentQueue* createQueue(int size);
	virtual ~BasicFactory();
};

#endif /* BASICFACTORY_H_ */
