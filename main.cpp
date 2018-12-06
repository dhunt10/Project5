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
   string fileName = "maze1.txt";

   fin.open(fileName.c_str()); //OPEN 
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {

      graph g; //new graph
      int rows,cols; //columns and rows for graph
      int n = 0;
      cols = n;
      rows =n;
      while (fin && fin.peek() != 'Z') 
      {	
         
         maze m(fin); //maze
         m.mapMazeToGraph(g); //map it
         cout << "BFS Non Recursive " << endl; 
         m.nonrecursivefind(g,n); //calling non recursive version
         if (m.path== true) //if the path exists
         {
		 cout << " There is a path of this Maze";
         for ( int i =0;i<m.direction.size(); i++) 
		 //goes through direction vector
         {
         	switch(m.direction[i]) 
         	 {
         	 	case 1:
         	 		cols++; 
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols); //output
					break;
				case 2:
         	 		cols--;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);  //output
					break;
         	 	case 3:
         	 		rows++;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);  //output
					break;
				case 4:
         	 		rows--;
         	 		m.print(m.Rows() - 1, m.Cols() - 1, rows, cols);  //output
					break;
         	 	
			}
         	
         	
		 }
         cout << "Maze path found "<< endl;
     	}
     	else 
     	{	 
     	cout <<"no Path Exists"<<endl;
     	}
        
		
		 m.reset(g); //resets the path
         cout << " DFS Non Recursive" << endl;
         m.recursivefind(g,n,n); //runs the recursive function
      	if (m.path== true)
         {
         for ( int i =0;i<m.direction.size(); i++) 
		 //outputs the directions 
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
			     cout << "Maze path found "<< endl;	//worked 	 
		 }
     	else 
     	{	 
     	cout <<"no Path Exists"<<endl; //did not work
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

