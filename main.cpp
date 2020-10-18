// main.cpp
#include "tst.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char** argv) {
  TST tst = TST();
  vector<string> input;
  string keywords[4] = {"lookup", "insert", "delete", "range_search"};
  for(int i = 0; i < argc; i++){
    input.push_back(argv[i]);
  }

  for(int i = 1; i < input.size(); i++){
    if (find(begin(keywords), end(keywords), input[i]) != end(keywords)){
      if(input[i] == "lookup"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        cout << param << endl;
        tst.lookup(param);
      }
      else if(input[i] == "insert"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        cout << param << endl;
        tst.insert(param);
      }
      else if(input[i] == "delete"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        cout << param << endl;
        tst.remove(param);
      }
      else if(input[i] == "range_search"){
        string param = input[i+1] + " " + input[i+2] + " " + input[i+3];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        cout << param << endl;
        tst.lookup(param);
      }
    }
  }
  cout << endl;

  return 0;
}
