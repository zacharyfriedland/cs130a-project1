// main.cpp
// Zachary Friedland
#include "tst.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char** argv) {
  TST* tst = new TST();
  
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
        cout << tst->lookup(param) << endl;
      }
      else if(input[i] == "insert"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        tst->insert(param);
      }
      else if(input[i] == "delete"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        tst->remove(param);
      }
      else if(input[i] == "range_search"){
        string param = input[i+1] + " " + input[i+2] + " " + input[i+3];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        tst->range_search(param);
      }
    }
  }
  return 0;
}
