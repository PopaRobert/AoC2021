#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ifstream fin("Day2.txt");
    string s;
    int n;
    unsigned long long forward = 0, depth = 0, aim = 0;
    while(fin >> s){
        fin >> n;
        if(s[0] == 'f'){
            forward += n;
        }
        else if(s[0] == 'd'){
            depth += n;
        }
        else if(s[0] == 'u'){
            depth -= n;
        }
    }
    cout << forward * depth << '\n';

    fin.close();
    fin.open("Day2.txt");
    depth = 0, forward = 0;
    while(fin >> s){
        fin >> n;
        if(s[0] == 'f'){
            forward += n;
            depth += aim * n;
        }
        else if(s[0] == 'd'){
            aim += n;
        }
        else if(s[0] == 'u'){
            aim -= n;
        }
    }
    cout << forward * depth;
    return 0;
}