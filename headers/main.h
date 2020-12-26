#ifndef MAIN_H
#define MAIN_H

#include <debugger.h>
#include <domino.h>

#include <vector>

// Vars
std::vector<domino> dominoList;
std::vector<std::vector<domino>> listPerms;
int start = -1;

// Methods
std::vector<std::vector<domino>> getListPerms(std::vector<domino>& _dominoList);
std::vector<std::vector<domino>> getListOfDoms(
    std::vector<std::vector<domino>> state);

void swap();
void permutation();

#endif