// Project 5
#ifndef maze_h
#define maze_h

#include <iostream>
#include <limits>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"
#include <queue>
#include <vector>

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
	int count = 0; // count to see how many nodes have been visited
	for (int i = 0; i <= rows-1; i++) //nested for loop to go through maze and create nodes
   {
      for (int j = 0; j <= cols-1; j++)
      {
			
			if (value[i][j]==true) //if the value is a 'O'
			{
				n.setId(count); //set an id to that coordinate
				g.addNode(n); //create the node
				setMap( i, j, count); //sends the count number
				
			}
			else 
			{
				setMap(i, j, -1); //node is not value so we send -1 instead of count
				
			}
			count++;
		}
			
	}
		count = 0;
	
for (int i = 0; i <= rows-1; i++) //nested for loop that is responsible to connecting nodes with edges
   {
      for (int j = 0; j <= cols-1; j++)
      {
		  if (value[i][j]==true) //again makes sure it only checks nodes in value matrix
		   {
		   	
		   	for (int k = 0; k < g.numNodes(); k++) //does this for ever node value
				{
					if (value[i][j] == g.getNode(k).getId()) //if count equals the node number, x equals iterations 
						x = k; 
				}
		   	
		   	
		   	 if (i+1 < rows) //if the iterations are in the matrix, checking to the right
		   	{
		   	if (map[i+1][j] != -1 ) //checks if point is valid
		   	 	{
		   	 			for (int k = 0; k < g.numNodes(); k++) //goes through every node
				{
					if (value[i+1][j] == g.getNode(k).getId()) //if the count is equal to the node id
						y = k;
					}
		   		g.addEdge(x,y); //we add an edge from source to destination
					}
			}
			
			if (i-1 > -1) //if the iterations are in the matrix, checking to the left
		   	{
		   	if (map[i-1][j] != -1 ) //checks if point is valid
		   	 	{
		   	 			for (int k = 0; k < g.numNodes(); k++) //goes through every node
				{
					if (value[i-1][j] == g.getNode(k).getId()) //if the count is equal to the node ID
						y = k;
					}
		   		g.addEdge(x,y); //we add an edge from source to destination
					}
			}
			if (j+1 < cols)	//if the iterations are in the matrix, checking below
		   	{
		   	if (map[i][j+1] != -1 ) //checks if point is valid
		   	 	{
		   	 			for (int k = 0; k < g.numNodes(); k++) //goes through every node
				{
					if (value[i][j+1] == g.getNode(k).getId()) //if the count is equal to the node ID
						y = k;
					}
		   		g.addEdge(x,y); //we add an edge from source to destination
					}
			}
			if (j-1>-1)	//if the iterations are in the matrix, checking above
		   		{
		   	if (map[i][j-1] != -1 ) //checks if point is valid
		   	 		{
		   	 			for (int k = 0; k < g.numNodes(); k++) //goes through every node
						{
						if (value[i][j-1] == g.getNode(k).getId()) //if the count is equal to the node ID
						y = k;
						}
		   		g.addEdge(x,y); //we add an edge from source to destination
					}
				}
					
		
		
			}
			count++; //count is iterated through every time
		}

	
	}
g.printNodes();
}

