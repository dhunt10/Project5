// Project 5

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
    void findPathNonRecursive(graph &g);
    
private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze
    
    matrix<bool> value;
    matrix<int> map;      // Mapping from maze (i,j) values to node index values
};

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
    int count =0;
    
    for (int i = 0; i< rows; i++)
    {
        
        for (int j = 0; j<cols; j++)
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
    
    for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<cols; j++)
        {
            
            if (map[i][j]!=-1)
            {
                
                
                for (int k = 0; k < g.numNodes(); k++)
                {
                    if (count == g.getNode(k).getId())
                        x = k;
                }
                
                
                if (i!=rows-1 && map[i+1][j] != -1)
                {
                    for (int k = 0; k < g.numNodes(); k++)
                    {
                        if (count == g.getNode(k).getId())
                            y = k;
                        
                    }
                    g.addEdge(x,y);
                }
                if (i!=0&&map[i-1][j] != -1 )
                {
                    for (int k = 0; k < g.numNodes(); k++)
                    {
                        
                        if (count == g.getNode(k).getId())
                            y = k;
                    }
                    
                }
                
                if (j<=cols-1 && map[i][j+1] != -1)
                {
                    for (int k = 0; k < g.numNodes(); k++)
                    {
                        if (count == g.getNode(k).getId())
                            y = k;
                    }
                    
                    
                }
                if (j!=0 && map[i][j-1] != -1)
                {
                    
                    for (int k = 0; k < g.numNodes(); k++)
                    {
                        if (count == g.getNode(k).getId())
                            y = k;
                    }
                    
                }
                
            }
            
            
            count++;
        }
        
    }
    
    
    
    
}

void maze::findPathNonRecursive(graph &g)
{
    queue <int> holding;
    g.clearVisit();
    holding.push(0);
    g.visit(0);
    
    
    while(!holding.empty())
    {
        
        for (int i =0; i < g.numNodes(); i++)
        {
            
            if (g.isEdge(holding.front(),i) || g.isEdge(i, holding.front()))
            {
                
                if (g.isVisited(i)==false)
                {
                    
                    g.visit(i);
                    holding.push(i);
                    cout << "Node visited : " << g.getNode(i).getId() << endl;
                    if (i==g.numNodes())
                    {
                        cout << "There exists a path from the start to finish" << endl;
                        break;
                    }
                }
                
                else
                    continue;
            }
            else
                continue;
        }
        holding.pop();
    }
    
}



int main()
{
    char x;
    ifstream fin;
    
    // Read the maze from the file.
    string fileName = "maze1.txt";
    
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    
    try
    {
        
        graph g;
        while (fin && fin.peek() != 'Z')
        {
            maze m(fin);
            m.mapMazeToGraph(g);
            m.findPathNonRecursive(g);
        }
        
        
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
    catch (rangeError &ex)
    {
        cout << ex.what() << endl; exit(1);
    }
}
