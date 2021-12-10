#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;
deque <int> values;
long long answears[15];

unsigned long long calcAfter(int days){
    int nr;
    if(answears[days] != 0)
        return answears[days];
    map <int, int> answear;
    unsigned long long toAdd[100];
    for(int i = 0; i <= 8; ++i)
        answear[i] = 0;
    answear[days]++;
    for(int i = 0; i < 256; ++i){
        toAdd[7] = answear[7]; toAdd[6] = answear[6];
        answear[7] = answear[8]; answear[8] = answear[0]; answear[6] = answear[0];
        answear[6] += toAdd[7];
        answear[0] = answear[1]; answear[1] = answear[2]; answear[2] = answear[3]; answear[3] = answear[4];
        answear[4] = answear[5]; answear[5] = toAdd[6];
    }
    unsigned long long ans = 0;
    for(int i = 0; i <= 8; ++i){
        ans += answear[i];
    }
    answears[days] = ans;
    return ans;
}

int main(){
    ifstream fin("Day6.txt");
    ios::sync_with_stdio(false);
    int nr;
    char ch;
    while(fin >> nr){
        fin >> ch;
        values.push_back(nr);
    }
    int i = 0;
    while(i < 80){
        int ssize = values.size();
        for(int j = 0; j < ssize; ++j){
            nr = values.front();
            values.pop_front();
            if(nr == 0){
                values.push_back(6);
                values.push_back(8);
            }
            else{
                values.push_back(nr-1);
            }
        }
        ++i;
    }
    cout << values.size() << '\n';
    fin.close();
    fin.open("Day6.txt");
    values.clear();
    while(fin >> nr){
        fin >> ch;
        values.push_back(nr);
    }
    unsigned long long ans = 0;
    for(int i : values){
        ans += calcAfter(i);
    }
    cout << ans;
    return 0;
}
