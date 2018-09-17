#include "graph.h"
#include <cassert>
#include <stack>

graph::graph()
{
  int vertex;
  cin >> size;
  adjList.resize(size,NULL);
  for(int i = 0; i < size; ++i) {
	cin >> vertex;
    while(vertex != -1) {
      adjList[i] = new vnode(vertex,adjList[i]); // insert at begining
	  cin >> vertex;
    }
  }
}

int firstFalse(vector<bool> b)
{
  int i = 0;
  while(i < b.size() && b[i])
    i += 1;
  return i;
}
 
bool all(vector<bool> b)
{
  for(int i = 0; i < b.size(); ++i)
    if(!b[i])
      return false;
  return true;
}

void graph::dfs(vector<bool> &visited)
{
  int start = firstFalse(visited);
  int nbr, current = start;
  stack<int> S;
  vnodeptr cursor;
  visited[start] = true;
  S.push(start);
  // Supply the remaining code below
  while(!S.empty())
	{
		current = S.top();
		S.pop();
		for(cursor = adjList[current]; cursor != NULL; cursor = cursor->next)
		{
			nbr = cursor->vertex;
			if(visited[nbr] == false)
			{
				S.push(nbr);
				visited[nbr] = true;
				
			}
		}
		
	}   
}
bool graph::connected(int excluded = -1)
{
  	vector<bool> visited(size,false);
  	if(excluded != -1)
    	visited[excluded] = true;
  	// Supply the remaining code below
	dfs(visited);
	return all(visited);
}  
    
vector<int> graph::get_cutpoints()
{
  	vector<int> cutpts;
 	 // Supply the remaining code below
	for(int i = 0; i < size; i++)
	{
		if(!this->connected(i))
		{	
			cutpts.push_back(i);
		}
		
	}
	return cutpts;
}

  

