// Project 5
#ifndef maze_h
#define maze_h

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);
      void print(int,int,int,int);
      bool isLegal(int i, int j);
      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
      void mapMazeToGraph(graph &g);
      void nonrecursivefind(graph &g, int &n);
	  void recursivefind(graph &g, int &n, int &i);
	  void reset(graph &g);
	  vector <int> visited; // keep track of visisted
	  vector <int> direction; // Keep track of path.
	  int Rows();
	  int Cols();
	   bool path;
   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;
       // check if it has a path
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
  
	  
	  
};
// resets graph to re find path. 
void maze::reset(graph &g)
{
	g.clearVisit();
	visited.push_back(0);
	g.visit(0);
	direction.clear();
	path=false;	
}
int maze::Cols()
{
	return cols;
}
int maze::Rows()
{
	return rows;
	
}
void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
	map[i][j] = n;
}

int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
	return map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	 fin >> x;
	 if (x == 'O')
            value[i][j] = true;
	 else
	    value[i][j] = false;
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
	node n;
	int x;
	int y;
	edge e;
	int count =0;
	for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
			
			if (value[i][j]==true)
			{
				n.setId(count);
				g.addNode(n);
				setMap( i, j, count);
				
			}
			else 
			{
				setMap(i, j, -1);
				
			}
			count++;
		}
			
	}
		count = 0;
	
for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
		  if (value[i][j]==true)
		   {
		   	
		   	for (int k = 0; k < g.numNodes(); k++)
				{
					if (count == g.getNode(k).getId())
						x = k;
				}
		   	
		   	
		   	 if (i+1 < rows)	
		   	{
		   	if (map[i+1][j] != -1 )
		   	 	{
		   	 			for (int k = 0; k < g.numNodes(); k++)
				{
					if (count == g.getNode(k).getId())
						y = k;
					}
		   		g.addEdge(x,y);
					}
			}
			
			if (i-1 > -1)	
		   	{
		   	if (map[i-1][j] != -1 )
		   	 	{
		   	 			for (int k = 0; k < g.numNodes(); k++)
				{
					if (count == g.getNode(k).getId())
						y = k;
					}
		   		g.addEdge(x,y);
					}
			}
			if (j+1 < cols)	
		   	{
		   	if (map[i][j+1] != -1 )
		   	 	{
		   	 			for (int k = 0; k < g.numNodes(); k++)
				{
					if (count == g.getNode(k).getId())
						y = k;
					}
		   		g.addEdge(x,y);
					}
			}
			if (j-1>-1)	
		   		{
		   	if (map[i][j-1] != -1 )
		   	 		{
		   	 			for (int k = 0; k < g.numNodes(); k++)
						{
						if (count == g.getNode(k).getId())
						y = k;
						}
		   		g.addEdge(x,y);
					}
				}
					
		
		
			}
			count++;	
		}

	
	}

}

void maze::nonrecursivefind(graph &g, int &n)// BFS non recursive
{
	// initialization
	g.clearVisit();
	queue <int> pred;
	vector <int> parents;
	vector <int> visits;
	pred.push(0);
	g.visit(0);
	visits.push_back(0);
	parents.resize(g.numNodes());
	// building the path
	
	while(pred.empty()==false)
	{
	
		for (int i = 0; i < g.numNodes(); i++)
		{
			
			if (g.isEdge(pred.front(), i)|| g.isEdge(i,pred.front()))
			{
				if (g.isVisited(i)==false)
				{
					g.visit(i);// Mark as visited
					pred.push(i);// push into queue
					visits.push_back(i); // keep track of visits
					parents[i]=pred.front(); // BFS Tree
					
				}
				
				
			}
		}
		pred.pop();// popping out previous visisted node
	}
		
	// getting the path
	int n1,n2,n3,n4; // neighbours
	int curr;
	vector <int> check;
	 // check if it has a path
	for (int i = 0; i <visits.size(); i++)
	{
		if (visits[i]==g.numNodes()-1)
		{
			path==true;
			curr=i;
			
		}
		}
	if (path==true)
		{
			do{
				
			check.push_back(curr);
			curr = parents[curr];
			
			} while (curr != 0);
		check.push_back(0);
			
	for (int i = check.size()-1; i>0; i-- )
			{
		
			n1 = g.getNode(check[i]).getId() % cols;
			
			n2 = (g.getNode(check[i]).getId() -n1) / cols;
			
			n3 = g.getNode(check[i - 1]).getId() % Cols();
			
			n4 = (g.getNode(check[i - 1]).getId() - n3) / cols;
			
			if (n1!=n3)
			{
				if (n1<n3)
				{
					//Moving right
					cout << " Go Right" << endl;
					direction.push_back(1);
				}
				else 
				{
					//Moving left
					cout << "Go Left" << endl;
					direction.push_back(2);
					
				}
			}
			else if(n2!=n4)
			
			{
				if (n2<n4)
				{
					//moving down
					
					cout << "Go Down"<<endl;
					direction.push_back(3);
				}
				else 
				{
					//moving up
					cout << "Go Up"<< endl;
					direction.push_back(4);
					
				}
			}
		}
	} 
}
	
		


void maze::recursivefind(graph &g, int &n, int &i) // DFS recursive
{
	
	int n1,n2,n3,n4; // neighbours

	n1 = g.getNode(i).getId() % cols;
	n2 = (g.getNode(i).getId() -n1) / cols;
	n3 = g.getNode(n).getId() % cols;
	n4 = (g.getNode(n).getId() - n3) / cols;
		if (n1!=n3&& path==false)
			{
				if (n1<n3)
				{
					//Moving right
					cout << " Go Right" << endl;
					direction.push_back(1);
				}
				else 
				{
					//Moving left
					cout << "Go Left" << endl;
					direction.push_back(2);
					
				}
			}
			else if(n2!=n4&&path==false)
			
			{
				if (n2<n4)
				{
					//moving down
					
					cout << "Go Down"<<endl;
					direction.push_back(3);
				}
				else 
				{
					//moving up
					cout << "Go Up"<< endl;
					direction.push_back(4);
					
			}
	
		}
			if(n==g.numNodes()-1)
			{
				path==true;
			}
			else 
			{
				for (int j = 0; j < g.numNodes(); j++)// scan all the nodes 
			{
				if (g.isEdge(n, j) || g.isEdge(j, n)) 
				{
					visited.push_back(j);
					g.visit(j);
					recursivefind(g,n,j);
					n1 = g.getNode(j).getId() % cols;
					n2 = (g.getNode(j).getId() -n1) / cols;
					n3 = g.getNode(j).getId() % cols;
					n4 = (g.getNode(j).getId() - n3) / cols;
					if (n1!=n3&& path==false)
			{
				if (n1<n3)
				{
					//Moving right
					cout << " Go Right" << endl;
					direction.push_back(1);
				}
				else 
				{
					//Moving left
					cout << "Go Left" << endl;
					direction.push_back(2);
					
				}
			}
			else if(n2!=n4&&path==false)
			
			{
				if (n2<n4)
				{
					//moving down
					
					cout << "Go Down"<<endl;
					direction.push_back(3);
				}
				else 
				{
					//moving up
					cout << "Go Up"<< endl;
					direction.push_back(4);
					
					}		
	
				}
			}			
		}
	}
} 


#endif
