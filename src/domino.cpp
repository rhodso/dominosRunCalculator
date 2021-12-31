// Source file auto-generated using CPP-Getter-Setter-Generator

// Includes
#include <domino.h>

// Constructor and Destructor
domino::domino() {}
domino::domino(int _topNum, int _btmNum) {
  topNum = _topNum;
  btmNum = _btmNum;
}
domino::~domino() {}

// Getters and Setters
int domino::getTopNum() {
  return topNum;  
}
int domino::getBtmNum() {
  return btmNum;
}

void domino::setTopNum(int _topNum) { topNum = _topNum; }
void domino::setBtmNum(int _btmNum) { btmNum = _btmNum; }

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
  s += "|";

  // If the number is < 10, then add a space to the front so it's aligned
  // correctly
  s += std::to_string(this->getBtmNum());
  return s;
}

void domino::flip(){
  int tmp = btmNum;
  btmNum = topNum;
  topNum = tmp;
}

int domino::getScore(){
  return topNum + btmNum;
}