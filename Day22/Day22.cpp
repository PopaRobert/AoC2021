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

int reactor[500][500][500];
int state = 0;
string line;
pair<long long, long long> x, y, z;
int cnt;

void get_values(){
    int i = 2, sign = 0;
    x.first = 0;
    x.second = 0;
    if(line[i] == '-'){
        sign = 1;
        ++i;
    }
    while(line[i] >= '0' && line[i] <= '9'){
        x.first *= 10;
        x.first += line[i] - '0';
        ++i;
    }
    if(sign == 1)
        x.first *= -1;
    sign = 0;
    while((line[i] < '0' || line[i] > '9') && line[i] != '-'){
        ++i;
    }
    if(line[i] == '-'){
        sign = 1;
        ++i;
    }
    while(line[i] >= '0' && line[i] <= '9'){
        x.second *= 10;
        x.second += line[i] - '0';
        ++i;
    }
    if(sign == 1)
        x.second *= -1;
    sign = 0;
    y.first = 0;
    y.second = 0;
    while((line[i] < '0' || line[i] > '9') && line[i] != '-')
        ++i;
    if(line[i] == '-'){
        sign = 1;
        ++i;
    }
    while(line[i] >= '0' && line[i] <= '9'){
        y.first *= 10;
        y.first += line[i] - '0';
        ++i;
    }
    if(sign == 1)
        y.first *= -1;
    sign = 0;
    while((line[i] < '0' || line[i] > '9') && line[i] != '-')
        ++i;

    if(line[i] == '-'){
        sign = 1;
        ++i;
    }
    while(line[i] >= '0' && line[i] <= '9'){
        y.second *= 10;
        y.second += line[i] - '0';
        ++i;
    }
    if(sign == 1)
        y.second *= -1;
    sign = 0;
    z.first = 0;
    z.second = 0;
     while((line[i] < '0' || line[i] > '9') && line[i] != '-')
        ++i;

    if(line[i] == '-'){
        sign = 1;
        ++i;
    }
    while(line[i] >= '0' && line[i] <= '9'){
        z.first *= 10;
        z.first += line[i] - '0';
        ++i;
    }
    if(sign == 1)
        z.first *= -1;
    sign = 0;

    while((line[i] < '0' || line[i] > '9') && line[i] != '-')
        ++i;

    if(line[i] == '-'){
        sign = 1;
        ++i;
    }
    while(line[i] >= '0' && line[i] <= '9'){
        z.second *= 10;
        z.second += line[i] - '0';
        ++i;
    }
    if(sign == 1)
        z.second *= -1;
}

struct {
    pair<long long, long long> x, y, z;
    int state;
}status[1000000], to_add, back_add[1000000];

int num_status = 0;

pair <long long, long long> intersection_x(int key){
    pair <long long, long long> x_return(INT_MAX, INT_MAX);
    if(x.first > status[key].x.second || status[key].x.first > x.second)
        return x_return;
    x_return.first = max(x.first, status[key].x.first);
    x_return.second = min(x.second, status[key].x.second);
    return x_return;
}

pair <long long, long long> intersection_y(int key){
    pair <long long, long long> y_return(INT_MAX, INT_MAX);
    if(y.first > status[key].y.second || status[key].y.first > y.second)
        return y_return;
    y_return.first = max(y.first, status[key].y.first);
    y_return.second = min(y.second, status[key].y.second);
    return y_return;

}

pair <long long, long long> intersection_z(int key){
    pair <long long, long long> z_return(INT_MAX, INT_MAX);
    if(z.first > status[key].z.second || status[key].z.first > z.second)
        return z_return;
    z_return.first = max(z.first, status[key].z.first);
    z_return.second = min(z.second, status[key].z.second);
    return z_return;
}

void add_status(pair<long long, long long> x1, pair<long long, long long> y1, pair<long long, long long> z1, int add_state){
    back_add[cnt].x = x1;
    back_add[cnt].y = y1;
    back_add[cnt].z = z1;
    back_add[cnt].state = add_state;
    ++cnt;
}

void set_state(){
    to_add.x = x;to_add.y = y;to_add.z = z;to_add.state = state;
    pair <long long, long long> xI, yI, zI;
    for(int i = 0; i < num_status; ++i){
        xI = intersection_x(i);
        if(xI.first != INT_MAX && xI.second != INT_MAX){
            yI = intersection_y(i);
            if(yI.first != INT_MAX && yI.second != INT_MAX){
                zI = intersection_z(i);
                if(zI.first != INT_MAX && zI.second != INT_MAX){
                    add_status(xI, yI, zI, status[i].state * (-1));
                }
            }
        }
    }
    if(to_add.state == 1)
        status[num_status++] = to_add;
    for(int i = 0; i < cnt; ++i){
        status[num_status++] = back_add[i];
    }
    cnt = 0;   
}

unsigned long long add_ans(int key){
    pair<long long, long long> x1, y1, z1;
    x1 = status[key].x;
    y1 = status[key].y;
    z1 = status[key].z;
    return (x1.second - x1.first + 1) * (y1.second - y1.first + 1) * (z1.second - z1.first + 1);
}

int main(){
    ifstream fin("Day22.txt");
    while(fin >> line){
        if(line == "on")
            state = 1;
        else
            state = -1;
        fin >> line;
        get_values();
        if((x.first >= -50 && x.second <= 50) && (y.first >= -50 && y.second <= 50) && (z.first >= -50 && z.second <= 50))
        for(int i = x.first; i <= x.second; ++i)
            for(int j = y.first; j <= y.second; ++j)
                for(int k = z.first; k <= z.second; ++k)
                    reactor[i+50][j+50][k+50] = state;
    }
    unsigned long long ans = 0;
    for(int i = 0; i <= 101; ++i)
            for(int j = 0; j <= 101; ++j)
                for(int k = 0; k <= 101; ++k)
                    if(reactor[i][j][k] == 1)
                        ++ans;

    cout << ans << '\n';

    fin.close();
    fin.open("Day22.txt");
    while(fin >> line){
        if(line == "on")
            state = 1;
        else
            state = -1;
        fin >> line;
        get_values();
        set_state();
    }
    ans = 0;
    for(int i = 0; i < num_status; ++i){
        if(status[i].state == 1)
            ans += add_ans(i);
        else
            ans -= add_ans(i);
    }
    cout << ans << '\n';
    return 0;
}
