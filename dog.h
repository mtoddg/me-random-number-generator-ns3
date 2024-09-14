
#include <iostream>
using namespace std;

class dog {
  //char myName[10];
  public: 
  int nums;
  void print_nums();
};

void dog::print_nums()
{
  cout << "test" << nums << endl;
  //cout << this->myName << endl;
}

