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
  bool getUsed();
  int getID();
  std::string getID_S();
  bool getFlipped();

  void setTopNum(int _topNum);
  void setBtmNum(int _btmNum);
  void setUsed(bool _used);
  void setFlipped(bool _flipped);

  // Other methods
  static domino generateDomino();
  std::string to_string();

  // Overloading <
  bool operator<(domino& rhs) {
    if (ID == rhs.getID()) {
      return ID < rhs.getID();
    } else {
      return ID < rhs.getID();
    }
  }

 private:
  // Variables
  int topNum;
  int btmNum;
  bool used;
  bool flipped;
  int ID;
  inline static int count = 0;
};
#endif