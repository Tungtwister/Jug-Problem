//non-graph structures used: priority queues, stacks, queues, vectors
#ifndef __JUG_H
#define __JUG_H
 
#include <string.h>
#include <sstream>
#include <queue>
#include <stack>
#include <vector>
 
using namespace std;

struct node
{
    int a;
    int b;
    int dist;
    bool visited;
    //6 different options
    node* neighbors[6];
    node* prev;
    node(int, int );
};

class Compare
{
    public:
    bool operator () (node* left, node* right)
    {
        return(left->dist > right->dist);
    }
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //anything else you need
        int Ca, Cb, N;
        int costs[6];
        node ***graph;
        void createGraph();
};

#endif