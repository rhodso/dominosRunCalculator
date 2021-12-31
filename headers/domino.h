// Header file auto-generated using CPP-Getter-Setter-Generator
#ifndef DOMINO_H
#define DOMINO_H

// Includes
#include <debugger.h>
#include <stdio.h>
#include <string.h>

#include <random>

class domino {
 public:
  // Constructor and Destructor
  domino();
  domino(int _topNum, int _btmNum);
  ~domino();

  // Getters and Setters
  int getTopNum();
  int getBtmNum();

  void setTopNum(int _topNum);
  void setBtmNum(int _btmNum);

  // Other methods
  static domino generateDomino();
  std::string to_string();
  void flip();
  int getScore();

 private:
  // Variables
  int topNum;
  int btmNum;
};
#endif