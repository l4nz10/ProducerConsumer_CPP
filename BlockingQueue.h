#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_

#include <mutex>
#include <condition_variable>
#include <queue>

class BlockingQueue {
private:
	std::mutex mutex;
	std::condition_variable cv;
	std::queue<int> queue;
	const unsigned int MAX_SIZE;
public:
	explicit BlockingQueue(unsigned int size);
	bool push(int element);
	bool pop();
	int front();
	int back();
	int frontPop();
	unsigned int size();
	virtual ~BlockingQueue();
};

#endif /* BLOCKINGQUEUE_H_ */
