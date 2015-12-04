#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>

#include "CommandPrompt.h"
#include "string_utils.h"

CommandPrompt::CommandPrompt() {
  welcome();
}

CommandPrompt::~CommandPrompt() {
  for (int i = 0; i < queues.size(); i++) {
    delete queues[i];
  }
  for (int i = 0; i < producers.size(); i++) {
    delete producers[i];
  }
  for (int i = 0; i < consumers.size(); i++) {
    delete consumers[i];
  }
  delete factory;
}

void CommandPrompt::welcome() {
  clearScreen();
  std::cout << "Welcome to the producer-consumer sample project.\n\n";
  selectFactory();
}

void CommandPrompt::selectFactory() {
  while (true) {
    std::cout << "\n";
    std::cout << "Please pick first a factory type:" << "\n";
    std::cout << "\n";
    std::cout << "* (1) Basic Factory. Simple factory with concurrent producers and consumers." << std::endl;
    std::cout << "\n";
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    int typecode;
    if (string_utils::is_number(input)) {
      typecode = std::stoi(input);
    } else {
      std::cout << "Invalid input." << std::endl;
      continue;
    }
    factory = Factory::getFactory(typecode);
    if (factory == nullptr) {
      std::cout << "Not a valid factory." << std::endl;
    } else {
      break;
    }
  }
  mainMenu();
}

void CommandPrompt::mainMenu() {
  while (true) {
    std::cout << "\n";
    std::cout << "Type a command (type 'help' or 'h' for help)" << std::endl;
    std::cout << "\n";
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> args = string_utils::split(input);
    if (args.empty()) {
      std::cout << "Invalid input." << std::endl;
    } else {
      std::string command = args[0];
      args.erase(args.begin());
      clearScreen();
      if (command == "create") {
        createEntities(args);
      } else if (command == "remove" || command == "delete") {
        removeEntities(args);
      } else if (command == "list" || command == "l") {
        listEntities(args);
      } else if (command == "setq") {
        setQueue(args);
      } else if (command == "unsetq") {
        unsetQueue(args);
      } else if (command == "start") {
        startQueueHandler(args);
      } else if (command == "stop") {
        stopQueueHandler(args);
      } else if (command == "help" || command == "h") {
        showHelp();
      } else if (command == "quit" || command == "q") {
        std::cout << "Bye." << std::endl;
        break;
      } else {
        std::cout << "Sorry. Command not recognized." << std::endl;
      }
    }
  }
}

void CommandPrompt::createEntities(std::vector<std::string> args) {
  int numOfProds = 0, numOfCons = 0, numOfQueues = 0;
  int i = 0;
  while (i < args.size()) {
    if (args[i] == "p") {
      producers.push_back(factory->createProducer());
      numOfProds++;
    } else if (args[i] == "c") {
      consumers.push_back(factory->createConsumer());
      numOfCons++;
    } else if (args[i] == "q") {
      queues.push_back(factory->createQueue(1000));
      numOfQueues++;
    } else {
      std::cout << "Encountered invalid syntax. Halting." << std::endl;
      break;
    }
    i++;
  }
  std::cout << "Created "
            << numOfProds << " producers, "
            << numOfCons << " consumers, "
            << numOfQueues << " queues." << std::endl;
}

void CommandPrompt::removeEntities(std::vector<std::string> args) {
  std::vector<int> prodNumbers, consNumbers, queueNumbers;

  int index = 0;
  while (index < args.size()) {
    if (args[index] == "p") {
      index++;
      // Inner loop for scanning the producer ids
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          prodNumbers.push_back(std::stoi(args[index]));
        } else {
          index--; // move the index back by one position so on the next outer cycle
                   // it will be back to the current position
          break;
        }
        index++;
      }
    } else if (args[index] == "c") {
      index++;
      // Inner loop for scanning the consumer ids
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          consNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else if (args[index] == "q") {
      index++;
      // Inner loop for scanning the queue ids
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          queueNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else {
      std::cout << "Encountered invalid syntax. Halting." << std::endl;
      break;
    }
    index++;
  }

  std::sort(prodNumbers.begin(), prodNumbers.end(), std::greater<int>());
  std::sort(consNumbers.begin(), consNumbers.end(), std::greater<int>());
  std::sort(queueNumbers.begin(), queueNumbers.end(), std::greater<int>());

  std::vector<int> deletedProds;
  std::vector<int> deletedCons;
  std::vector<int> deletedQueues;

  for (int i = 0; i < prodNumbers.size(); i++) {
    if (prodNumbers[i] >= 0 && prodNumbers[i] < producers.size()) {
      delete producers[prodNumbers[i]];
      producers[prodNumbers[i]] = producers.back();
      producers.pop_back();
      deletedProds.push_back(prodNumbers[i]);
    }
  }
  for (int i = 0; i < consNumbers.size(); i++) {
    if (consNumbers[i] >= 0 && consNumbers[i] < consumers.size()) {
      delete consumers[consNumbers[i]];
      consumers[consNumbers[i]] = consumers.back();
      consumers.pop_back();
      deletedCons.push_back(consNumbers[i]);
    }
  }
  for (int i = 0; i < queueNumbers.size(); i++) {
    if (queueNumbers[i] >= 0 && queueNumbers[i] < queues.size()) {
      delete queues[queueNumbers[i]];
      queues[queueNumbers[i]] = queues.back();
      queues.pop_back();
      deletedQueues.push_back(queueNumbers[i]);
    }
  }

  if (deletedProds.empty() && deletedCons.empty() && deletedQueues.empty()) {
    std::cout << "Nothing removed." << std::endl;
  } else {
    std::cout << "Deleted";
    if (!deletedProds.empty()) {
      std::cout << " Producer";
      for (int j = 0; j < deletedProds.size(); j++) {
        std::cout << " #" << deletedProds[j];
      }
      std::cout << ".";
    }
    if (!deletedCons.empty()) {
      std::cout << " Consumer";
      for (int j = 0; j < deletedCons.size(); j++) {
        std::cout << " #" << deletedCons[j];
      }
      std::cout << ".";
    }
    if (!deletedQueues.empty()) {
      std::cout << " Queue";
      for (int j = 0; j < deletedQueues.size(); j++) {
        std::cout << " #" << deletedQueues[j];
      }
      std::cout << ".";
    }
    std::cout << std::endl;
  }
}

