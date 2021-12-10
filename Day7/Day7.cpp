#include <fstream>
#include <iostream>

using namespace std;

int freq[20005];

int main(){
    int nr;
    char ch;
    ifstream fin("Day7.txt");
    while(fin >> nr){
        fin >> ch;
        freq[nr]++;
    }
    int maxx = 0, maxval;
    long long ans = 100000000, cans = 0;
    for(int i = 0; i < 2000; ++i){
        cans = 0;
        for(int j = 0; j < 2000; ++j){
            for(int k = 0; k < freq[j]; ++k){
                int cnt = 1;
                for(int l = min(j, i); l < max(j, i); ++l, ++cnt)
                    cans += cnt;
            }
        }
        ans = min(ans, cans);
    }
    
    cout << ans << '\n';
    fin.close();
    fin.open("Day7.txt");
    
    return 0;
}