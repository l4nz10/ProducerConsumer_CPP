#ifndef CONCURRENTQUEUE_H_
#define CONCURRENTQUEUE_H_

#include <mutex>
#include <queue>

class ConcurrentQueue {
private:
	std::mutex mutex;
	std::queue<int> queue;
	const unsigned int MAX_SIZE;
public:
	explicit ConcurrentQueue(unsigned int size);
	bool push(int element);
	bool pop();
	int get();
	int get_and_pop();
	unsigned int size();
	virtual ~ConcurrentQueue();
};

#endif /* CONCURRENTQUEUE_H_ */
