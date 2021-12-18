#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

string s, prevS;
int ok, test;

void split(int pos){
    ok = 1;
    int x = 0, nr = 0, i, nr2;
    for(i = pos; s[i] >= '0' && s[i] <= '9'; ++i){
        nr *= 10;
        nr += s[i] - '0';
        ++x;
    }
    string help;
    help = '[';
    help += to_string(nr / 2);
    if(nr % 2 == 0)
        nr2 = nr / 2;
    else
        nr2 = nr / 2 + 1;
    help += ',';
    help += to_string(nr2);
    help += ']';
    s.replace(pos, x, help);
}

void explode(int pos){
    ok = 1;
    int i, j, x = 0, y = 0, nr, nrAdd = 0, nrAddT = 0, cnt, nrSize = 0;
    for(j = pos; s[j] >= '0' && s[j] <= '9'; ++j){
        nrAdd *= 10;
        nrAdd += s[j] - '0';
        ++y;
    }
    for(j = j+1; s[j] >= '0' && s[j] <= '9'; ++j){
        nrAddT *= 10;
        nrAddT += s[j] - '0';
        ++y;
    }
    
    cnt = 0;
    for(i = pos-1; i >= 0; --i){
        nr = 0;
        if(s[i] >= '0' && s[i] <= '9'){
            for(j = i; s[j] >= '0' && s[j] <= '9'; --j)
                ;
            for(j = j+1; s[j] >= '0' && s[j] <= '9'; ++j){
                nr *= 10;
                nr += s[j] - '0';
                ++cnt;
            }
            break;
        }
    }
    for(j = i; s[j] >= '0' && s[j] <= '9'; --j);

    if(i != -1){
        s.replace(j+1, cnt, to_string(nr+nrAdd));
        nrSize += (to_string(nr+nrAdd)).size() - cnt;
        cnt = 0;
    }
    for(i = pos+2 + nrSize + y; i < s.size(); ++i){
        nr = 0;
        if(s[i] >= '0' && s[i] <= '9'){
            for(j = i; s[j] >= '0' && s[j] <= '9'; ++j){
                nr *= 10;
                nr += s[j] - '0';
                ++cnt;
            }
            break;
        }
    }
    if(i != s.size()){
        s.replace(i, cnt, to_string(nr+nrAddT));
    }
    s.replace(pos+nrSize-1, 3 + y, "0");    
}

int insideP(int x){
    int i = x-1, j = x+1, pari = 0, pard = 0, cd = 0;
    while(true){
        if(i < 0 && j >= s.size())
            break;
        while(s[i] != '[' && i >= 0){
            if(s[i] == ']'){
                ++cd;
                --i;
                for(; cd; --i){
                    if(s[i] == ']')
                        ++cd;
                    if(s[i] == '[')
                        --cd;
                }
                ++i;
            }
            --i;
        }
        ++pari;
        while(s[j] != ']' && j < s.size()){
            if(s[j] == '['){
                ++cd;
                ++j;
                for(; cd; ++j){
                    if(s[j] == '[')
                        ++cd;
                    if(s[j] == ']')
                        --cd;
                }
                --j;
            }
            ++j;
        }
        if(j < s.size())
        ++pard;
        ++j;
        --i;
    }
    return min(pari, pard);
}

void reduce(){
    test = 0;
    ok = 1;
    string help;
    while(ok){
        ok = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] >= '0' && s[i] <= '9'){
                if(insideP(i) == 5){
                    explode(i);
                    test = 1;
                    i = s.size();
                }
            }
        }
    }
    ok = 1;
    while(ok){
        ok = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] >= '0' && s[i] <= '9')
                if(s[i+1] >= '0' && s[i+1] <= '9'){
                    split(i);
                    test = 1;
                    i = s.size();
                    ok = 0;
                }
        }
    }
    if(test)
        reduce();
}

void add(){
    if(prevS.size() == 0)
        return;
    prevS.insert(0, "[");
    prevS += ",";
    prevS += s;
    prevS += "]";
    s = prevS;
}

int sum(){
    int sum = 0;
    int nr = 0, i, j, x = 0, csum = 0;
    vector <int> values;
    while(s[s.size()-1] == ']'){
        for(i = 0; i < s.size(); ++i){
            nr = 0;
            if(s[i] == '[' && s[i+1] >='0' && s[i+1] <= '9'){
                x = 0;
                csum = 0;
                for(j = i+1; s[j] >= '0' && s[j] <= '9'; ++j){
                    nr *= 10;
                    nr += s[j] - '0';
                    ++x;
                }
                ++j;
                if(s[j] < '0' || s[j] > '9')
                    continue;
                csum += nr * 3;
                nr = 0;
                for(; s[j] >= '0' && s[j] <= '9'; ++j){
                    nr *= 10;
                    nr += s[j] - '0';
                    ++x;
                }
                csum += nr * 2;
                s.replace(i, x+3, to_string(csum));
            }
        }
    }
    j = 0;
    while(j < s.size()){
        sum *= 10;
        sum += s[j] - '0';
        ++j;
    }
    return sum;
}

int main(){
    ifstream fin("Day18.txt");
    prevS.clear();
    while(fin >> s){
        if(prevS.size() > 0){
            add();
            reduce();
        }
        prevS = s;
    }
    fin.close();
    cout << s << '\n';
    cout << sum() << '\n';
    int maxx = INT_MIN;
    for(int i = 0; i < 100; ++i){
        fin.open("Day18.txt");
        string now;
        for(int k = 0; k <= i; ++k){
            fin >> now;
        }
        fin.close();
        fin.open("Day18.txt");
        for(int k = 0; k < 100; ++k){
            prevS = now;
            fin >> s;
            if(k == i)
                continue;
            add();
            reduce();
            maxx = max(maxx, sum());
        }
        fin.close();
    }
    cout << maxx;
    
    return 0;
}