void CommandPrompt::listEntities(std::vector<std::string> args) {
  bool showProds = false, showCons = false, showQueues = false;

  if (args.empty()) {
    std::cout << "Invalid syntax." << std::endl;
    return;
  }
  for (int i = 0; i < args.size(); i++) {
    if (args[i] == "p") {
      showProds = true;
    } else if (args[i] == "c") {
      showCons = true;
    } else if (args[i] == "q") {
      showQueues = true;
    } else {
      std::cout << "Invalid syntax." << std::endl;
      return;
    }
  }
  if (showProds) {
    std::cout << "* Producers:" << std::endl;
    if (producers.empty()) {
      std::cout << "  <empty>" << std::endl;
    } else {
      for (int i = 0; i < producers.size(); i++) {
        std::cout << "(" << i << "): " << "Producer";
        if (producers[i]->isRunning()) {
          std::cout << " *running*";
        }
        std::cout << "\n";
      }
    }
  }
  if (showCons) {
    std::cout << "* Consumers:" << std::endl;
    if (consumers.empty()) {
      std::cout << "  <empty>" << std::endl;
    } else {
      for (int i = 0; i < consumers.size(); i++) {
        std::cout << "(" << i << "): " << "Consumer";
        if (consumers[i]->isRunning()) {
          std::cout << " *running*";
        }
        std::cout << "\n";
      }
    }
  }
  if (showQueues) {
    std::cout << "* Queues:" << std::endl;
    if (queues.empty()) {
      std::cout << "  <empty>" << std::endl;
    } else {
      for (int i = 0; i < queues.size(); i++) {
        std::cout << "(" << i << "): " << "Queue (" << queues[i]->size() << " elements)" << std::endl;
      }
    }
  }
}

void CommandPrompt::setQueue(std::vector<std::string> args) {
  int queueNumber = -1;
  std::vector<int> prodNumbers, consNumbers;

  if (args.size() < 3) {
    std::cout << "Invalid syntax." << std::endl;
    return;
  }
  // Check if the first argument is actually a number
  if (string_utils::is_number(args[0])) {
    queueNumber = std::stoi(args[0]);
  } else {
    std::cout << "Invalid syntax." << std::endl;
    return;
  }
  // Check if the delimiter is present
  if (args[1] != "to") {
    std::cout << "Invalid syntax." << std::endl;
    return;
  }

  int index = 2;
  while (index < args.size()) {
    if (args[index] == "p") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        prodNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          prodNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else if (args[index] == "c") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        consNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          consNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else {
      std::cout << "Invalid syntax." << std::endl;
      return;
    }
    index++;
  }
  // Check if the first argument is inside the valid queues range
  if (!(queueNumber >= 0 && queueNumber < queues.size())) {
    std::cout << "Not a valid queue number." << std::endl;
    return;
  }

  for (int i = 0; i < prodNumbers.size(); i++) {
    if (prodNumbers[i] >= 0 && prodNumbers[i] < producers.size()) {
      producers[prodNumbers[i]]->setQueue(queues[queueNumber]);
      std::cout << "Queue " << queueNumber << " set for Producer " << prodNumbers[i] << std::endl;
    }
  }
  for (int i = 0; i < consNumbers.size(); i++) {
    if (consNumbers[i] >= 0 && consNumbers[i] < consumers.size()) {
      consumers[consNumbers[i]]->setQueue(queues[queueNumber]);
      std::cout << "Queue " << queueNumber << " set for Consumer " << consNumbers[i] << std::endl;
    }
  }
}

