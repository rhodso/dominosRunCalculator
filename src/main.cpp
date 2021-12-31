#include <main.h>

#include <algorithm>
#include <iostream>
#include <thread>
#include <sstream>

std::string getStringList(std::vector<domino> _lst){
  std::string outStr = "";
  for(domino d : _lst){
    outStr += d.to_string() + " ";
  }
  return outStr;
}

int getListScore(std::vector<domino> _lst){
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

  //Flip D1 and turn it into d3
  domino d3 = d1;
  d3.flip();

  //Compare against d2
  if(d3.getTopNum() == d2.getTopNum()){
    if(d3.getBtmNum() == d2.getBtmNum()){
      return true;
    }
  }

  return false;
}

void getPermutation(std::vector<domino> _current, std::vector<domino> _available, int _starter){
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
  std::vector<domino> noDupes = {};
  for(domino d : _dominoList){
    bool isDupe = false;
    for(domino dom : noDupes){
      if(compareDom(dom, d)){
        isDupe = true;
        break;
      }
    }
    if(!isDupe){
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

  if(debugger::getDebug()){
    //Set list of dominos

    dominoList.push_back(domino(2,1));
    dominoList.push_back(domino(2,2));
    dominoList.push_back(domino(2,3));
    dominoList.push_back(domino(3,4));
    dominoList.push_back(domino(4,5));
    dominoList.push_back(domino(5,6));

    //Set starter
    // Set starter
    start = 12;  // Starter is double 1

  }else{
    debugger::p("Enter dominos in the format \"x x\" or enter nothing to continue:");
    while(true){
      debugger::setDebug(false);
      debugger::log("Getting input for new domino");
      std::string dom;
      std::getline(std::cin, dom);
      debugger::log("Read \"" + dom + "\"");
      if(dom == ""){
        if(dominoList.size() < 1){
          debugger::p("No dominos entered, quitting");
          return 0;
        } else {
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

    debugger::p("Checking for duplicate dominos");
    dominoList = checkDupeDoms(dominoList);

    debugger::p("Calculating...");
  }

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
  debugger::p("Listing permutations:");
  int i = 0;
  for(std::vector<domino> dList : listPerms){
    debugger::p("P" + std::to_string(i) + ", Score " + std::to_string(getListScore(dList)) + ", Order: " + getStringList(dList));
    i++;
  }  
  
  //Find best permutation
  debugger::p("Finding best permutation:");
  std::vector<domino> bestPerm = {};
  for(std::vector<domino> p : listPerms){
    if(getListScore(bestPerm) < getListScore(p)){
      bestPerm = p;
    }
  }

  //Print out
  debugger::p("Best permutation has score " + std::to_string(getListScore(bestPerm)) + ", and has order: " + getStringList(bestPerm));
  return 0;
}