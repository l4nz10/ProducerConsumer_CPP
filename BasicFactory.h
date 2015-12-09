#ifndef BASICFACTORY_H_
#define BASICFACTORY_H_

#include "Factory.h"

class BasicFactory: public Factory {
private:
	int producerCtr, consumerCtr, queueCtr;
public:
	BasicFactory();
	virtual Producer * createProducer();
	virtual Consumer * createConsumer();
	virtual Queue * createQueue(unsigned int size);
	virtual ~BasicFactory();
};

#endif /* BASICFACTORY_H_ */
