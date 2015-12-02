#ifndef QUEUEHANDLER_H_
#define QUEUEHANDLER_H_

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class ConcurrentQueue;

class QueueHandler {
protected:
	std::string name;
	ConcurrentQueue * queue;
	std::thread* thread;
	std::mutex mutex;
	std::condition_variable cv;
	bool dead, keep_going;
	QueueHandler(std::string name);
	virtual void run();
	virtual bool execute() = 0;
public:
	virtual void setQueue(ConcurrentQueue * queue);
	virtual ConcurrentQueue * getQueue();
	virtual ConcurrentQueue * unsetQueue();
	virtual void start();
	virtual void stop();
	virtual void awake();
	virtual ~QueueHandler();
};

#endif /* QUEUEHANDLER_H_ */
