#include<bits/stdc++.h>
using namespace std;

void subsetsString(char *input, char *output, int i,int j) {
    if(input[i] == '\0') {
        output[j] = '\0';
        cout<<output<<"\n";
        return;
    }

    output[j] = input[i];
    subsetsString(input,output,i+1,j+1);
    subsetsString(input,output,i+1,j);
}

void permutationString(string input,int i,int j) {
    if(i == j) {
        cout<<input<<"\n";
        return;
    }

    for(int k = i; k<=j-1; k++) {
        swap(input[i],input[k]);
        permutationString(input,i+1,j);
        swap(input[i],input[k]);
    }
}


// N-QUEEN PROBLEM

bool canPlace(int board[][20],int n,int i,int j) {
    int r = i;
    while(r>=0) {
        if(board[r][j]) return false;
        r--;
    }

    r = i; 
    int c = j;
    while(r >= 0 and c<=n-1) {
        if(board[r][c]) return false;
        r--;
        c++;
    }

    r = i;
    c = j;
    while(r>=0 and c>=0) {
        if(board[r][c]) return false;
        r--;
        c--;
    }

    return true;
}


bool NQueen(int board[][20],int n,int i) {
    if(i == n) return true;

    for(int j=0; j<n; j++) {
        if(canPlace(board,n,i,j)) {
            board[i][j] = 1;
            bool success = NQueen(board,n,i+1);
            if(success) return true;

            board[i][j] = 0;
        }
    }

    return false;
}

int NQueenWays(int board[][20],int n, int i) {
    if(i == n) return 1;  // write print function here to see the configuration

    int ways = 0;
    for(int j=0; j<n; j++) {
        if(canPlace(board,n,i,j)) {
            board[i][j] = 1;
            ways += NQueenWays(board,n,i+1);
        }

        board[i][j] = 0;
    }

    return ways;
}

void dfs(vector<vector<int>> board, int i,int j,int m,int n,int &flag,vector<vector<int>> &visited,vector<vector<char>> &ans) {
    
    if(flag) return;
    if(i == m-1 and j == n-1 and board[i][j] == 1) {
        flag = 1;
        return;
    }

    if(i>=m || j>=n || i<0 || j<0 || board[i][j] == 0 || visited[i][j] == 1) return;

    visited[i][j] = 1;
    dfs(board,i,j+1,m,n,flag,visited,ans);
    dfs(board,i+1,j,m,n,flag,visited,ans);
    dfs(board,i,j-1,m,n,flag,visited,ans);
    dfs(board,i-1,j,m,n,flag,visited,ans);
    ans[i][j] = 'X';
    
}


bool ratMaze(vector<vector<int>> board,int m, int n) {
    int flag = 0;
    vector<vector<int>> visited(m,vector<int>(n,0));
    vector<vector<char>> ans(m,vector<char>(n,'O'));
    dfs(board,0,0,m,n,flag,visited,ans);
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) cout<<ans[i][j]<<" ";
        cout<<"\n";
    }
    if(flag) return true;
    return false;
}

bool place(int sudoku[][9],int i,int j,int key) {
    
    for(int k = 0; k<9; k++) {
        if(sudoku[i][k] == key || sudoku[k][j] == key) return false;
    }

    int sx = (i/3)*3;
    int sy = (j/3)*3;

    for(int x=sx; x<sx+3; x++) {
        for(int y=sy; y<sy+3; y++) {
            if(sudoku[x][y] == key) return false;
        }
    }

    return true;
}

bool sudokuSolver(int sudoku[][9],int i,int j) {
    if(i == 9) {
        for(int r=0; r<9; r++) {
            for(int c=0; c<9; c++) {
                cout<<sudoku[r][c]<<" ";
            }

            cout<<"\n";
        }
        return true;
    }

    if(j == 9) {
        return sudokuSolver(sudoku,i+1,0);
    }

    if(sudoku[i][j] != 0) {
        return sudokuSolver(sudoku,i,j+1);
    }

    for(int no = 1; no<=9; no++) {
        if(place(sudoku,i,j,no)){
            sudoku[i][j] = no;
            bool success = sudokuSolver(sudoku,i,j+1);
            if(success) return true;   
        }
    }

    sudoku[i][j] = 0;
    return false;
}

int main() {
    int n;
    cin>>n;
    vector<vector<int>> v(n,vector<int>(n));
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) cin>>v[i][j];
    }

    ratMaze(v,n,n);
    
    return 0;
}