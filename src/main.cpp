#include <main.h>

#include <algorithm>
#include <iostream>
#include <thread>

std::vector<std::vector<domino>> updateOutval(
    std::vector<std::vector<domino>> _tmp,
    std::vector<std::vector<domino>> outVal) {
  for (std::vector<domino> v : _tmp) {
    outVal.push_back(v);
  }
  return outVal;
}

std::vector<std::vector<domino>> getListOfDoms(
    std::vector<std::vector<domino>> state,
    std::vector<std::vector<domino>> outVal) {
  // Get list of valid dominos we could add to current state
  domino back = state.back().back();
  std::vector<domino> validDoms;
  debugger::log("Starting gathering list of valid doms");
  for (domino d : dominoList) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    debugger::log("Testing domino with ID" + d.getID_S());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if (d.getID() == back.getID()) {
      // Dom is invalid because it's this dom
      debugger::log(
          "Dom is invalid due to it being the same dom we're testing");
    } else if (d.getUsed() == true) {
      // Dom is invalid
      debugger::log("Dom is invalid due to already being used in this state");
    } else if ((d.getBtmNum() == state.back().back().getBtmNum()) ||
               (d.getTopNum() == state.back().back().getBtmNum())) {
      // Dom is valid

      // Determine if the dom is flipped or not
      if (d.getTopNum() == back.getBtmNum()) {
        d.setFlipped(false);
      } else {
        d.setFlipped(true);
      }

      debugger::log("Dom is valid, pushing to back");
      validDoms.push_back(d);

    } else {
      // Dom is invalid
      debugger::log("Dom is invalid due to spots mismatch");
    }
  }

  debugger::log("ValidDomSize is " + std::to_string(validDoms.size()));

  if (validDoms.size() == 0) {  // No valid doms, add state to outVal and finish
                                // with this permutation
    debugger::log("validDoms size is 0");
    return state;
  } else {  // At least one valid dom, save state here and pick one
    debugger::log("validDoms size is " + std::to_string(validDoms.size()));
    for (domino d : validDoms) {
      debugger::log("Starting with domino " + d.getID_S());
      std::vector<std::vector<domino>> newState;  // dupe state here

      for (std::vector<domino> v : state) {
        std::vector<domino> tmp;
        for (domino dm : v) {
          tmp.push_back(dm);
        }
        newState.push_back(tmp);
      }

      debugger::log("***New state created***");
      debugger::log("New state size is " + std::to_string(newState.size()));
      std::vector<domino> dms;

      d.setUsed(true);  // TODO setUsed state isn't being updated
      dms.push_back(d);
      newState.push_back(dms);

      // Newstate created, list
      std::string s = "new state is: \n";
      for (std::vector<domino> v : state) {
        for (domino dm : v) {
          s += dm.to_string() + " , ";
        }
        s += "\n";
      }
      if (!s.empty()) {
        s.pop_back();
        s.pop_back();
        s.pop_back();
      }
      debugger::log(s);

      debugger::log("Starting getListOfDoms");
      newState = getListOfDoms(newState, outVal);
      outVal = updateOutval(newState, outVal);

      // Reset for next iteration
      // d.setUsed(false);
    }
  }
}

std::vector<std::vector<domino>> getListPerms(
    std::vector<domino>& _dominoList) {
  // List
  std::vector<std::vector<domino>> outVal;
  std::vector<std::vector<domino>> tmp;

  debugger::log("dominoList size is " + std::to_string(dominoList.size()));

  // Currently, list is empty (blank state)
  // Start recursion
  if (start != -1) {
    debugger::log("Starter is set");
    // Starter is set, will try that first
    std::vector<std::vector<domino>> state;
    std::vector<domino> dms;
    dms.push_back(domino(start, start));
    state.push_back(dms);
    tmp = getListOfDoms(state, outVal);
    outVal = updateOutval(tmp, outVal);
    tmp.clear();  // Ensure that the temp state is cleared
  } else {
    debugger::log("Starter not set");
  }

  for (domino d : dominoList) {
    debugger::log("Started with domino " + d.getID_S());
    // Create a state and push it to the back
    std::vector<std::vector<domino>> state;
    debugger::log("Created blank state");
    std::vector<domino> dms;
    d.setUsed(true);
    dms.push_back(d);
    state.push_back(dms);
    debugger::log("Starting getListOfDoms");
    tmp = getListOfDoms(state, outVal);
    debugger::log("Done, updating outVal");
    outVal = updateOutval(tmp, outVal);
    tmp.clear();  // Ensure that the temp state is cleared

    // Reset for next iteration
    // d.setUsed(false);
  }

  return outVal;
}

int main() {
  // Seed RNG
  srand(time(0));

  debugger::setDebug(true);

  debugger::logIgnore("Starting...");

  // Set starter
  // start = 12; //Starter is double 12

  // Create list of 10 dominos
  for (int i = 0; i < 10; i++) {
    domino d = domino::generateDomino();
    dominoList.push_back(d);
  }

  // Output dominos
  std::string s = "";
  for (domino d : dominoList) {
    s += d.to_string() + " , ";
  }
  if (!s.empty()) {
    s.pop_back();
    s.pop_back();
  }
  debugger::log(s);

  debugger::log("dominoList size is " + std::to_string(dominoList.size()));

  debugger::log("Starting generation");
  listPerms = getListPerms(dominoList);

  debugger::log("Done generating");
  debugger::log(std::to_string(listPerms.size()));

  for (std::vector<domino> v : listPerms) {
    std::string s = "";
    for (domino d : v) {
      s += d.to_string() + " , ";
    }
    if (!s.empty()) {
      s.pop_back();
      s.pop_back();
    }
    debugger::log(s);
  }

  // Done?
}