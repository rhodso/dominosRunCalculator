#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <string.h>

#include <chrono>
#include <iostream>

class debugger {
 public:
  // Constructor
  debugger();

  // Getters and setters
  static bool getDebug();
  static void setDebug(bool _debug);

  // Methods
  static void log(std::string msg);  // Log message if debug is enabled
  static void logIgnore(
      std::string msg);  // Log message regardless if debug is enabled or not
  static void logErr(std::string msg);
  static void p(std::string msg);  // Print message without time
  static double getExecTime();
  static std::string getExecTime_S();

 private:
  static bool debug;  // Wheather debug is enabled or not
  static std::time_t initTime;
};
#endif  // DEBUGGER_H
