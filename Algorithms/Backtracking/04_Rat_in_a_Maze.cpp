#include<iostream>
using namespace std;

#define N 5

int maze[N][N]  =  {
   {1, 0, 0, 0, 0},
   {1, 1, 1, 1, 0},
   {0, 1, 0, 0, 0},
   {0, 1, 0, 1, 0},
   {1, 1, 1, 1, 1}
};

int sol[N][N];      // Auto zero-initialization

void printSol()
{
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++)
            cout<<sol[i][j]<<" ";
        cout<<"\n";
    }
}
bool ratInMazeRec(int x,int y)  // x -> row index, y -> col index
{
    if(x==N-1 && y==N-1)    // On reaching the endpoint
    {
        sol[x][y] = 1;
        return true;
    }
    if(x<N && y<N && maze[x][y]==1)     // Must be a valid path to follow
    {
        sol[x][y] = 1;
        if(ratInMazeRec(x+1,y))         // Next Row
            return true;
        else if(ratInMazeRec(x,y+1))    // Next Column
            return true;
        
        sol[x][y] = 0;  // Blocking the solution path we came through now that we know it's wrong
    }
    return false;   // In case (x+1,y) & (x,y+1) are both infeasible
}

void ratInMaze()
{
    if(!ratInMazeRec(0,0))
        cout<<"Infeasible";
    else {
        cout<<"Feasible\n";
        printSol();
    }
}

int main()
{
    // Only allows down & right movement. Can be extended to allow left & up movements too.
    ratInMaze();
    return 0;
}