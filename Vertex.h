#ifndef VERTEX_H_
#define VERTEX_H_

#include <string>
#include <list>
#include <map>
#include <climits>
// #include "Jug.h"

using namespace std;

class Vertex {
public:
  list<pair<int, int> > neighbors;
  // string label;
  // int distance;
  // string color;
  Vertex* prev;
  int bucket1;
  int bucket2;
  
  
  Vertex(int a, int b) : bucket1(a), bucket2(b), prev(0) {}
  ~Vertex(){}
};

#endif /* VERTEX_H_ */