#ifndef COMMAND_PROMPT_
#define COMMAND_PROMPT_

#include <string>
#include <vector>

#include "Factory.h"

class CommandPrompt {
private:
  Factory * factory;
  std::vector<Producer *> producers;
  std::vector<Consumer *> consumers;
  std::vector<ConcurrentQueue *> queues;
  void welcome();
  void selectFactory();
  void mainMenu();
  void createEntities(std::vector<std::string> args);
  void removeEntities(std::vector<std::string> args);
  void listEntities(std::vector<std::string> args);
  void setQueue(std::vector<std::string> args);
  void unsetQueue(std::vector<std::string> args);
  void startQueueHandler(std::vector<std::string> args);
  void stopQueueHandler(std::vector<std::string> args);
  void showHelp();
  void clearScreen();
public:
  CommandPrompt();
  virtual ~CommandPrompt();
};

#endif
