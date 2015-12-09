#ifndef QUEUE_H_
#define QUEUE_H_

#include <string>
#include <queue>

class Queue {
protected:
  std::string name;
  std::queue<int> queue;
  const unsigned int MAX_SIZE;
public:
  explicit Queue(std::string name, unsigned int capacity = 1000);
  virtual bool push(int element);
	virtual bool pop();
	virtual int get();
	virtual int get_and_pop();
	virtual unsigned int size();
  virtual unsigned int capacity();
  virtual ~Queue ();
};

#endif
