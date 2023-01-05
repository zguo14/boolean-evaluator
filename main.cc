#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
  FormulaParser *fp = new FormulaParser(formulaStr);
  TreeNode *root = fp->getTreeRoot();
  AssignmentParser *ap = new AssignmentParser(assignmentStr);
  std::map<std::string, bool> amap = ap->parseAssignment();
  bool res = root->evaluate(amap);
  std::cout << res << std::endl;
  // amap.clear();
  delete root;
  delete ap;
  delete fp;
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    getline(std::cin, line);
    if(!std::cin) {
      break;
    }

    int pos = line.find(";");
    if (pos == -1) {
      std::cout << "Error: invalid input"<< std::endl;
      continue;
    }

    formulaStr = line.substr(0, pos);
    if (formulaStr == "") {
      std::cout << "Error: invalid input"<< std::endl;
      continue;
    }
    // std::cout << pos;
    if (pos == line.size() - 1) {
      assignmentStr = "";
    } else {
      assignmentStr = line.substr(pos + 1, line.size() - 1 - pos);
    }

    try {
      parseLine(line, formulaStr, assignmentStr);
    } catch (const char* msg) {
      std::cout << msg << std::endl;
    }
  }
}
