#include <main.h>

#include <algorithm>
#include <iostream>
#include <thread>
#include <sstream>

std::string getStringList(std::vector<domino> _lst){
  // Convert a list of dominos to a string
  std::string outStr = "";
  for(domino d : _lst){
    outStr += d.to_string() + " ";
  }
  return outStr;
}

int getListScore(std::vector<domino> _lst){
  // Get the score of dominos played from a list
  int sum = 0;
  for(domino d : _lst){
    sum += d.getScore();
  }
  return sum;
}

bool compareDom(domino d1, domino d2){
  //Check for match when unflipped
  if(d1.getTopNum() == d2.getTopNum()){
    if(d1.getBtmNum() == d2.getBtmNum()){
      return true;
    }
  }

  //Compare against d2, but inverted
  if(d1.getBtmNum() == d2.getTopNum()){
    if(d1.getTopNum() == d2.getBtmNum()){
      return true;
    }
  }

  return false;
}

void getPermutation(std::vector<domino> _current, std::vector<domino> _available, int _starter){
  // Debug info
  debugger::log("Entered getPermutation");
  debugger::log("Current is" + getStringList(_current));
  debugger::log("Available is" + getStringList(_available));
  debugger::log("Starter is " + std::to_string(_starter));

  //Get a list of dominos that can fit
  std::vector<domino> canFit = {};
  for(domino d : _available){
    if(d.getTopNum() == _starter){
      canFit.push_back(d);
    }
    if(d.getBtmNum() == _starter){
      d.flip();
      canFit.push_back(d);
    }
  }
  
  debugger::log("canFit size is " + std::to_string(canFit.size()));

  //Determine next action based on size of list
  if(canFit.size() == 0){
    debugger::log("No dominos will fit, adding finished permutation to list");
    listPerms.push_back(_current);
  } else {
    debugger::log("At least 1 domino will fit, calculating full permutation");
    //For each domino in canFit
    for(domino d : canFit){

      //Create new vectors
      std::vector<domino> newAvailable = {};
      std::vector<domino> newCurrent = _current;

      //Copy the current available dominos apart from the one we're currently using
      for(domino dom : _available){
        if(!compareDom(d, dom)){
          newAvailable.push_back(dom);
        }
      }

      //Add the current domino to _current
      newCurrent.push_back(d);

      debugger::log("Everything set up, starting to calculate next permutation...\n");
      getPermutation(newCurrent, newAvailable, d.getBtmNum());
    }
  }
}

std::vector<domino> checkDupeDoms(std::vector<domino> _dominoList){
  // Create an emptty list
  std::vector<domino> noDupes = {};

  // For each domino in the list, check if it's a dupe
  for(domino d : _dominoList){
    bool isDupe = false;
    for(domino dom : noDupes){
      // If it is, set isDupe to true and break
      if(compareDom(dom, d)){
        isDupe = true;
        break;
      }
    }
    if(!isDupe){
      // If not, add to noDupes list
      noDupes.push_back(d);
    }
  }

  return noDupes;
}