void maze::nonrecursivefind(graph &g, int &n)// BFS non recursive
{
	
	cout << "int" << endl;
	// initialization
	g.clearVisit(); //clear all
	queue <int> pred; //queue that makes BFS possible
	vector <int> parents; //holds the parents
	vector <int> visits; //remebered the visits
	pred.push(0); //start by pushing 0 into queue and vectors
	g.visit(0);
	visits.push_back(0);
	parents.resize(g.numNodes());
	// building the path
	
	cout << "before while loop" << endl;
	while(pred.empty()==false) //while the queue is not empty
	{
	
		for (int i = 0; i < g.numNodes(); i++) //we go do as many iterations as there are nodes
		{
			
			if (g.isEdge(pred.front(), i)|| g.isEdge(i,pred.front())) //check to see if there is an edge between the front of the stack and IT IS CHECKING 0
			{
			//	cout << "before final if" << endl;
			//	cout << g.isVisited(i) << endl;
				if (g.isVisited(i)==false) //make sure it has not been visited
				{
				//	cout << "in if" << endl;
					g.visit(i);// Mark as visited
					pred.push(i);// push into queue
					visits.push_back(i); // keep track of visits
					parents[i]=pred.front(); // BFS Tree
					
				}
				
				else
					continue;
				
				
			}
		}
		pred.pop();// popping out previous visisted node
	}
		
	// getting the path
	int n1,n2,n3,n4; //neighbours
	int curr;
	vector <int> check;
	 // check if it has a path
	for (int i = 0; i <visits.size(); i++) //number of iterations is equal to number of visited nodes
	{
		if (visits[i]==g.numNodes()-1) //for all nodes
		{
			path==true; //path is true
			curr=i; 
			
		}
		}
	if (path==true) 
		{
			do{ //run
				
			check.push_back(curr); //push the current int into check 
			curr = parents[curr]; //current = parent of it ~ float down
			
			} while (curr != 0); //while its not 0
			
		check.push_back(0); //push 0 into check
			
	for (int i = check.size()-1; i>0; i-- ) //starting at the end, it goes through check
			{
		
			n1 = g.getNode(check[i]).getId() % cols; //neighbors 1,2,3 and 4 finding the neighbors for R, L, U & D
			
			n2 = (g.getNode(check[i]).getId() - n1) / cols; 
			
			n3 = g.getNode(check[i - 1]).getId() % Cols(); 
			
			n4 = (g.getNode(check[i - 1]).getId() - n3) / cols;  
			
			if (n1!=n3) // checks right and lefts
			{
				if (n1<n3) //to the right
				{
					//Moving right
					cout << " Go Right" << endl;
					direction.push_back(1); //saves direction
				}
				else //to the left
				{
					//Moving left
					cout << "Go Left" << endl;
					direction.push_back(2); //saves direction
					
				}
			}
			else if(n2!=n4) //checks up and downs
			
			{
				if (n2<n4) //below
				{
					//moving down
					
					cout << "Go Down"<<endl;
					direction.push_back(3); //saves direction
				}
				else //above
				{
					//moving up
					cout << "Go Up"<< endl;
					direction.push_back(4); //saves direction
					
				}
			}
		} 
	} 
}
	
		


void maze::recursivefind(graph &g, int &n, int &i) // DFS recursive
{
	
	int n1,n2,n3,n4; // neighbours

	n1 = g.getNode(i).getId() % cols; //assigns all the neighbors
	n2 = (g.getNode(i).getId() -n1) / cols;
	n3 = g.getNode(n).getId() % cols;
	n4 = (g.getNode(n).getId() - n3) / cols;
	
		if (n1!=n3&& path==false) //checks right and left neighbors
			{
				if (n1<n3) //to the right
				{
					//Moving right
					cout << " Go Right" << endl;
					direction.push_back(1);
				}
				else  //to the left
				{
					//Moving left
					cout << "Go Left" << endl;
					direction.push_back(2);
					
				}
			}
			else if(n2!=n4&&path==false) //checks up and down
			
			{
				if (n2<n4) //below
				{
					//moving down
					
					cout << "Go Down"<<endl;
					direction.push_back(3);
				}
				else  //above
				{
					//moving up
					cout << "Go Up"<< endl;
					direction.push_back(4);
					
			}
	
		}
			if(n==g.numNodes()-1) //the correct number of nodes
			{
				path==true;
			}
			else 
			{
				for (int j = 0; j < g.numNodes(); j++)// scan all the nodes 
			{
				if (g.isEdge(n, j) || g.isEdge(j, n))  //if there is an edge in either direction
				{
					visited.push_back(j); //psuh j into visited
					g.visit(j); //mark it as visited
					recursivefind(g,n,j); //recursive call
					n1 = g.getNode(j).getId() % cols; //re-assign neighbors
					n2 = (g.getNode(j).getId() -n1) / cols;
					n3 = g.getNode(j).getId() % cols;
					n4 = (g.getNode(j).getId() - n3) / cols;
					if (n1!=n3&& path==false) //checking right and left again
			{
				if (n1<n3) //to the right
				{
					//Moving right
					cout << " Go Right" << endl;
					direction.push_back(1); //saves the direction
				}
				else  //to the left
				{
					//Moving left
					cout << "Go Left" << endl;
					direction.push_back(2); //saves the direction
					
				}
			}
			else if(n2!=n4&&path==false) //checks above and below
			
			{
				if (n2<n4) //checks below
				{
					//moving down
					
					cout << "Go Down"<<endl;
					direction.push_back(3); //saves the direction
				}
				else //checks above
				{
					//moving up
					cout << "Go Up"<< endl;
					direction.push_back(4); //saves the direction
					
					}		
	
				}
			}			
		}
	}
} 

#endif
