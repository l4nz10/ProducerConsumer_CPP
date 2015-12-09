#ifndef QUEUEHANDLER_H_
#define QUEUEHANDLER_H_

#include <string>

#include "Queue.h"

class QueueHandler {
protected:
  std::string name;
  Queue * queue;
  QueueHandler(std::string name);
  virtual bool execute() = 0;
public:
  virtual Queue * setQueue(Queue * queue);
  virtual Queue * unsetQueue();
  virtual const Queue * getQueue();
  virtual bool hasQueue();
  virtual ~QueueHandler ();
};

#endif
