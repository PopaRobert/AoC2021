#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

int octopus[12][12];
int lights = 0, k;
bool inmat(int x, int y){
    if(x < 0 || y < 0)
        return false;
    if(x >= 10 || y >= 10)
        return false;
    return true;
}
void increase(int x, int y){
    octopus[x][y] = 11;
    lights++;
    if(inmat(x-1, y-1) && octopus[x-1][y-1] <= 9){
        octopus[x-1][y-1]++;
        if(octopus[x-1][y-1] == 10){
            octopus[x-1][y-1] = 11;
            increase(x-1, y-1);
        }
    }
    if(inmat(x-1, y) && octopus[x-1][y] <= 9){
        octopus[x-1][y]++;
        if(octopus[x-1][y] == 10){
            octopus[x-1][y] = 11;
            increase(x-1, y);
        }
    }
    if(inmat(x-1, y+1) && octopus[x-1][y+1] <= 9){
        octopus[x-1][y+1]++;
        if(octopus[x-1][y+1] == 10){
            octopus[x-1][y+1] = 11;
            increase(x-1, y+1);
        }
    }
    if(inmat(x, y-1) && octopus[x][y-1] <= 9){
        octopus[x][y-1]++;
        if(octopus[x][y-1] == 10){
            octopus[x][y-1] = 11;
            increase(x, y-1);
        }
    }
    if(inmat(x, y+1) && octopus[x][y+1] <= 9){
        octopus[x][y+1]++;
        if(octopus[x][y+1] == 10){
            octopus[x][y+1] = 11;
            increase(x, y+1);
        }
    }
    if(inmat(x+1, y-1) && octopus[x+1][y-1] <= 9){
        octopus[x+1][y-1]++;
        if(octopus[x+1][y-1] == 10){
            octopus[x+1][y-1] = 11;
            increase(x+1, y-1);
        }
    }
    if(inmat(x+1, y) && octopus[x+1][y] <= 9){
        octopus[x+1][y]++;
        if(octopus[x+1][y] == 10){
            octopus[x+1][y] = 11;
            increase(x+1, y);
        }
    }
    if(inmat(x+1, y+1) && octopus[x+1][y+1] <= 9){
        octopus[x+1][y+1]++;
        if(octopus[x+1][y+1] == 10){
            octopus[x+1][y+1] = 11;
            increase(x+1, y+1);
        }
    }
}

void printMat(){
    for(int i = 0; i < 10; ++i, cout << '\n')
        for(int j = 0; j < 10; ++j)
            cout << octopus[i][j] << ' ';
    cout << '\n';
}

int main(){
    char ch;
    int nr;
    ifstream fin("Day11.txt");
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j){
            fin >> ch;
            nr = ch - '0';
            octopus[i][j] = nr;
        }
    for(k = 0; k < 500; ++k){
        for(int i = 0; i < 10; ++i){
            for(int j = 0; j < 10; ++j)
                if(octopus[i][j] == 9){
                    octopus[i][j] = 11;
                    increase(i, j);
                }
                else{
                    if(octopus[i][j] < 9)
                        ++octopus[i][j];
                }
        }
        int cnt = 0;
        for(int i = 0; i < 10; ++i)
            for(int j = 0; j < 10; ++j)
                if(octopus[i][j] == 11){
                    octopus[i][j] = 0;
                    ++cnt;
                }
        if(k == 100)
            cout << lights << '\n';
        if(cnt == 100){
            cout << k << '\n';
            return 0;
        }
        //printMat();
    }

    return 0;
}
