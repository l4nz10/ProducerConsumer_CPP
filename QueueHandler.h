#ifndef QUEUEHANDLER_H_
#define QUEUEHANDLER_H_

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadSafeQueue;

class QueueHandler {
protected:
	std::string name;
	ThreadSafeQueue * queue;
	std::thread* thread;
	std::mutex mutex;
	std::condition_variable cv;
	bool dead, keep_going;
	QueueHandler(std::string name);
	virtual void run();
	virtual bool execute() = 0;
public:
	virtual ThreadSafeQueue * setQueue(ThreadSafeQueue * queue);
	virtual ThreadSafeQueue * getQueue();
	virtual ThreadSafeQueue * unsetQueue();
	virtual bool hasQueue();
	virtual bool start();
	virtual bool stop();
	virtual bool isRunning();
	virtual void awake();
	virtual ~QueueHandler();
};

#endif /* QUEUEHANDLER_H_ */
