#include<iostream>
#define N 4
using namespace std;

int solMat[N][N];

void printSol()
{
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++)
            cout<<solMat[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

bool isSafe(int row, int col)
{
    // Check for other queens in the same row. We do not need to check for another in the same column since we're placing only one queen in a column by default (we call nQueensRec(col+1) after placing a queen in column col).
    for(int i=0; i<col; i++)
        if(solMat[row][i])
            return false;
    
    // Upper diagonal check
    for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--)
        if(solMat[i][j])
            return false;
    
    // Lower diagonal check
    for(int i=row+1, j=col-1; i<N && j>=0; i++, j--)
        if(solMat[i][j])
            return false;
    
    // All checks passed
    return true;
}

bool nQueensRec(int col)
{
    // Implies we've already placed all the queens
    if(col==N)
        return true;
        // /* For all possible solutions :-*/
        // printSol();
    
    // For column 'col', check for each row from 1st to Nth as a possible queen placement cell
    for(int row=0; row<N; row++) {
        // Check if another queen would be in an attacking position if we place a queen at (row,col)
        if(isSafe(row, col)) 
        {
            // Place the queen at (row,col)
            solMat[row][col] = 1;

            // /*For all possible solutions :- */
            // nQueensRec(col+1);

            if(nQueensRec(col+1))
                return true;
            
            // Backtrack: Remove the queen from (row,col) in case this configuration could not lead to a solution as we delved deeper into the solution tree
            solMat[row][col] = 0;
        }
    }
    // No feasible position to place the queen in any of the rows
    return false;
}

void nQueens()
{
    if(nQueensRec(0))
        printSol();
    else
        cout<<"No possible configuration\n";
}

int main()
{
    nQueens();
    return 0;
}