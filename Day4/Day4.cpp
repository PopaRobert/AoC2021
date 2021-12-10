#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

vector <int> bingo;
int cmat[6][6];
int freq[6][6];

bool checkBingo(){
    for(int r = 0; r < 5; ++r){
        int cmarked = 0, rmarked = 0;
        for(int c = 0; c < 5; ++c){
            if(freq[r][c])
                ++cmarked;
            if(freq[c][r])
                ++rmarked;
        }
        if(rmarked == 5 || cmarked == 5)
            return true;
    }
    return false;
}

int unmarked(){
    int sum = 0;
    for(int r = 0; r < 5; ++r)
        for(int c = 0; c < 5; ++c)
            if(freq[r][c] == 0)
                sum += cmat[r][c];
    return sum;
}

int main(){
    ifstream fin("Day4.txt");
    int number;
    char ch;
    
    fin >> number;
    bingo.push_back(number);
    fin >> ch;
    while(ch == ','){
        fin >> number;
        bingo.push_back(number);
        fin >> ch;
    }
    int winner = 0, wmoves = 0;
    while(!fin.eof()){
        for(int r = 0; r < 5; ++r)
            for(int c = 0; c < 5; ++c){
                fin >> cmat[r][c];
                freq[r][c] = 0;
            }
        int moves = 0;
        for(int i : bingo){
            ++moves;
            for(int r = 0; r < 5; ++r)
                for(int c = 0; c < 5; ++c)
                    if(cmat[r][c] == i)
                        freq[r][c] = 1;
            if(checkBingo()){
                //for part 1 wmoves = 100000(up) and if(wmoves > moves) ... and delete final break;
                if(wmoves < moves){
                    wmoves = moves;
                    winner = unmarked();
                    winner *= i;
                    break;
                }
                break;
            }
        }

    }
    cout << winner;
    fin.close();
    fin.open("Day4.txt");
    
    return 0;
}