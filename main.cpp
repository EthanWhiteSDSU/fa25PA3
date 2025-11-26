//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();

    cout << "\nMaze:\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

bool dfs(int ent_r, int ent_c, const vector<vector<int>>& maze, vector<vector<bool>>& visited, vector<vector<int>>& parent_r, vector<vector<int>>& parent_c, int exit_r, int exit_c)
{
    // base case, if current cell is the exit, stop and return true
    if(ent_r == exit_r && ent_c == exit_c)
    {
        return true;
    }

    // mark current cell as visited
    visited[ent_r][ent_c] = true;

    // establish cardinal directions from current cell
    pair<int, int> up(ent_r + dr[0], ent_c + dc[0]);
    pair<int, int> right(ent_r + dr[1], ent_c + dc[1]);
    pair<int, int> down(ent_r + dr[2], ent_c + dc[2]);
    pair<int, int> left(ent_r + dr[3], ent_c + dc[3]);

    // if up cell can be visited
    if(up.first > -1 && maze[up.first][up.second] != 1 && !visited[up.first][up.second])
    {
        // save current cell as parent of up cell
        parent_r[up.first][up.second] = ent_r;
        parent_c[up.first][up.second] = ent_c;

        // move to up cell, if allows for other directions to be tried
        if(dfs(up.first, up.second, maze, visited, parent_r, parent_c, exit_r, exit_c))
        {
            return true;
        }
    }

    // if right cell can be visited
    if(right.second < maze[0].size() && maze[right.first][right.second] != 1 && !visited[right.first][right.second])
    {
        // save current cell as parent of right cell
        parent_r[right.first][right.second] = ent_r;
        parent_c[right.first][right.second] = ent_c;

        // move to right cell, if allows for other directions to be tried
        if(dfs(right.first, right.second, maze, visited, parent_r, parent_c, exit_r, exit_c))
        {
            return true;
        }
    }

    // if down cell can be visited
    if(down.first < maze.size() && maze[down.first][down.second] != 1 && !visited[down.first][down.second])
    {
        // save current cell as parent of down cell
        parent_r[down.first][down.second] = ent_r;
        parent_c[down.first][down.second] = ent_c;

        // move to down cell, if allows for other directions to be tried
        if(dfs(down.first, down.second, maze, visited, parent_r, parent_c, exit_r, exit_c))
        {
            return true;
        }
    }

    // if left cell can be visited
    if(left.second > -1 && maze[left.first][left.second] != 1 && !visited[left.first][left.second])
    {
        // save current cell as parent of left cell
        parent_r[left.first][left.second] = ent_r;
        parent_c[left.first][left.second] = ent_c;

        // move to left cell, if allows for other directions to be tried
        if(dfs(left.first, left.second, maze, visited, parent_r, parent_c, exit_r, exit_c))
        {
            return true;
        }
    }

    // if no more cells can be visited and the exit wasn't found, stop and return false
    return false;
}

// ----------------------------------------------------------
// MAIN PROGRAM (students add DFS calls and logic)
// ----------------------------------------------------------
int main() {
    int N, M;

    cout << "Enter maze dimensions N M: ";
    cin >> N >> M;

    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(maze, N, M);

    // Pick entrance and exit
    pair<int,int> entrance = chooseBoundaryCell(maze);
    pair<int,int> exitcell = chooseBoundaryCell(maze);

    while (exitcell == entrance) {
        exitcell = chooseBoundaryCell(maze);
    }

    int ent_r = entrance.first;
    int ent_c = entrance.second;
    int exit_r = exitcell.first;
    int exit_c = exitcell.second;

    // Display the maze
    printMaze(maze, ent_r, ent_c, exit_r, exit_c);

    // Students must use these
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> parent_r(N, vector<int>(M, -1));
    vector<vector<int>> parent_c(N, vector<int>(M, -1));

    bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);
    if(found) 
    {
        printPath(exitcell, parent_r, parent_c, ent_r, ent_c);
    } 
    else 
    {
        cout << "\nNo path exists.\n";
    }
    
    return 0;
}