#ifndef QUEUEHANDLER_H_
#define QUEUEHANDLER_H_

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "ConcurrentQueue.h"

class QueueHandler {
protected:
	std::string name;
	ConcurrentQueue* queue;
	std::thread* thread;
	std::mutex mutex;
	std::condition_variable cv;
	bool alive, keep_going;
	QueueHandler(std::string name, ConcurrentQueue* queue);
	virtual void run();
	virtual bool execute() = 0;
public:
	virtual void setQueue(ConcurrentQueue* queue);
	virtual ConcurrentQueue* getQueue();
	virtual ConcurrentQueue* unsetQueue();
	virtual void start();
	virtual void kill();
	virtual void stop();
	virtual void notify();
	virtual ~QueueHandler();
};

#endif /* QUEUEHANDLER_H_ */
