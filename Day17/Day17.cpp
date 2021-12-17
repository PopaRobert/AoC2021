#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <limits.h>

using namespace std;

long long ans = INT_MIN, yAns, cnt;
long long x = 150, x1 = 193, y = -136, y1 = -86;
long long xC, yC;
multimap <int, int> values;

void solve(int xAct, int yAct){
    int xV = xAct-1, yV = yAct -1;
    int yMax = -100000;
    while(xAct <= x1 && yAct >= y){
        yMax = max(yMax, yAct);
        if(x <= xAct && xAct <= x1 && y <= yAct && yAct<= y1){
            values.insert(make_pair(xC, yC));
            ++cnt;
            if(yMax > ans){
                ans = yMax;
            }
        }
        xAct += xV;
        yAct += yV;
        if(xV > 0)
            --xV;
        else if(xV < 0)
            ++xV;
        --yV;
    }
}


int main()
{
    for(int i = 0; i < 300; ++i)
        for(int j = -200; j < 150; ++j){
            xC = i;
            yC = j;
            solve(i, j);
        }
    cout << ans << '\n';
    pair<int, int> it;
    for(auto i : values){
        if(it.first == i.first && it.second == i.second)
            --cnt;
        it = i;
    }

    cout << cnt << '\n';
    return 0;
}
