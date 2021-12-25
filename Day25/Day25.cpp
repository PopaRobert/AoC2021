#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <deque>
#include <map>

using namespace std;
string line;
int values[150][150];
int c_values[150][150], cp_values[150][150];
int n, m;

bool check_east(int p[150][150], int x, int y){
    if(y == m-1){
        if(p[x][0] == 0)
            return true;
        return false;
    }
    if(p[x][y+1] == 0)
        return true;
    return false;
}

bool check_south(int p[150][150], int x, int y){
    if(x == n-1){
        if(p[0][y] == 0)
            return true;
        return false;
    }
    if(p[x+1][y] == 0)
        return true;  
    return false;
}

int main(){
    ifstream fin("Day25.txt");
    while(fin >> line){
        for(int i = 0; i < line.size(); ++i)
            if(line[i] == '>')
                values[n][i] = 1;
            else if(line[i] == 'v')
                values[n][i] = 2;
        ++n;
        m = line.size();
    }
    int ok = 1, ans = 0;
    while(ok){
        ok = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                c_values[i][j] = values[i][j];
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j){
                if(values[i][j] == 1)
                    if(check_east(values, i, j)){
                        c_values[i][j] = 0;
                        ok = 1;
                        if(j == m-1){
                            c_values[i][0] = 1;
                        }
                        else
                            c_values[i][j+1] = 1;
                    }
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                cp_values[i][j] = c_values[i][j];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j){
                if(c_values[i][j] == 2)
                    if(check_south(c_values, i, j)){
                        cp_values[i][j] = 0;
                        ok = 1;
                        if(i == n-1)
                            cp_values[0][j] = 2;
                        else
                            cp_values[i+1][j] = 2;
                    }
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                values[i][j] = cp_values[i][j];
        ++ans;
    }
    cout << ans << '\n';
    return 0;
}
