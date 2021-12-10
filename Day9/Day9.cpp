#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <deque>
#include <string.h>

using namespace std;
vector <string> strings;
vector <pair<int, int>> minP;
vector <int> basins;
int marked[1000][1000];

int main(){
    ifstream fin("Day9.txt");
    string up = ":", mid = ":", down = ":", up1, down1, mid1;
    string s = "99999999999999999999999999999999";
    strings.push_back(s);
    int cnt = 3;
    unsigned long long ans = 0;
    fin >> up1;
    fin >> mid1;
    fin >> down1;
    up += up1;
    mid += mid1;
    down += down1;
    mid += ':';
    up += ':';
    down += ':';
    strings.push_back(up);
    strings.push_back(mid);
    strings.push_back(down);
    for(int i = 1; i < up.size()-1; ++i){
        if(up[i] < up[i-1]  && up[i] < up[i+1] && up[i] < mid[i])
            ans += up[i] - '0' + 1, minP.push_back(pair<int, int> (1, i));
        if(mid[i] < up[i] && mid[i] < mid[i-1] && mid[i] < mid[i+1] && mid[i] < down[i]){
            ans += mid[i] - '0' + 1, minP.push_back(pair<int, int> (2, i));
        }
    }
    while(!fin.eof()){
        up = mid;
        mid = down;
        fin >> down1;
        down = ":";
        down += down1;
        down += ':';
        strings.push_back(down);
        for(int i = 1; i < up.size() - 1; ++i){
            if(mid[i] < up[i] && mid[i] < mid[i-1] && mid[i] < mid[i+1] && mid[i]< down[i])
                ans += mid[i] - '0' + 1, minP.push_back(pair<int, int> (cnt, i));
        }
        ++cnt;
    }
    for(int i = 1; i < up.size() - 1; ++i){
        if(down[i] < down[i-1] && down[i] < down[i+1] && down[i] < mid[i])
            ans += down[i] - '0' + 1, minP.push_back(pair<int, int> (cnt, i));
    }
    cout << ans << '\n';
    ans = 1;
    strings.push_back(s);
    deque <pair<int, int>> points;
    cnt = 0;
    for(auto i = minP.begin(); i != minP.end(); ++i){
        cout << cnt << ' ';
        points.clear();
        pair <int, int> cr;
        cr.first = i->first;
        cr.second = i->second;
        points.push_back(cr);
        int bsize = 0;
        memset(marked, 0, sizeof(marked));
        while(!points.empty()){
            ++bsize;
            pair <int, int> coord;
            coord = points.front();
            char ch = strings[coord.first][coord.second];
            //cout << ch << ' ';
            points.pop_front();
            if(strings[coord.first][coord.second+1] == ch + 1 && ch + 1 != '9' && !marked[coord.first][coord.second+1])
                points.push_back(pair<int, int> (coord.first, coord.second+1)), marked[coord.first][coord.second+1]++;
            if(strings[coord.first][coord.second-1] == ch + 1 && ch + 1 != '9' && !marked[coord.first][coord.second-1])
                points.push_back(pair<int, int> (coord.first, coord.second-1)), marked[coord.first][coord.second-1]++;
            if(strings[coord.first-1][coord.second] == ch + 1 && ch + 1 != '9' && !marked[coord.first-1][coord.second])
                points.push_back(pair<int, int> (coord.first-1, coord.second)), marked[coord.first-1][coord.second]++;
            if(strings[coord.first+1][coord.second] == ch + 1 && ch + 1 != '9' && !marked[coord.first+1][coord.second])
                points.push_back(pair<int, int> (coord.first+1, coord.second)), marked[coord.first+1][coord.second]++;
        }
        //cout << bsize << '\n';
        //cout << '\n';
        basins.push_back(bsize);
        ++cnt;
    }
    
    sort(basins.begin(), basins.end());
    int i = basins.size()-1;
    ans *= basins[i];
    --i;
    ans *= basins[i];
    --i;
    ans *= basins[i];
    cout << ans << '\n';
    
    return 0;
}