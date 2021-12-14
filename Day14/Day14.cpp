#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>
#include <string.h>
#include <map>

using namespace std;

string s, first, second, aux;
map <string, string> values;
map <string, long long> pairs;
map <string, long long> pairsCpy;
long long cnt[201];

int main(){
    ifstream fin("Day14.txt");
    //cin.tie();
    //ios::sync_with_stdio(false);
    fin >> s;
    while(!fin.eof()){
        fin >> first >> aux >> second;
        values[first] = second;
    }
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < s.size(); ++j){
            aux = s[j];
            aux += s[j+1];
            for(auto l : values)
                if(l.first == aux){
                    s.insert(j+1, l.second);
                    ++j;
                }
        }
    }
    long long maxx = 0, minn = 1000000000;
    for(int i = 0; i < s.size(); ++i){
        cnt[s[i]]++;
    }
    for(int i = 0; i < 100; ++i){
        maxx = max(maxx, cnt[i]);
        if(cnt[i] != 0)
            minn = min(minn, cnt[i]);
    }
    cout << maxx - minn << '\n';

    fin.close();
    fin.open("Day14.txt");

    fin >> s;
    while(!fin.eof()){
        fin >> first >> aux >> second;
        values[first] = second;
    }
    for(int i = 0; i < s.size()-1; ++i){
        aux = s[i];
        aux += s[i+1];
        pairs[aux]++;
    }

    for(int i = 0; i < 40; ++i){
        for(auto j : pairs){
            for(auto k : values){
                if(j.first == k.first){
                    aux = k.first[0];
                    aux += k.second;
                    pairsCpy[aux] += j.second;
                    aux = k.second;
                    aux += k.first[1];
                    pairsCpy[aux] += j.second;
                    break;
                }
            }
        }
        pairs = pairsCpy;
/*
        cout << i << '\n';
        for(auto j : pairs)
            cout << j.first << ' ' << j.second << '\n';
*/
        pairsCpy.clear();
    }
    memset(cnt, 0, sizeof(cnt));
    for(auto i : pairs){
        cnt[i.first[0]] += i.second / 2;
        cnt[i.first[1]] += i.second / 2;
    }
    maxx = 0, minn = 10000000000000;
    for(int i = 65; i <= 90; ++i){
        maxx = max(maxx, cnt[i]);
        if(cnt[i] > 0){
            minn = min(minn, cnt[i]);
            if(i == 'P')
                --minn;
        }
    }
    cout << maxx - minn << '\n';

    return 0;
}
