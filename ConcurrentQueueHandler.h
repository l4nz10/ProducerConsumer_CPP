#ifndef CONCURRENTQUEUEHANDLER_H_
#define CONCURRENTQUEUEHANDLER_H_

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "QueueHandler.h"

class ConcurrentQueueHandler : public QueueHandler {
protected:
	std::thread* thread;
	std::mutex mutex;
	std::condition_variable cv;
	bool dead, keep_going;
	ConcurrentQueueHandler(std::string name);
	virtual void run();
public:
	virtual Queue * setQueue(Queue * queue);
	virtual Queue * unsetQueue();
	virtual bool start();
	virtual bool stop();
	virtual bool isRunning();
	virtual void awake();
	virtual ~ConcurrentQueueHandler();
};

#endif /* QUEUEHANDLER_H_ */
