#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int freq[10000];

int transform(string n){
    int number = 0;
    for(int i = n.size()-1; i >= 0; --i){
        if(n[i] == '1'){
            number += pow(2, n.size() - i);
        }
    }
    return number;
}

int main(){
    ifstream fin("Day3.txt");
    string s;
    int read = 0;
    int ssize;
    while(fin >> s){
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '1')
                ++freq[i];
        }
        ssize = s.size();
        ++read;
    }
    string gamma, epsilon;
    for(int i = 0; i < ssize; ++i){
        if(freq[i] >= read/2){
            gamma += '1';
            epsilon += '0';
        }
        else{
            gamma += '0';
            epsilon += '1';
        }
    }
    cout << (transform(gamma) /2) * (transform(epsilon)/2) << '\n';
    fin.close();
    fin.open("Day3.txt");
    memset(freq, 0, sizeof(freq));
    vector <string> good;
    while(fin >> s){
        good.push_back(s);
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '1')
                ++freq[i];
        }
    }
    int i = 0;
    char ch;
    string second;
    vector <string> gcpy;
    while(good.size() > 1){
        gcpy.clear();
        if(read - freq[i] <= freq[i])
            ch = '1';
        else
            ch = '0';
        for(string j : good){
            if(j[i] == ch){
                gcpy.push_back(j);
            }
        }
        memset(freq, 0, sizeof(freq));
        ++i;
        good = gcpy;
        for(string j : good){
            if(j[i] == '1')
                ++freq[i];
        }
        read = good.size();
    }
    //cout << second << '\n';
    int first = transform(good[0])/2;
    fin.close();
    fin.open("Day3.txt");
    good.clear();
    read = 0;
    while(fin >> s){
        good.push_back(s);
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '1')
                ++freq[i];
        }
    }
    i = 0;
    while(good.size() > 1){
        read = good.size();
        gcpy.clear();
        if(read-freq[i] > freq[i])
            ch = '1';
        else
            ch = '0';
        for(string j : good){
            if(j[i] == ch){
                gcpy.push_back(j);
            }
        }
        memset(freq, 0, sizeof(freq));
        ++i;
        good = gcpy;
        for(string j : good){
            if(j[i] == '1')
                ++freq[i];
        }
    }
    cout << good[0] << '\n';
    cout << first * (transform(good[0])/2);
    return 0;
}