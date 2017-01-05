//non-graph structures used: priority queues, stacks, queues, vectors
#include "Jug.h"

node :: node(int capA, int capB)
{
    a = capA;
    b = capB;
    dist = -1;
    prev = NULL;
    visited = false;
    for(int i = 0; i < 6; ++i)
    {
        neighbors[i] = 0;
    }
}

Jug::Jug(int A,int B,int C,int cfA,int cfB,int ceA,int ceB,int cpAB,int cpBA)
{
    //capacites
    Ca = A;
    Cb = B;
    N = C;
    
    //costs
    costs[0] = cfA;
    costs[1]=cfB;
    costs[2]=ceA;
    costs[3]=ceB;
    costs[4]=cpAB;
    costs[5]=cpBA;
    
    //check for validation
    bool valid = true;
    for(int i = 0; i < 6; ++i)
    {
        if(costs[i] < 0)
        {
            valid = false;
            break;
        }
    }
    if(!((0 < Ca)&&(Ca <= Cb)) || !((N <= Cb)&&(Cb <= 1000)))
    {
        valid = false;
    }
    
    if(valid)
    {
        graph = new node**[Ca+1];
        for(int i = 0; i <= Ca; ++i)
        {
            graph[i] = new node*[Cb + 1];
            for(int j = 0; j <= Cb; ++j)
            {
                graph[i][j] = 0;
            }
        }
        createGraph();
    }
    else
    {
        graph = 0;
    }
}

Jug::~Jug() 
{
  if(graph)
  {
    for(int  i= 0; i <= Ca; ++i)
    {
      for(int j = 0; j <= Cb; ++j)
      {
        if(graph[i][j])
        {
          delete graph[i][j];
        }
      }
      delete graph[i];
    }
    delete graph;
  }
}

int Jug::solve(string &solution)
{
  if(graph)
  {
    graph[0][0]->dist = 0;
    priority_queue<node*, vector<node*>, Compare> wow;
    node *end=0;
    wow.push(graph[0][0]);
    //Dijkstra's
    while(!wow.empty())
    {
      node *top = wow.top();
      wow.pop();
      if(top->a == 0 && top->b == N)
      {
        end=top;
        break;
      }
      top->visited=true;
      for(int i = 0; i < 6 ; ++i)
      {
        if(top->neighbors[i])
        {
          if(!top->neighbors[i]->visited)
          {
            if(top->neighbors[i]->dist == -1)
            {
              top->neighbors[i]->dist = top->dist+costs[i];
              top->neighbors[i]->prev = top;
              wow.push(top->neighbors[i]);
            } 
            else if(top->neighbors[i]->dist > top->dist+costs[i])
            {
              top->neighbors[i]->dist = top->dist+costs[i];
              top->neighbors[i]->prev = top;
            }
          }
        }
      }
    }
    if(end)
    {
      stack<string> path;
      int totalCost=0;
      while(end != graph[0][0])
      {
        int i=0;
        for(i = 0; i < 6; ++i) {
          if(end->prev->neighbors[i] == end)
          {
            totalCost += costs[i];
            break;
          }
        }
        if(i == 0)
        {
            path.push("fill A\n");
        }
        else if(i == 1)
        {
            path.push("fill B\n");
        }
        else if(i == 2)
        {
            path.push("empty A\n");
        }
        else if(i == 3)
        {
            path.push("empty B\n");
        }
        else if(i == 4)
        {
            path.push("pour A B\n");
        }
        else if(i == 4)
        {
            path.push("pour B A\n");
        }
        else
        {
            path.push("\n");
        }
        end = end->prev;
      }
      
      solution="";
      while(!path.empty())
      {
        solution += path.top();
        path.pop();      
      }
      stringstream ss;
      string temp;
      ss << totalCost;
      ss >> temp;
      solution += "success ";
      solution += temp;
      return 1;
    }
    else
    {
      solution = "";
      return 0;
    }
  }
  solution = "";
  return -1;
}
void Jug::createGraph()
{
  graph[0][0] = new node(0,0);
  queue<node*> q;
  q.push(graph[0][0]);
  while(!q.empty())
  {
    node* top = q.front();
    q.pop();
    if(top->a < Ca)
    {
      if(!graph[Ca][top->b])
      {
        graph[Ca][top->b] = new node(Ca,top->b);
        q.push(graph[Ca][top->b]);
      }
      top->neighbors[0] = graph[Ca][top->b];
    }
    if(top->b < Cb)
    {
      if(!graph[top->a][Cb])
      {
        graph[top->a][Cb] = new node(top->a,Cb);
        q.push(graph[top->a][Cb]);
      }
      top->neighbors[1] = graph[top->a][Cb];
    }
    if(top->a)
    {
      if(!graph[0][top->b])
      {
        graph[0][top->b] = new node(0,top->b);
        q.push(graph[0][top->b]);
      }
      top->neighbors[2] = graph[0][top->b];
    }
    if(top->b)
    {
      if(!graph[top->a][0])
      {
        graph[top->a][0] = new node(top->a,0);
        q.push(graph[top->a][0]);
      }
      top->neighbors[3] = graph[top->a][0];
    }
    if(top->a > 0 && top->b < Cb)
    {
      int newA = top->a;
      int newB = top->b;
      while(newA > 0 && newB < Cb)
      {
        newA--;
        newB++;
      }
      if(!graph[newA][newB])
      {
        graph[newA][newB] = new node(newA,newB);
        q.push(graph[newA][newB]);
      }
      top->neighbors[4] = graph[newA][newB];
    }
    if(top->b > 0 && top->a < Ca)
    {
      int newA = top->a;
      int newB = top->b;
      while(newB > 0 && newA < Ca)
      {
        newA++;
        newB--;
      }
      if(!graph[newA][newB])
      {
        graph[newA][newB] = new node(newA,newB);
        q.push(graph[newA][newB]);
      }
      top->neighbors[5] = graph[newA][newB];
    }
  }
}

