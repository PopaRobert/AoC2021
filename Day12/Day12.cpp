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

multimap <string, string> connections;
vector <string> toEnd;
vector <string> start;
map <string, int> visit;
vector <string> path(100000);

long long ans;

void dfs(string nod, string prev, int cnt, bool ok){
    auto it = connections.find(nod);
    if(it->first == "end"){
        ++ans;
        return;
    }
    while(it->first == nod){
        if((visit[it->second] != 2 || (it->second[0] >= 65 && it->second[0] <= 90)) && it->second != "start" && (ok == true || visit[it->second] == 0 || (it->second[0] >= 65 && it->second[0] <= 90))){
            if(it->second[0] >= 90)
                visit[it->second]++;
            path[cnt] = nod;
            if(visit[it->second] == 2 || ok == false)
                dfs(it->second, nod, cnt + 1, false);
            else if(visit[it->second] < 2)
                dfs(it->second, nod, cnt + 1, true);
            visit[it->second]--;
        }
        ++it;
    }
}

int main(){
    ifstream fin("Day12.txt");
    string s;
    while(fin >> s){
        string word;
        string nod;
        for(int i = 0; i < s.size(); ++i)
            if(s[i] != '-')
                word += s[i];
            else{
                nod = word;
                word.clear();
            }
        connections.insert(make_pair(nod, word));
        connections.insert(make_pair(word, nod));
    }
    dfs("start", "0", 0, true);
    cout << ans << '\n';
    fin.close();
    fin.open("Day11.txt");

    return 0;
}
