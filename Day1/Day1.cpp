#include <fstream>
#include <iostream>

using namespace std;

int main(){
    long long ans = 0;
    int curr, prev;
    ifstream fin("Day1.txt");
    fin >> prev;
    while(fin >> curr){
        if(curr > prev)
            ++ans;
        prev = curr;
    }
    cout << ans << '\n';

    fin.close();
    fin.open("Day1.txt");
    int first, second, third, nr;
    ans = 0;
    fin >> first >> second >> third;
    prev = first + second + third;
    while(fin >> nr){
        curr = prev - first + nr;
        first = second;
        second = third;
        third = nr;
        if(curr > prev)
            ++ans;
        prev = curr;
    }
    cout << ans << '\n';
    return 0;
}