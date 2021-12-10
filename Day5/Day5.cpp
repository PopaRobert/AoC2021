#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int table[1000][1000];

int main(){
    ifstream fin("Day5.txt");
    int x1, y1, x2, y2;
    char ch;
    while(!fin.eof()){
        fin >> x1 >> ch >> y1;
        fin >> ch >> ch;
        fin >> x2 >> ch >> y2;
        if(x1 == x2 || y1 == y2){
            if(x1 > x2)
                swap(x1, x2);
            if(y1 > y2)
                swap(y1, y2);
            if(x1 != x2)
                for(int i = x1; i <= x2; ++i){
                    table[i][y1]++;
                }
            if(y1 != y2)
                for(int i = y1; i <= y2; ++i){
                    table[x1][i]++;
                }
        }
    }
    int cnt = 0;
    for(int i = 0; i < 1000; ++i)
        for(int j = 0; j < 1000; ++j)
            if(table[i][j] >= 2)
                ++cnt;
    cout << cnt << '\n';
    fin.close();
    fin.open("Day5.txt");
    memset(table, 0, sizeof(table));
    while(!fin.eof()){
        fin >> x1 >> ch >> y1;
        fin >> ch >> ch;
        fin >> x2 >> ch >> y2;
        if(x1 == x2 || y1 == y2){
            if(x1 != x2)
                for(int i = min(x1, x2); i <= max(x1, x2); ++i){
                    table[i][y1]++;
                }
            if(y1 != y2)
                for(int i = min(y1, y2); i <= max(y1, y2); ++i){
                    table[x1][i]++;
                }
        }
        else{
            ++table[x1][y1];
            while(x1 != x2 && y1 != y2){
                if(x1 > x2){
                    --x1;
                }
                else if(x1 < x2)
                    ++x1;
                if(y1 > y2)
                    --y1;
                else if(y1 < y2)
                    ++y1;
                ++table[x1][y1];
            }
        }
    }
    cnt = 0;
    for(int i = 0; i < 1000; ++i)
        for(int j = 0; j < 1000; ++j)
            if(table[i][j] >= 2)
                ++cnt;
    cout << cnt << '\n';
    return 0;
}