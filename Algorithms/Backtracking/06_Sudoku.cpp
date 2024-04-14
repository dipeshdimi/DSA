#include<iostream>
#include<math.h>
#define N 4

using namespace std;

void printBoard(int board[][N])
{
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++)
            cout<<board[i][j]<<" ";
        cout<<"\n";
    }
}
bool isSafe(int board[][N], int n, int i, int j)
{
    // Row & column check
    for(int k=0; k<N; k++)
        if(board[i][k]==n || board[k][j]==n)
            return false;
    
    // Grid check
    int gridSize = sqrt(N);
    int rs = i - i%gridSize;    // row start
    int cs = j - j%gridSize;    // column start
    for(int gridRow=0; gridRow<gridSize; gridRow++)
        for(int gridCol=0; gridCol<gridSize; gridCol++)
            if(board[rs + gridRow][cs + gridCol] == n)
                return false;
    
    // Both checks passed => Safe
    return true;
}

bool sudokuRec(int board[][N])
{
    // Check if there is still still an empty slot
    int i=0, j;
    bool flag = false;
    for(; i<N; i++) {
        for(j=0; j<N; j++) {
            if(board[i][j]==0) {
                flag = true;
                break;
            }
        }
        if(flag)
            break;
    }
    
    // Return if already filled
    if(i==N && j==N)
        return true;
    
    // Check for each number from 1 to N to find the suitable number for the current empty slot
    for(int n=1; n<=N; n++) {
        // If a safe number (follows all the rules)
        if(isSafe(board, n, i, j))
        {
            // Fill the empty slot
            board[i][j] = n;

            // Continue further down the solution tree
            if(sudokuRec(board))
                return true;
            
            // If solution not found on this path on solution tree, empty the filled slot
            board[i][j] = 0;
        }
    }
    // No suitable number for the empty slot => No possible configuration
    return false;
}

void sudoku(int board[][N])
{
    if(sudokuRec(board))
        printBoard(board);
    else
        cout<<"No solution exists";
}

int main()
{
    /*
        # SUDOKU RULES
            1) No duplicate in any row.
            2) No duplicate in any column.
            3) No duplicate in any (discrete) sqrt(N)xsqrt(N) grid.
    */
    // Sudoku boards can be of 4x4, 9x9, 16x16, ... dimensions
    int board[N][N] = { {1,0,3,0},
                        {0,0,2,1},
                        {0,1,0,2},
                        {2,4,0,0} };
    sudoku(board);

    return 0;
}