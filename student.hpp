#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
  string username;
  int scoreCPP, scoreGDB, scoreAlgo;
  vector<string> notWork;
  vector<string> yesWork;
  bool inGroup;
};