void CommandPrompt::unsetQueue(std::vector<std::string> args) {
  std::vector<int> prodNumbers, consNumbers;

  int index = 0;
  while (index < args.size()) {
    if (args[index] == "p") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        prodNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          prodNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else if (args[index] == "c") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        consNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          consNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else {
      std::cout << "Invalid syntax." << std::endl;
      return;
    }
    index++;
  }

  for (int i = 0; i < prodNumbers.size(); i++) {
    if (prodNumbers[i] >= 0 && prodNumbers[i] < producers.size()) {
      producers[prodNumbers[i]]->safeUnsetQueue();
      std::cout << "Queue unset for Producer " << prodNumbers[i] << std::endl;
    }
  }
  for (int i = 0; i < consNumbers.size(); i++) {
    if (consNumbers[i] >= 0 && consNumbers[i] < consumers.size()) {
      consumers[consNumbers[i]]->safeUnsetQueue();
      std::cout << "Queue unset for Consumer " << consNumbers[i] << std::endl;
    }
  }
}

void CommandPrompt::startQueueHandler(std::vector<std::string> args) {
  std::vector<int> prodNumbers, consNumbers;

  int index = 0;
  while (index < args.size()) {
    if (args[index] == "p") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        prodNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          prodNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else if (args[index] == "c") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        consNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          consNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else {
      std::cout << "Invalid syntax." << std::endl;
      return;
    }
    index++;
  }

  for (int i = 0; i < prodNumbers.size(); i++) {
    if (prodNumbers[i] >= 0 && prodNumbers[i] < producers.size()) {
      if (producers[prodNumbers[i]]->start()) {
        std::cout << "Starting Producer " << prodNumbers[i] << std::endl;
      }
    }
  }
  for (int i = 0; i < consNumbers.size(); i++) {
    if (consNumbers[i] >= 0 && consNumbers[i] < consumers.size()) {
      if (consumers[consNumbers[i]]->start()) {
        std::cout << "Starting Consumer " << consNumbers[i] << std::endl;
      }
    }
  }
}

void CommandPrompt::stopQueueHandler(std::vector<std::string> args) {
  std::vector<int> prodNumbers, consNumbers;

  int index = 0;
  while (index < args.size()) {
    if (args[index] == "p") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        prodNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          prodNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else if (args[index] == "c") {
      index++;
      if (index >= args.size() || !string_utils::is_number(args[index])) {
        std::cout << "Invalid syntax." << std::endl;
        return;
      } else {
        consNumbers.push_back(std::stoi(args[index]));
      }
      index++;
      while (index < args.size()) {
        if (string_utils::is_number(args[index])) {
          consNumbers.push_back(std::stoi(args[index]));
        } else {
          index--;
          break;
        }
        index++;
      }
    } else {
      std::cout << "Invalid syntax." << std::endl;
      return;
    }
    index++;
  }

  for (int i = 0; i < prodNumbers.size(); i++) {
    if (prodNumbers[i] >= 0 && prodNumbers[i] < producers.size()) {
      if (producers[prodNumbers[i]]->stop()) {
        std::cout << "Stopping Producer " << prodNumbers[i] << std::endl;
      }
    }
  }
  for (int i = 0; i < consNumbers.size(); i++) {
    if (consNumbers[i] >= 0 && consNumbers[i] < consumers.size()) {
      if (consumers[consNumbers[i]]->stop()) {
        std::cout << "Stopping Consumer " << consNumbers[i] << std::endl;
      }
    }
  }
}

void CommandPrompt::showHelp() {
  std::string commands = "- create  ( p | c | q )+ \n"
                         "  \"Create one or more producer, consumer and/or queue.\"\n"
                         "- remove, delete  ( p (#)+ | c (#)+ | q (#)+ )+ \n"
                         "  \"Remove one or more producer, consumer and/or queue of number '#'.\"\n"
                         "- list, l   p | c | q  \n"
                         "  \"Show a list of producers, consumers and/or queues.\"\n"
                         "- setq  #  to  ( p (#)+ | c (#)+ )+ \n"
                         "  \"Set the queue of number '#' to the producers and/or consumers of number '#'.\"\n"
                         "- unsetq  ( p (#)+ | c (#)+ )+ \n"
                         "  \"Unset the queue from the producers and/or consumers of number '#'.\"\n"
                         "- start  ( p (#)+ | c (#)+ )+ \n"
                         "  \"Start the producers and/or consumers of number '#'.\"\n"
                         "- stop  ( p (#)+ | c (#)+ )+ \n"
                         "  \"Stop the producers and/or consumers of number '#'.\"\n"
                         "- help, h \n"
                         "  \"Show this message.\"\n"
                         "- quit, q \n"
                         "  \"Quit the application.\"";
  std::cout << "* List of commands:" << "\n" << commands << std::endl;
}

void CommandPrompt::clearScreen() {
  std::cout << std::string(100, '\n');
}
