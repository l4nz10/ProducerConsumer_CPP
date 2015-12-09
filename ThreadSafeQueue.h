#ifndef CONCURRENTQUEUE_H_
#define CONCURRENTQUEUE_H_

#include <mutex>
#include <queue>
#include <string>
#include <vector>

#include "Queue.h"
#include "ConcurrentQueueHandler.h"

class ThreadSafeQueue : public Queue {
protected:
	std::mutex mutex;
	std::vector<ConcurrentQueueHandler *> producers;
	std::vector<ConcurrentQueueHandler *> consumers;
	virtual void awakeProducers();
	virtual void awakeConsumers();
public:
	explicit ThreadSafeQueue(std::string name, unsigned int size = 1000);
	virtual void addProducer(ConcurrentQueueHandler * producer);
	virtual void addConsumer(ConcurrentQueueHandler * consumer);
	virtual void removeProducer(ConcurrentQueueHandler * producer);
	virtual void removeConsumer(ConcurrentQueueHandler * consumer);
	virtual bool push(int element);
	virtual bool pop();
	virtual int get();
	virtual int get_and_pop();
	virtual unsigned int size();
	virtual ~ThreadSafeQueue();
};

#endif /* CONCURRENTQUEUE_H_ */
