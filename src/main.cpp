#include <main.h>

#include <algorithm>
#include <iostream>
#include <thread>

void printState(std::vector<domino> state) {
  std::string s = "";
  for (domino d : state) {
    s = s + d.to_string() + " , ";
  }
  if (!s.empty()) {
    s.pop_back();
    s.pop_back();
    s.pop_back();
  }
  debugger::log(s);
}

void printStateIgnore(std::vector<domino> state) {
  std::string s = "";
  for (domino d : state) {
    s = s + d.to_string() + " , ";
  }
  if (!s.empty()) {
    s.pop_back();
    s.pop_back();
    s.pop_back();
  }
  debugger::p(s);
}

void updateOutval(std::vector<domino> _tmp) {
  stateList.push_back(_tmp);
  printStateIgnore(_tmp);
  debugger::log("Updated outval");
}

std::vector<domino> getListOfDoms(std::vector<domino> state) {
  // Fucking bullshit if this works
  debugger::log("Curent dominos in state");
  for (domino d : state) {
    for (domino dm : dominoList) {
      if (dm.getID() == d.getID()) {
        dm.setUsed(true);
      }
    }
  }

  // Get list of valid dominos we could add to current state
  domino back = state.back();
  std::vector<domino> validDoms;
  debugger::log("***Starting gathering list of valid doms***");

  std::vector<domino> tmpDominoList;
  for (domino d : dominoList) {
    bool u = false;
    for (domino dm : state) {
      if (dm.getID() == d.getID()) {
        u = true;
        break;
      }
    }
    if (!u) {
      tmpDominoList.push_back(d);
    }
  }

  for (domino d : tmpDominoList) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    debugger::log("Testing domino with ID" + d.getID_S());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    debugger::log("DominoUsed for this dom is " + std::to_string(d.getUsed()));

    if (d.getID() == back.getID()) {
      // Dom is invalid because it's this dom
      debugger::log(
          "Dom is invalid due to it being the same dom we're testing");
    } else if (d.getUsed()) {
      // Dom is invalid
      debugger::log("Dom is invalid due to already being used in this state");
    } else {
      if ((d.getBtmNum() == back.getBtmNum()) ||
          (d.getTopNum() == back.getBtmNum())) {
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
  }

  debugger::log("***Finished getting list of valid doms***");
  debugger::log("ValidDomSize is " + std::to_string(validDoms.size()));

  if (validDoms.size() == 0) {  // No valid doms, add state to outVal and
                                // finish with this permutation
    debugger::log("validDoms size is 0");
    debugger::log("State is:");
    printState(state);
    updateOutval(state);
    return state;
  } else {  // At least one valid dom, save state here and pick one
    debugger::log("validDoms size is " + std::to_string(validDoms.size()));
    int i = 1;
    for (domino d : validDoms) {
      debugger::log("i = " + std::to_string(i));
      i++;
      debugger::log("Starting with domino " + d.getID_S());
      std::vector<domino> newState;  // dupe state here

      for (domino dm : state) {
        newState.push_back(dm);
      }

      debugger::log("***New state created***");
      debugger::log("New state size is " + std::to_string(newState.size()));

      d.setUsed(true);  // TODO setUsed state isn't being updated
      newState.push_back(d);

      // Newstate created, list
      debugger::log("new state is:");
      printState(state);

      debugger::log("Starting getListOfDoms");
      newState = getListOfDoms(newState);
      debugger::log("Next i is " + std::to_string(i));
      newState.clear();
      debugger::log("Moving to next state inside getListOfDoms");
    }
    validDoms.clear();
    debugger::log("Done with this state branching");
  }
  return state;
}

std::vector<std::vector<domino>> getListPerms(
    std::vector<domino>& _dominoList) {
  // List
  std::vector<std::vector<domino>> outVal;
  std::vector<domino> tmp;

  debugger::log("dominoList size is " + std::to_string(dominoList.size()));

  // Currently, list is empty (blank state)
  // Start recursion
  if (start != -1) {
    debugger::log("Starter is set");
    // Starter is set, will try that first
    domino d = domino(start, start);
    debugger::log("Started with domino " + d.getID_S());
    // Create a state and push it to the back
    std::vector<domino> state;
    debugger::log("Created blank state");
    std::vector<domino> dms;

    d.setUsed(true);
    state.push_back(d);

    debugger::log("Starting getListOfDoms");

    debugger::log("Current state is ");
    printState(state);

    tmp = getListOfDoms(state);
    tmp.clear();  // Ensure that the temp state is cleared

    // Reset for next iteration
    // d.setUsed(false);
  } else {
    debugger::log("Starter not set");
  }

  for (domino d : dominoList) {
    debugger::log("Started with domino " + d.getID_S());
    // Create a state and push it to the back
    std::vector<domino> state;
    debugger::log("Created blank state");
    std::vector<domino> dms;

    d.setUsed(true);
    state.push_back(d);

    debugger::log("Starting getListOfDoms");

    debugger::log("Current state is ");
    printState(state);

    tmp = getListOfDoms(state);

    tmp.clear();  // Ensure that the temp state is cleared

    // Reset for next iteration
    // d.setUsed(false);
  }

  return outVal;
}

int main() {
  // Seed RNG
  srand(time(0));

  debugger::setDebug(false);

  debugger::p("Starting...");

  // Set starter
  start = 12;  // Starter is double 12

  // Create list of 10 dominos
  for (int i = 0; i < 10; i++) {
    domino d = domino::generateDomino();
    dominoList.push_back(d);
  }

  // Output dominos
  std::string s = "Dominos list is:\n";
  for (domino d : dominoList) {
    s += d.to_string() + " , ";
  }
  if (!s.empty()) {
    s.pop_back();
    s.pop_back();
  }
  debugger::p(s);

  debugger::log("dominoList size is " + std::to_string(dominoList.size()));

  debugger::p("Calculating...");
  listPerms = getListPerms(dominoList);

  debugger::log("Done");
  debugger::p("Took " + debugger::getExecTime_S() + "s");

  debugger::p("Finding best possible move....");
  std::vector<int> value;
  std::vector<int> trueValue;

  for (std::vector<domino> run : stateList) {
    int val = 0;
    int tVal = 0;

    for (domino d : run) {
      tVal += d.getTopNum();
      tVal += d.getBtmNum();
    }
    trueValue.push_back(tVal);

    if (start != -1) {
      if (run.front().getTopNum() == start) {
        // Give bonus 100 pts if it starts with the correct thing
        val = 100;
      }
    }

    // Add values
    val += tVal;
    value.push_back(val);
  }

  // Find best
  int max = 0;
  int idx = 0;

  int max_t = 0;
  int idx_t = 0;

  // Find value and index of highest score
  for (int i = 0; i < value.size(); i++) {
    if (value[i] > max) {
      max = value[i];
      idx = i;
    }
  }

  // Find value and index of highest true score
  for (int i = 0; i < trueValue.size(); i++) {
    if (trueValue[i] > max_t) {
      max_t = trueValue[i];
      idx_t = i;
    }
  }

  debugger::p("Highest score that starts with the starter is: " +
              std::to_string(max));
  printStateIgnore(stateList[idx]);

  if (idx != idx_t) {
    debugger::p("Highest score is: " + std::to_string(max_t));
    printStateIgnore(stateList[idx_t]);
  }

  // Done?
}