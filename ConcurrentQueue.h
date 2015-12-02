#ifndef CONCURRENTQUEUE_H_
#define CONCURRENTQUEUE_H_

#include <mutex>
#include <queue>
#include <vector>

#include "QueueHandler.h"

class ConcurrentQueue {
protected:
	std::mutex mutex;
	std::queue<int> queue;
	std::vector<QueueHandler *> producers;
	std::vector<QueueHandler *> consumers;
	const unsigned int MAX_SIZE;
public:
	explicit ConcurrentQueue(unsigned int size);
	virtual void addProducer(QueueHandler * producer);
	virtual void addConsumer(QueueHandler * consumer);
	virtual void removeProducer(QueueHandler * producer);
	virtual void removeConsumer(QueueHandler * consumer);
	virtual void awakeProducers();
	virtual void awakeConsumers();
	virtual bool push(int element);
	virtual bool pop();
	virtual int get();
	virtual int get_and_pop();
	virtual unsigned int size();
	virtual ~ConcurrentQueue();
};

#endif /* CONCURRENTQUEUE_H_ */
