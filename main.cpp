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
  string argument = argv[1];

  string word;
  for(int i = 0; i < argument.size(); i++){
    if(argument[i] == ' '){
      input.push_back(word);
      word = "";
    }
    else if(i == argument.size() - 1){
      word += argument[i];
      input.push_back(word);
    }
    else{
      word += argument[i];
    }
  }


  for(int i = 0; i < input.size(); i++){
    if (find(begin(keywords), end(keywords), input[i]) != end(keywords)){
      if(input[i] == "lookup"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        cout << tst->lookup(param) << endl;
        i++;
      }
      else if(input[i] == "insert"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        tst->insert(param);
        i++;
      }
      else if(input[i] == "delete"){
        string param = input[i+1];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        tst->remove(param);
        i++;
      }
      else if(input[i] == "range_search"){
        string param = input[i+1] + " " + input[i+2] + " " + input[i+3];
        param.erase(remove(param.begin(), param.end(), ','), param.end());
        tst->range_search(param);
        i+=3;
      }
    }
  }
  return 0;
}
