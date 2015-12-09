#ifndef FACTORY_H_
#define FACTORY_H_

#include <string>

#include "Producer.h"
#include "Consumer.h"
#include "Queue.h"

class Factory {
public:
	static Factory * getFactory(int typecode);
	virtual Producer * createProducer() = 0;
	virtual Consumer * createConsumer() = 0;
	virtual Queue * createQueue(unsigned int size) = 0;
	virtual ~Factory();
};

#endif /* FACTORY_H_ */
