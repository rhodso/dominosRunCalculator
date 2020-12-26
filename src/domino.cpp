// Source file auto-generated using CPP-Getter-Setter-Generator

// Includes
#include <domino.h>

// Constructor and Destructor
domino::domino() {
  ID = count;
  debugger::log("Created domino with ID " + std::to_string(ID));
  debugger::log("Domino is " + this->to_string());
  count++;
  used = false;
  flipped = false;
}
domino::domino(int _topNum, int _btmNum) {
  topNum = _topNum;
  btmNum = _btmNum;
}
domino::~domino() {}

// Getters and Setters
int domino::getTopNum() {
  if (flipped) {
    return btmNum;
  } else {
    return topNum;
  }
}
int domino::getBtmNum() {
  if (!flipped) {
    return btmNum;
  } else {
    return topNum;
  }
}
bool domino::getUsed() { return used; }
int domino::getID() { return ID; }
std::string domino::getID_S() {
  std::string s = std::to_string(this->ID) + " (" + this->to_string() + ")";
  return s;
}
bool domino::getFlipped() { return flipped; }

void domino::setTopNum(int _topNum) { topNum = _topNum; }
void domino::setBtmNum(int _btmNum) { btmNum = _btmNum; }
void domino::setUsed(bool _used) { used = _used; }
void domino::setFlipped(bool _flipped) { flipped = _flipped; }

// Other methods
domino domino::generateDomino() {
  // Get to RNs, max 12 for top and bottom
  domino d = domino();
  d.setTopNum(rand() % 13);
  d.setBtmNum(rand() % 13);

  return d;
}

std::string domino::to_string() {
  std::string s;

  // If the number is < 10, then add a space to the front so it's aligned
  // correctly
  if (this->getTopNum() < 10) {
    s += " " + std::to_string(this->getTopNum());
  } else {
    s += std::to_string(this->getTopNum());
  }

  // Add seperator
  s += " | ";

  // If the number is < 10, then add a space to the front so it's aligned
  // correctly
  if (this->getBtmNum() < 10) {
    s += " " + std::to_string(this->getBtmNum());
  } else {
    s += std::to_string(this->getBtmNum());
  }
  return s;
}
