#include <iostream>
#include "Jug.h"
using namespace std;

int main() {
  Jug j(3,5,4,1,2,3,4,5,6);
  string solution;
  j.solve(solution);
  cout << solution << endl;
  cout << endl;
  
   string solution2;
   Jug head( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
   if(head.solve(solution2) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution2 << endl;

}