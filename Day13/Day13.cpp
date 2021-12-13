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

int mat[10000][10000];
int nr1, nr2, ans[10000];
int x, y;

void foldY(int line){
    for(int i = 0; i <= y+1; ++i){
        mat[line][i] = -1;
    }
    for(int i = line+1; i <= x; ++i)
        for(int j = 0; j <= y; ++j)
            if(mat[i][j] == 1){
                mat[x - i][j] = 1;
            }
    x = line-1;
}

void foldX(int line){
    for(int i = 0; i <= x+1; ++i){
        mat[i][line] = -1;
    }
    for(int i = 0; i <= x; ++i)
        for(int j = line+1; j <= y; ++j)
            if(mat[i][j] == 1)
                mat[i][y - j] = 1;
    y = line-1;
}

int main(){
    ofstream fout("Day13OUT.txt");
    ifstream fin("Day13.txt");
    string s;
    char ch;
    while(fin >> s){
        nr1 = 0;
        nr2 = 0;
        if(s != "fold"){
            int k = 0;
            while(s[k] != ','){
                nr1 *= 10;
                nr1 += s[k] - '0';
                ++k;
            }
            ++k;
            while(s[k] != ',' && k < s.size()){
                nr2 *= 10;
                nr2 += s[k] - '0';
                ++k;
            }
            y = max(y, nr1);
            x = max(x, nr2);
            mat[nr2][nr1] = 1;
        }
        else{
            fin >> s;
            fin >> ch;
            if(ch == 'x'){
                fin >> ch >> nr1;
                foldX(nr1);
            }
            else{
                fin >> ch >> nr1;
                foldY(nr1);
            }
        }
    }
    for(int i = 0; i <= x; ++i, fout << '\n')
        for(int j = 0; j <= y; ++j){
            if(mat[i][j] == 1)
                fout << '#';
            else
                fout << '.';
            if(mat[i][j] == 1){
                ans[1]++;
            }
        }
    cout << ans[1] << '\n';
    fin.close();
    fin.open("Day13.txt");

    return 0;
}
