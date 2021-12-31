#ifndef MAIN_H
#define MAIN_H

#include <debugger.h>
#include <domino.h>

#include <mutex>
#include <thread>
#include <vector>
#include <map>

// Vars
std::vector<domino> dominoList;
std::vector<std::vector<domino>> listPerms;
int start = -1;
std::mutex mtx;

// Methods
void getPermutation(std::vector<domino> _current, std::vector<domino> _available, int _starter);
std::string getStringList(std::vector<domino> _lst);
int getListScore(std::vector<domino> _lst);
bool compareDom(domino d1, domino d2);
std::vector<domino> checkDupeDoms(std::vector<domino> _dominoList);

#endif