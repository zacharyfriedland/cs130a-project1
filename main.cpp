// main.cpp
#include "tst.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
  TST tst = TST();
  tst.insert("dog");
  tst.insert("lion");
  tst.insert("ball");
  tst.insert("cat");
  tst.insert("wolf");
  tst.insert("dog");
  tst.printInOrder();
  // cout << tst.lookup("lion") << endl;
  // cout << tst.lookup("army") << endl;
  // tst.range_search("dog to rat");

  tst.remove("ball");
  tst.remove("wolf");
  tst.remove("cat");
  tst.remove("dog");
  tst.remove("dog");
  tst.remove("lion");


  cout << "------" << endl;
  tst.printInOrder();

  return 0;
}
