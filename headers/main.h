#ifndef MAIN_H
#define MAIN_H

#include <debugger.h>
#include <domino.h>

#include <mutex>
#include <thread>
#include <vector>

// Vars
std::vector<domino> dominoList;
std::vector<std::vector<domino>> listPerms;
std::vector<std::vector<domino>> stateList;
int start = -1;
std::mutex mtx;

// Methods
std::vector<std::vector<domino>> getListPerms(std::vector<domino>& _dominoList);
void getListOfDoms(std::vector<domino> state);

void swap();
void permutation();

#endif