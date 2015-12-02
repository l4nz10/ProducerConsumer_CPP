// #include <iostream>
//
// #include "CommandPrompt.h"
//
// void CommandPrompt::welcome() {
//   std::cout << "Welcome to the producer-consumer sample project." << std::endl;
//   selectFactory();
// }
//
// void CommandPrompt::selectFactory() {
//   while (true) {
//     std::cout << "Please pick first a factory type:" << std::endl;
//     std::cout << "* (1) Basic Factory. Simple factory with concurrent producers and consumers." << std::endl;
//     int typecode;
//     std::cin >> typecode;
//     factory = Factory::getFactory(typecode);
//     if (factory == nullptr) {
//       std::cout << "Not a valid factory." << std::endl;
//     } else {
//       break;
//     }
//   }
//   mainMenu();
// }
//
// void CommandPrompt::mainMenu() {
//   while (true) {
//     std::cout << "Select an action:" << std::endl;
//     std::cout << "* (1) Create a new producer;" << std::endl;
//     std::cout << "* (2) Create a new consumer;" << std::endl;
//     std::cout << "* (3) Create a new queue;" << std::endl;
//     std::cout << "* (4) Manage producers;" << std::endl;
//     std::cout << "* (5) Manage consumers;" << std::endl;
//     std::cout << "* (6) Manage queues;" << std::endl;
//     std::cout << "* (0) Quit." << std::endl;
//     int action;
//     std::cin >> action;
//     switch (action) {
//       case 1:
//         createProducer();
//         break;
//       case 2:
//         createConsumer();
//         break;
//       case 3:
//         createQueue();
//         break;
//       case 4:
//         manageProducer();
//         break;
//       case 5:
//         manageConsumer();
//         break;
//       case 6:
//         // Manage queues
//         break;
//       case 0:
//         std::cout << "Bye." << std::endl;
//         return;
//       default:
//         std::cout << "Not a valid action." << std::endl;
//     }
//   }
// }
