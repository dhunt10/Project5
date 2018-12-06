#include <iostream>
#include "maze.h"
#include "graph.h"
#include <fstream>
using namespace std;


int main()
{
   char x;
   ifstream fin;
   
   // Read the maze from the file.
   string fileName = "maze2.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {

      graph g;
      int rows,cols;
      int n = 0;
      cols = n;
      rows =n;
      while (fin && fin.peek() != 'Z')
      {	
         
         maze m(fin);
         m.mapMazeToGraph(g);
         cout << "BFS Non Recursive " << endl;
         m.nonrecursivefind(g,n);
         if (m.path== true)
         {
		 cout << " There is a path of this Maze";
         for ( int i =0;i<m.direction.size(); i++)
         {
         	switch(m.direction[i])
         	 {
         	 	case 1:
         	 		cols++;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
				case 2:
         	 		cols--;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
         	 	case 3:
         	 		rows++;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
				case 4:
         	 		rows--;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
         	 	
			}
         	
         	
		 }
         cout << "Maze path found "<< endl;
     	}
     	else 
     	{	 
     	cout <<"no Path Exists"<<endl;
     	}
         m.reset(g);
         cout << " DFS Non Recursive" << endl;
         m.recursivefind(g,n,n);
      	if (m.path== true)
         {
         for ( int i =0;i<m.direction.size(); i++)
         {
         	switch(m.direction[i])
         	 {
         	 	case 1:
         	 		cols++;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
				case 2:
         	 		cols--;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
         	 	case 3:
         	 		rows++;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
				case 4:
         	 		rows--;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);
					break;
				default:
					break;
         	 	
				}
         	
         	
			 }
			     cout << "Maze path found "<< endl;		 
		 }
     	else 
     	{	 
     	cout <<"no Path Exists"<<endl;
     	}
         
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
   fin.close();
}
