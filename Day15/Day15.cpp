#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <limits.h>

using namespace std;

#define ROW 500
#define COL 500

bool inGrid(int i, int j){
    return (i >= 0 && i < ROW && j >= 0 && j < COL);
}

int shortest(int grid[ROW][COL], int row, int col){
    int dis[row][col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            dis[i][j] = INT_MAX;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    set<pair<int, pair<int, int>>> st;
    pair<int, pair<int, int>> hp;
    hp.first = 0;
    hp.second.first = 0;
    hp.second.second = 0;
    st.insert(hp);
    dis[0][0] = grid[0][0];

    while (!st.empty()){
        pair<int, pair<int, int>> k = *st.begin();
        st.erase(st.begin());
        for (int i = 0; i < 4; i++){
            int x = k.second.first + dx[i];
            int y = k.second.second + dy[i];
            if (!inGrid(x, y))
                continue;
            if (dis[x][y] > dis[k.second.first][k.second.second] + grid[x][y]){
                if (dis[x][y] != INT_MAX){
                    pair<int, pair<int, int>> hp;
                    hp.second.first = x;
                    hp.second.second = y;
                    hp.first = dis[x][y];
                    st.erase(st.find(hp));
                }
                dis[x][y] = dis[k.second.first][k.second.second] + grid[x][y];
                pair<int, pair<int, int>> hp;
                hp.second.first = x;
                hp.second.second = y;
                hp.first = dis[x][y];
                st.insert(hp);
            }
        }
    }
    return dis[row - 1][col - 1];
}

void addGrid(int grid[ROW][COL], int x, int y, int xM, int yM){
    for(int i = x; i < x + 100; ++i)
        for(int j = y; j < y + 100; ++j)
            if(grid[i-xM][j-yM] == 9)
                grid[i][j] = 1;
            else
                grid[i][j] = grid[i-xM][j-yM] + 1;
}

int main()
{
    int grid[ROW][COL];
    ifstream fin("Day15.txt");
    char ch;
    for(int i = 0; i < 100; ++i)
        for(int j = 0; j < 100; ++j)
            fin >> ch, grid[i][j] = ch - '0';
    addGrid(grid, 0, 100, 0, 100);
    addGrid(grid, 0, 200, 0, 100);
    addGrid(grid, 0, 300, 0, 100);
    addGrid(grid, 0, 400, 0, 100);

    addGrid(grid, 100, 0, 100, 0);
    addGrid(grid, 200, 0, 100, 0);
    addGrid(grid, 300, 0, 100, 0);
    addGrid(grid, 400, 0, 100, 0);

    addGrid(grid, 100, 100, 100, 0);
    addGrid(grid, 100, 200, 100, 0);
    addGrid(grid, 100, 300, 100, 0);
    addGrid(grid, 100, 400, 100, 0);

    addGrid(grid, 200, 100, 100, 0);
    addGrid(grid, 200, 200, 100, 0);
    addGrid(grid, 200, 300, 100, 0);
    addGrid(grid, 200, 400, 100, 0);

    addGrid(grid, 300, 100, 100, 0);
    addGrid(grid, 300, 200, 100, 0);
    addGrid(grid, 300, 300, 100, 0);
    addGrid(grid, 300, 400, 100, 0);

    addGrid(grid, 400, 100, 100, 0);
    addGrid(grid, 400, 200, 100, 0);
    addGrid(grid, 400, 300, 100, 0);
    addGrid(grid, 400, 400, 100, 0);

    cout << shortest(grid, ROW, COL) - grid[0][0] << endl;
    return 0;
}
