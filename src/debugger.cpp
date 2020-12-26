#include "debugger.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <thread>

// Constructors
debugger::debugger() {}

bool debugger::debug{false};  // Give the var it's value
std::time_t debugger::initTime{std::chrono::system_clock::to_time_t(
    std::chrono::system_clock::now())};  // Give start time at init

// Getters and setters
bool debugger::getDebug() { return debugger::debug; }
void debugger::setDebug(bool _debug) { debugger::debug = _debug; }

// Methods
void debugger::log(std::string msg) {
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  if (debug) {  // Only log it if it's being told to
    logIgnore(msg);
  }
}

void debugger::logIgnore(std::string msg) {
  // Get current time, and format as s.ms
  // I tried to get it formatted as 3dp but instead it wants to do 6, which are
  // always 0. Which is nice
  std::string timeStr = "[";
  timeStr +=
      std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::system_clock::now() -
                         std::chrono::system_clock::from_time_t(initTime))
                         .count() /
                     1000.0f);
  timeStr += "]";

  // Remove endl's
  timeStr.erase(remove(timeStr.begin(), timeStr.end(), '\n'), timeStr.end());

  // Format full output as [time_since_init] \t msg, and output
  std::cout << timeStr << " " << msg << std::endl;
}

void debugger::logErr(std::string msg) {
  // Get current time, and format as s.ms
  // I tried to get it formatted as 3dp but instead it wants to do 6, which are
  // always 0. Which is nice
  std::string timeStr = "[";
  timeStr +=
      std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::system_clock::now() -
                         std::chrono::system_clock::from_time_t(initTime))
                         .count() /
                     1000.0f);
  timeStr += "]";

  // Remove endl's
  timeStr.erase(remove(timeStr.begin(), timeStr.end(), '\n'), timeStr.end());

  // Format full output as [time_since_init] \t msg, and output
  // But this time to cerr for errors
  std::cerr << timeStr << " " << msg << std::endl;
}