int main() {
  // Seed RNG
  srand(time(0));
  debugger::setDebug(false);

  debugger::p("Starting...");
  debugger::p("Enter dominos in the format \"x x\" or enter nothing to continue:");

  bool isFirst = true;
  while(true){
    debugger::log("Getting input for new domino");
    std::string dom;
    std::getline(std::cin, dom);

    // Check if the line is just 'r' and it's the first domino
    if(dom == "r" && isFirst){
      // Generate 12 random dominos, add them to the list, and continue
      for(int i = 0; i < 12; i++){
        domino d = domino::generateDomino();
        dominoList.push_back(d);
        debugger::p("Added " + d.to_string());
      }

      continue;
    }

    // Not reading a random signal, check for empty string
    debugger::log("Read \"" + dom + "\"");
    if(dom == ""){
      // Empty line, either process or quit
      if(dominoList.size() < 1){
        // No dominos entered, quit
        debugger::p("No dominos entered, quitting");
        return 0;
      } else {
        // Break and start process
        break;
      }
    } else {
      debugger::log("Creating vars");
      //Split string into parts
      std::vector<std::string> parts;
      const std::string& dm = dom;
      std::istringstream iss(dom);

      debugger::log("Splitting string");
      for(std::string s; iss >> s; ){
        debugger::log("Added " + s);
        parts.push_back(s);
      }

      debugger::log("Done splitting string");

      //Get parts
      int top;
      int btm;
      debugger::log("Getting parts");
      for(std::string s : parts){
        debugger::log(s + " ");
      }
      try{
        top = std::stoi(parts[0]);
        btm = std::stoi(parts[1]);
        debugger::log("Split string");
      } catch(const std::exception& e){
        debugger::p("Error parsing domino: " + dom);
      }

      debugger::log("Creating domino");
      //Create domino
      domino d = domino(top, btm);
      dominoList.push_back(d);
    }
  }

  //Get starter
  debugger::p("Enter starter:");
  std::string starterDoubleDom;
  std::getline(std::cin, starterDoubleDom); 
  start = std::stoi(starterDoubleDom);

  // Check for starter dom
  int testIdx = 0;
  bool haveStart = false;
  for(domino d : dominoList){
    if(d.getTopNum() == start && d.getBtmNum() == start){
      // We have the starter, remove from the list and tell the user
      haveStart = true;
      break;
    }
    testIdx++;
  }

  // Test for starter double
  if(haveStart){
    // Remove the domino at index i, and inform the user they
    // have the starter domino
    dominoList.erase(dominoList.begin() + testIdx);
    debugger::p("You have the double to start, so this has been removed from the list of available dominos");
  }

  debugger::p("Checking for duplicate dominos");
  dominoList = checkDupeDoms(dominoList);

  debugger::p("Calculating...");

  //Do the calculations
  std::vector<domino> blank = {};
  getPermutation(blank, dominoList, start);
  std::cout << std::endl;
  
  //Do some more calculations if we can't find one to match the starter
  if(listPerms[0].size() == 0){
    //No valid routes found from given starter
    debugger::p("No valid routes found from given starter, will try and find permutation from available dominos");
    for(domino d : dominoList){
      //Create new vectors
      std::vector<domino> newAvailable = {};
      std::vector<domino> newCurrent = {d};

      //Copy the current available dominos apart from the one we're currently using
      for(domino dom : dominoList){
        if(!compareDom(d, dom)){
          newAvailable.push_back(dom);
        }
      }

      //Get the permutations
      getPermutation(newCurrent, newAvailable, d.getBtmNum());
      d.flip();
      getPermutation(newCurrent, newAvailable, d.getBtmNum());

    }
  }

  //If literally nothing fits
  if(listPerms.size() == 0){
    debugger::p("Could not find any permutations or anything that matched. Good luck!");
    return 0;
  }

  //List found permutations
  debugger::p("Permutations list:");
  int i = 0;
  for(std::vector<domino> dList : listPerms){
    std::string toPrint = "P";
    if(i < 10){ toPrint += "0";}
    toPrint += std::to_string(i) + ", Score " + std::to_string(getListScore(dList)) + ", Order: " + getStringList(dList);
    debugger::p(toPrint);
    i++;
  }  
  
  //Find best permutation
  debugger::p("\nFinding best permutation...");
  std::cout << std::endl;
  std::vector<domino> bestPerm = {};
  for(std::vector<domino> p : listPerms){
    if(getListScore(bestPerm) < getListScore(p)){
      bestPerm = p;
    }
  }

  debugger::p("Best permutation has score " + std::to_string(getListScore(bestPerm)) + ", and has order: " + getStringList(bestPerm));
  //Print out
  if(haveStart){
    debugger::p("Since you have the double, don't forget to play it first");
  }
  return 0;
}